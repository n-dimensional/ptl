#ifndef CORE_PAYLOADS_HPP
#define CORE_PAYLOADS_HPP

#include <pugixml.hpp>

#include "event_pool.h"
#include "abstract_lib.h"
#include "payload.hpp"

namespace core
{

class payloads
{
protected:
    struct module_t
    {
    abstract::lib_t     m_lib;
    payload::payload_t  m_payload;
    };

std::vector<module_t>   m_modules;

void    load_modules(const pugi::xml_node& cfg);
void    load_module(const char* name);

public:
        payloads(const pugi::xml_node& cfg, event_pool& pool);
};

} // namespace core

#endif

