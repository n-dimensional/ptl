#include <module.h>
#include <transport.h>

#include "tcp.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define TRANSPORT_COUNT 1

static const struct module_info_t module_info = { MODULE_API_VERSION, MODULE_TYPE_TRANSPORT };

static transport_interface_t transports[TRANSPORT_COUNT];

struct module_info_t MODULE_INFO_FUNC_NAME()
{
return module_info;
}

size_t TRANSPORT_COUNT_FUNC_NAME()
{
return TRANSPORT_COUNT;
}

struct transport_interface_t* TRANSPORT_INTERFACE_FUNC_NAME()
{
transports[0].full_name = tcp_full_name;
transports[0].short_name = tcp_short_name;
transports[0].init = tcp_init;
transports[0].copy = tcp_copy;
transports[0].cleanup = tcp_cleanup;

transports[0].connection.listen = tcp_listen;
transports[0].connection.connect = tcp_connect;
transports[0].connection.close = tcp_close;

return transports;
}

#ifdef __cplusplus
} //extern "C"
#endif

