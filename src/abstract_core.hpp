#include "core.hpp"

#ifndef ABSTRACT_CORE_HPP
#define ABSTRACT_CORE_HPP

#include "abstract_base.hpp"

namespace abstract
{

class core_t:
    public base<core::interface_t,core::handle_t>
{
public:
inline              core_t();
inline              core_t(const interface_t* interface, handle_t handle);
inline              core_t(const core_t& origin);
inline              ~core_t();

using               base::operator =;

inline event_base*  get_event_base();
};

} //namespace abstract

#include "abstract_core.inc"

#endif

