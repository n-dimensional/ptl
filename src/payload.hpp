#include "core.hpp"

#ifndef PAYLOAD_HPP
#define PAYLOAD_HPP

#include "payload.h"

namespace payload
{
typedef c::payload_name_t           name_t;
typedef c::payload_handle_t         handle_t;
typedef c::payload_interface_t      interface_t;
typedef c::payload_interface_func_t payload_interface_func_t;
} //namespace payload

#include "abstract_lib.h"
#include "abstract_payload.hpp"

namespace payload
{
struct module_t
{
abstract::lib_t     m_lib;
abstract::payload_t m_payload;

inline              module_t();
inline              module_t(const module_t& origin);
inline              ~module_t();
inline  module_t&   operator = (const module_t& rvalue);
};

module_t::module_t():
    m_lib( NULL ), m_payload()
{
}

module_t::module_t(const module_t& origin):
    m_lib( origin.m_lib ), m_payload( origin.m_payload )
{
}

module_t::~module_t()
{
m_lib = NULL;
}

module_t& module_t::operator = (const module_t& rvalue)
{
m_lib = rvalue.m_lib;
m_payload = rvalue.m_payload;
return *this;
}

} //namespace payload

#endif

