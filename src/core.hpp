#ifndef CORE_HPP
#define CORE_HPP

#include <string>

#include <event2/event.h>

#include "event_pool.hpp"
#include "core.h"

namespace core
{
typedef core::c::core_interface_t   interface_t;
typedef core::c::core_handle_t      handle_t;
} //namespace core

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
static  interface_t                 m_interface;
event_pool_t                        m_event_pool;
std::vector<transport::module_t>    m_transports;
std::vector<payload::module_t>      m_payloads;

void    cfg_threads(const pugi::xml_node& cfg);
void    cfg_modules(const pugi::xml_node& cfg);

void    load_modules(const pugi::xml_node& cfg);
void    load_module(const char* name, const pugi::xml_node& cfg);
void    load_module_transport(abstract::lib_t lib, const std::string& libname, const pugi::xml_node& cfg);
void    load_module_payload(abstract::lib_t lib, const std::string& libname, const pugi::xml_node& cfg);

public:
        core_t(const pugi::xml_node& cfg);
void    run(bool nonblock);

void    payload_enable();
void    payload_disable();

struct event_base*  get_event_base();
};

} //namespace core

#endif

