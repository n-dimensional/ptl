#ifndef IP_TCP_H
#define IP_TCP_H

#include <ptl/transport.h>

extern const char   tcp_full_name[];
extern const char   tcp_short_name[];

transport_handle_t  tcp_init(const core_interface_t* core_interface, core_handle_t core_handle);
transport_handle_t  tcp_copy(transport_handle_t handle);
void                tcp_cleanup(transport_handle_t handle);

void tcp_connect(const transport_handle_t transport, const addr_t addr, size_t size);
void tcp_listen(const transport_handle_t transport, const addr_t addr, size_t size);
void tcp_close(const transport_connection_handle_t connection);


#endif

