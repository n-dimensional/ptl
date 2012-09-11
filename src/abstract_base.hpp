#ifndef ABSTRACT_HPP
#define ABSTRACT_HPP

#include <stddef.h>

namespace abstract
{

template <class I, class H> //Interface, Handle
class base
{
public:
typedef I   interface_t;
typedef H   handle_t;

protected:
const interface_t*  m_interface;
handle_t            m_handle;

public:
inline                      base(const interface_t* interface = NULL, handle_t handle = NULL);
inline                      base(const base& origin);
inline                      ~base();

inline  bool                is_null() const;
inline  const interface_t*  interface() const;
inline  handle_t            handle() const;

inline  base&               operator = (const base& rvalue);
};

} //namespace abstract

#include "abstract_base.inc"

#endif

