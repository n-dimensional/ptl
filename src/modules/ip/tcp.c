#include <stdlib.h>
#include <event2/bufferevent.h>

#include "tcp.h"
#include "connection.h"

const char tcp_full_name[] = "tcp v0.1";
const char tcp_short_name[] = "tcp";

/*
gnutls_init( &conn->m_tls, GNUTLS_SERVER | GNUTLS_NONBLOCK );
gnutls_priority_set_direct( conn->m_tls, "NORMAL:+ANON-ECDH:+ANON-DH", NULL );
gnutls_certificate_credentials_t x509;
gnutls_certificate_allocate_credentials( &x509 );  //TODO: ret
gnutls_credentials_set( conn->m_tls, GNUTLS_CRD_CERTIFICATE, x509 );
gnutls_certificate_set_x509_key_file( x509, "cert.pem", "key.pem", GNUTLS_X509_FMT_PEM );
gnutls_dh_params_t dh_params;
gnutls_dh_params_init( &dh_params );
gnutls_dh_params_generate2( dh_params, 1023 );
gnutls_certificate_set_dh_params( x509, dh_params );
gnutls_dh_set_prime_bits( conn->m_tls, 1023 ); //TODO: ???
gnutls_certificate_server_set_request( conn->m_tls, GNUTLS_CERT_IGNORE );
gnutls_session_set_ptr( conn->m_tls, conn );
gnutls_transport_set_pull_function( conn->m_tls, (gnutls_pull_func)evbuf_tls_read );
gnutls_transport_set_push_function( conn->m_tls, (gnutls_push_func)evbuf_tls_write );
*/

struct transport_core
{
uint32_t            links;
core_interface_t*   core_interface;
core_handle_t      core_handle;
};

transport_handle_t tcp_init(const core_interface_t* core_interface, core_handle_t core_handle)
{
struct transport_core* transport = malloc( sizeof(struct transport_core) );
transport->links = 1;
transport->core_interface = core_interface;
transport->core_handle = core_handle;
return transport;
}

transport_handle_t tcp_copy(transport_handle_t handle)
{
struct transport_core* transport = (struct transport_core*)handle;
++transport->links;
return transport;
}

void tcp_cleanup(transport_handle_t handle)
{
struct transport_core* transport = (struct transport_core*)handle;
--(transport->links);
if ( 0 == transport->links )
    free( transport );
}

void tcp_connect(const transport_handle_t handle, const addr_t addr, size_t size)
{
struct transport_core* transport = (struct transport_core*)handle;
struct event_base* base = transport->core_interface->get_event_base( transport->core_handle );
struct bufferevent* bev = bufferevent_socket_new( base, -1, BEV_OPT_CLOSE_ON_FREE );
//bufferevent_setcb( bev, connection_handshake_cb, connection_handshake_cb, connection_event_cb, conn );
//bufferevent_enable( bev, EV_READ | EV_WRITE );
}

void tcp_listen(const transport_handle_t transport, const addr_t addr, size_t size)
{
}

void tcp_close(const transport_connection_handle_t connection)
{
}

