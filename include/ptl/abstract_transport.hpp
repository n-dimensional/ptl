#ifndef ABSTRACT_TRANSPORT_HPP
#define ABSTRACT_TRANSPORT_HPP

#include <ptl/transport_base.hpp>
#include <ptl/abstract_base.hpp>
#include <ptl/abstract_core.hpp>

namespace abstract
{

class transport_t:
    public base<transport::interface_t,transport::handle_t>
{
public:
typedef transport::name_t       name_t;

inline          transport_t();
inline          transport_t(const interface_t* interface, const abstract::core_t& core);
inline          transport_t(const transport_t& origin);
inline          ~transport_t();

using           base::operator =;

inline  name_t  full_name() const;
inline  name_t  short_name() const;

inline  void    open();
inline  void    listen();
inline  void    close();
};

} //namespace abstract

#include <ptl/abstract_transport.inc>

#endif

