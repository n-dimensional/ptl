#include <stdint.h>
#include <ptl/module.hpp>
#include <ptl/abstract_payload.hpp>
#include <ptl/abstract_core.hpp>

#define BASE_PAYLOAD_ID 0

static const char BASE_FULL_NAME[] = "base v0.1";
static const char BASE_SHORT_NAME[] = "base";

class base_payload_t;

extern "C"
{
module::info_t MODULE_INFO_FUNC_NAME();
payload::interface_t* PAYLOAD_INTERFACE_FUNC_NAME();

payload::handle_t   init_func(const core::interface_t* intreface, core::handle_t handle);
payload::handle_t   copy_func(payload::handle_t handle);
void                cleanup_func(payload::handle_t handle);
}

static const struct module::info_t module_info( module::api_version, module::type::payload );

payload::interface_t module_interface = {
    BASE_FULL_NAME,
    BASE_SHORT_NAME,
    BASE_PAYLOAD_ID,
    init_func,
    copy_func,
    cleanup_func
    };

module::info_t MODULE_INFO_FUNC_NAME()
{
return module_info;
}

payload::interface_t* PAYLOAD_INTERFACE_FUNC_NAME()
{
return &module_interface;
}

class base_payload_t
{
protected:
uint32_t            m_links;
abstract::core_t    m_core;

public:
        base_payload_t(const abstract::core_t& core);
void    link();
void    unlink();
};

base_payload_t::base_payload_t(const abstract::core_t& core):
    m_links( 1 ), m_core( core )
{
}

void base_payload_t::link()
{
++m_links;
}

void base_payload_t::unlink()
{
--m_links;
if ( 0 == m_links )
    delete this;
}

payload::handle_t init_func(const core::interface_t* interface, core::handle_t handle)
{
abstract::core_t core( interface, handle );
return new base_payload_t( core );
}

payload::handle_t copy_func(payload::handle_t handle)
{
base_payload_t* base = static_cast<base_payload_t*>( handle );
base->link();
return handle;
}

void cleanup_func(payload::handle_t handle)
{
base_payload_t* base = static_cast<base_payload_t*>( handle );
base->unlink();
}

