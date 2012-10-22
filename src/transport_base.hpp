#ifndef TRANSPORT_BASE_HPP
#define TRANSPORT_BASE_HPP

#include "transport.h"

namespace transport
{
typedef c::transport_interface_t        interface_t;
typedef c::transport_name_t             name_t;
typedef c::transport_handle_t           handle_t;

typedef c::transport_count_t            count_t;
typedef c::transport_count_func_t       count_func_t;
typedef c::transport_interface_func_t   interface_func_t;
} //namespace transport

#endif

