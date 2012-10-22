#include <stdlib.h>
#include <string.h>

#include <syslog.h>
#include <syslogpp.h>

#include <ptl/module.hpp>

#include "core.hpp"

namespace core
{

handle_t static_copy(handle_t handle)
{
return handle;
}

void static_cleanup(handle_t handle)
{
}

struct event_base*  static_get_event_base(handle_t handle)
{
core_t* core = static_cast<core_t*>( handle );
return core->get_event_base();
}

interface_t core_t::m_interface = {
    static_copy,
    static_cleanup,
    static_get_event_base 
    };

core_t::core_t(const pugi::xml_node& cfg):
    m_event_pool(), m_transports(), m_payloads()
{
pugi::xml_node threads_cfg;
pugi::xml_node modules_cfg;

for (pugi::xml_node child = cfg.first_child(); child; child = child.next_sibling())
    {   
    if ( child.empty() )
        continue;
    //else if ( !strcmp( child.name(), "" ) ) 
    else if ( !strcmp( child.name(), "threads" ) )
        threads_cfg = child;
    else if ( !strcmp( child.name(), "modules" ) )
        modules_cfg = child;
    else
        syslog( LOG_WARNING, "unexcepected config element '%s'", child.name() );
    }
cfg_threads( threads_cfg );
cfg_modules( modules_cfg );
}

void core_t::cfg_threads(const pugi::xml_node& cfg)
{
int32_t th_count;
if ( !strcmp( "auto", cfg.value() ) )
    {
    th_count = 4; //TODO: determine optimal threads count
    }
else
    {
    th_count = atoi( cfg.value() );
    if ( th_count < 1 )
        th_count = 1;
    }
m_event_pool.resize( th_count );
}

void core_t::cfg_modules(const pugi::xml_node& cfg)
{
load_modules( cfg );
}

void core_t::load_modules(const pugi::xml_node& cfg)
{
for (pugi::xml_node child = cfg.first_child(); child; child = child.next_sibling())
    {
    if ( child.empty() )
        continue;
    else if ( !strcmp( child.name(), "module" ) )
        {
        const char* libname = NULL;
        for (pugi::xml_attribute attr = child.first_attribute(); attr; attr = attr.next_attribute())
            {
            if ( !strcmp( attr.name(), "name" ) )
                libname = attr.value();
            else
                syslog( LOG_WARNING, "unexcepected config attr <module %s>", attr.name() );
            }
        if ( NULL == libname )
            {
            syslog( LOG_WARNING, "module: name not set" );
            continue;
            }
        load_module( libname, child );
        }
    else
        syslog( LOG_WARNING, "unexcepected config elements modules::%s", child.name() );
    }
}

void core_t::load_module(const char* name, const pugi::xml_node& cfg)
{
std::string libname( DLPATH );
libname += name;
libname += DLEXT;
syslog( LOG_DEBUG ) << "loading module '" << libname << '\'' << std::endl;
abstract::lib_t lib = abstract::lib_open( libname.c_str() );
if ( NULL == lib )
    {
    syslog( LOG_ERR, "failed to load module: %s (%s)", libname.c_str(), abstract::lib_error() );
    return;
    }
module::info_func_t info_func = (module::info_func_t)abstract::lib_sym( lib, STR(MODULE_INFO_FUNC_NAME) );
if ( NULL == info_func )
    {
    syslog( LOG_ERR, "module have no '" STR(MODULE_INFO_FUNC_NAME) "' func" );
    abstract::lib_close( lib );
    return;
    }
module::info_t info = info_func();
if ( module::api_version != info.api_version )
    {
    syslog( LOG_ERR, "invalid module API version: got 0x%08x, required 0x%08x", info.api_version, module::api_version );
    abstract::lib_close( lib );
    return;
    }
switch ( info.type )
    {
    case module::type::transport:
        load_module_transport( lib, libname, cfg );
        return;
    case module::type::payload:
        load_module_payload( lib, libname, cfg );
        return;
    default:
        {
        syslog( LOG_ERR, "invalid module type: 0x%08x", info.type );
        abstract::lib_close( lib );
        return;
        }
    }
}

void core_t::load_module_transport(abstract::lib_t lib, const std::string& libname, const pugi::xml_node& cfg)
{
transport::count_func_t count_func = (transport::count_func_t)abstract::lib_sym( lib, STR(TRANSPORT_COUNT_FUNC_NAME) );
if ( !count_func )
    {
    syslog( LOG_ERR, "transport module %s has no '" STR(TRANSPORT_COUNT_FUNC_NAME) "' func", libname.c_str() );
    abstract::lib_close( lib );
    return;
    }
transport::interface_func_t interface_func = (transport::interface_func_t)abstract::lib_sym( lib, STR(TRANSPORT_INTERFACE_FUNC_NAME) );
if ( !interface_func )
    {
    syslog( LOG_ERR, "transport module %s has no '" STR(TRANSPORT_INTERFACE_FUNC_NAME) "' func", libname.c_str() );
    abstract::lib_close( lib );
    return;
    }
const transport::interface_t* transports = interface_func();
transport::count_t transports_count = count_func();
if ( !transports || !transports_count )
    {
    syslog( LOG_ERR, "transport module %s has no transports", libname.c_str() );
    abstract::lib_close( lib );
    return;
    }

transport::module_t module;
module.m_lib = lib;
abstract::core_t core( &m_interface, this );
for (transport::count_t i = 0; i < transports_count; ++i)
    {
    syslog( LOG_NOTICE, "  loading transport %s", transports[i].full_name );
    abstract::transport_t transport( &transports[i], core ); 
    if ( ! transport.is_null() )
        module.m_transports.push_back( transport );
    else
        syslog( LOG_ERR, "can't init transport %s", transports[i].full_name );
    }
if ( module.m_transports.empty() )
    {
    abstract::lib_close( lib );
    return;
    }
m_transports.push_back( module );
}

void core_t::load_module_payload(abstract::lib_t lib, const std::string& libname, const pugi::xml_node& cfg)
{
payload::payload_interface_func_t payload_interface_func = (payload::payload_interface_func_t)abstract::lib_sym( lib, STR(PAYLOAD_INTERFACE_FUNC_NAME) );
if( !payload_interface_func )
    {
    syslog( LOG_ERR, "payload module %s has no '" STR(PAYLOAD_INTERFACE_FUNC_NAME) "' func", libname.c_str() );
    abstract::lib_close( lib );
    return;
    }
const payload::interface_t* payload = payload_interface_func();
if ( !payload )
    {
    syslog( LOG_ERR, "payload module %s has no payloads", libname.c_str() );
    abstract::lib_close( lib );
    return;
    }

syslog( LOG_NOTICE, "  loading payload %s", payload->full_name );
abstract::core_t core( &m_interface, this );
payload::module_t module;
module.m_lib = lib;
module.m_payload = abstract::payload_t( payload, core );
if ( module.m_payload.is_null() )
    {
    syslog( LOG_ERR, "can't init payload %s", payload->full_name );
    abstract::lib_close( lib );
    return;
    }
else
    m_payloads.push_back( module );
}

void core_t::run(bool nonblock)
{
m_event_pool.run( nonblock );
}

struct event_base* core_t::get_event_base()
{
return m_event_pool.get();
}

} //namespace core

