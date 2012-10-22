#ifndef CORE_HPP
#define CORE_HPP

#include <map>
#include <vector>
#include <string>

#include <event2/event.h>

#include "event_pool.hpp"
#include "transport.hpp"
#include "payload.hpp"

namespace core
{

handle_t            static_copy(handle_t handle);
void                static_cleanup(handle_t handle);
struct event_base*  static_get_event_base(handle_t handle);

class core_t
{
protected:
typedef std::vector<transport::module_t>                    transports_container_t;
typedef std::map<payload::id_t,payload::module_t>           payloads_container_t;
typedef std::vector<payloads_container_t::const_iterator>   payloads_table_t;

static  interface_t     m_interface;
event_pool_t            m_event_pool;
transports_container_t  m_transports;
payloads_container_t    m_payloads;
payloads_table_t        m_payloads_table;

void    cfg_threads(const pugi::xml_node& cfg);
void    cfg_modules(const pugi::xml_node& cfg);

void    load_modules(const pugi::xml_node& cfg);
void    load_module(const char* name, const pugi::xml_node& cfg);
void    load_module_transport(abstract::lib_t lib, const std::string& libname, const pugi::xml_node& cfg);
void    load_module_payload(abstract::lib_t lib, const std::string& libname, const pugi::xml_node& cfg);

public:
        core_t(const pugi::xml_node& cfg);
void    run(bool nonblock);

struct event_base*  get_event_base();
};

} //namespace core

#endif

