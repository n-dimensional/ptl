#ifndef ABSTRACT_PAYLOAD_HPP
#define ABSTRACT_PAYLOAD_HPP

#include "payload_base.hpp"
#include "abstract_base.hpp"
#include "abstract_core.hpp"

namespace abstract
{

class payload_t:
    public base<payload::interface_t,payload::handle_t>
{
public:
inline      payload_t();
inline      payload_t(const interface_t* interface, const abstract::core_t& core);
inline      ~payload_t();

using       base::operator =;
};

} //namespace abstract

#include "abstract_payload.inc"

#endif
