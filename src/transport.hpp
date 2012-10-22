#ifndef TRANSPORT_HPP
#define TRANSPORT_HPP

#include <stdint.h>
#include <stddef.h>

#include <vector>

#include <ptl/cross_lib.h>
#include <ptl/transport_base.hpp>
#include <ptl/abstract_transport.hpp>

namespace transport
{

struct module_t
{
abstract::lib_t                     m_lib;
std::vector<abstract::transport_t>  m_transports;

inline module_t();
inline module_t(const module_t& origin);
inline module_t& operator = (const module_t& rvalue);
};

module_t::module_t():
    m_lib( NULL ), m_transports()
{
}

module_t::module_t(const module_t& origin):
    m_lib( origin.m_lib ), m_transports( origin.m_transports )
{
}

module_t& module_t::operator = (const module_t& rvalue)
{
m_lib = rvalue.m_lib;
m_transports = rvalue.m_transports;
return *this;
}

} //namespace transport

#endif

