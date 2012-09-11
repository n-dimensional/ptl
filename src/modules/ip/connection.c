#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <gnutls/gnutls.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>
#include "connection.h"

struct connection
{
struct bufferevent* m_bev;
gnutls_session_t    m_tls;
};

struct evbuf_tls
{
struct bufferevent* m_bev;
struct evbuffer*    m_evbuf;
gnutls_session_t    m_tls;
};

void run_rehandshake()
{
abort();
}

void run_handshake()
{
abort();
}

enum bufferevent_filter_result connection_tls_read_filter(struct evbuffer *src, struct evbuffer *dst, ev_ssize_t dst_limit, enum bufferevent_flush_mode mode, void *arg)
{
fprintf( stderr, "readfilter\n" );
struct connection* conn = (struct connection*)arg;
struct evbuf_tls read_p;
struct evbuf_tls write_p;
read_p.m_bev = conn->m_bev;
read_p.m_evbuf = src;
read_p.m_tls = conn->m_tls;
write_p.m_bev = conn->m_bev;
write_p.m_evbuf = bufferevent_get_output( conn->m_bev );
write_p.m_tls = conn->m_tls;
gnutls_transport_set_ptr2( conn->m_tls, &read_p, &write_p );
char buff[4096];
size_t nread = gnutls_record_recv( conn->m_tls, buff, sizeof(buff) );
if ( nread < 0 )
    {
    switch ( nread )
        {
        case GNUTLS_E_REHANDSHAKE:
            run_handshake();
            return BEV_NEED_MORE;
        case GNUTLS_A_NO_RENEGOTIATION:
            //wtf?
            abort();
        case GNUTLS_E_INTERRUPTED:
        case GNUTLS_E_AGAIN:
            return BEV_NEED_MORE;
        }
    }
else
    {
    fprintf( stderr, "connection_tls_read_filter: decoded %zd bytes\n", nread );
    evbuffer_add( dst, buff, nread );
    }
return BEV_OK;
}

enum bufferevent_filter_result connection_tls_write_filter(struct evbuffer *src, struct evbuffer *dst, ev_ssize_t dst_limit, enum bufferevent_flush_mode mode, void *arg)
{
fprintf( stderr, "writefilter\n" );
struct connection* conn = (struct connection*)arg;
struct evbuf_tls read_p;
struct evbuf_tls write_p;
read_p.m_bev = conn->m_bev;
read_p.m_evbuf = bufferevent_get_input( conn->m_bev );
read_p.m_tls = conn->m_tls;
write_p.m_bev = conn->m_bev;
write_p.m_evbuf = dst;
write_p.m_tls = conn->m_tls;
gnutls_transport_set_ptr2( conn->m_tls, &read_p, &write_p );
/* determine how many chunks we need. */
int n = evbuffer_peek( src, -1, NULL, NULL, 0 );
struct evbuffer_iovec* v = malloc( sizeof(struct evbuffer_iovec) * n );
/* Actually fill up v. */
n = evbuffer_peek( src, -1, NULL, v, n);
int i = 0;
//size_t total = 0;
for (i = 0; i < n; ++i)
    {
    size_t nwrite = gnutls_record_send( conn->m_tls, v[i].iov_base, v[i].iov_len );
    if ( nwrite < 0 )
        {
        free( v );
        switch ( nwrite )
            {
            case GNUTLS_E_REHANDSHAKE:
                run_handshake();
                return BEV_NEED_MORE;
            case GNUTLS_A_NO_RENEGOTIATION:
                //wtf?
                abort();
            case GNUTLS_E_INTERRUPTED:
            case GNUTLS_E_AGAIN:
                return BEV_NEED_MORE;
            }
        }
    else
        {
        evbuffer_drain( src, nwrite );
        }
    }
free( v );
return BEV_OK;
}

ssize_t evbuf_tls_read(gnutls_transport_ptr_t arg, void* buf, size_t count)
{
struct evbuf_tls* p = (struct evbuf_tls*)arg;
ssize_t nread = evbuffer_remove( p->m_evbuf, buf, count );
fprintf( stdout, "evbuf_tls_read: %zd\n", nread );
if ( 0 == nread )
    {
    gnutls_transport_set_errno( p->m_tls, EAGAIN );
    return -1;
    }
else if ( nread < count )
    {
    size_t remain = count - nread;
    bufferevent_setwatermark( p->m_bev, EV_READ, remain, remain );
    }
return nread;
}

ssize_t evbuf_tls_write(gnutls_transport_ptr_t arg, const void* buf, size_t count)
{
struct evbuf_tls* p = (struct evbuf_tls*)arg;
fprintf( stdout, "evbuf_tls_write: %zu\n", count );
int ret = evbuffer_add( p->m_evbuf, buf, count );
if ( ret )
    {
    gnutls_transport_set_errno( p->m_tls, EAGAIN );
    return -1;
    }
return count;
}

void connection_read_cb(struct bufferevent* bev, void* arg)
{
fprintf( stderr, "read_cb\n" );
//struct connection* conn = (struct connection*)arg;
ssize_t nread = 1;
char tmp[128];
while ( nread > 0 )
    {
    nread = bufferevent_read( bev, tmp, sizeof(tmp) );   
    fwrite( tmp, nread, 1, stdout );
    fflush( stdout );
    bufferevent_write( bev, tmp, nread );
    }
}

void connection_write_cb(struct bufferevent* bev, void* arg)
{
struct connection* conn = (struct connection*)arg;
fprintf( stdout, "write_cb\n" );
bufferevent_free( conn->m_bev );
}

void connection_event_cb(struct bufferevent* bev, short events, void* arg)
{
if ( events & BEV_EVENT_EOF )
    {   
    fprintf( stderr, "close\n" );
    //close( bufferevent_getfd( bev ) );
    bufferevent_free( bev );
    }   
else
    {
    fprintf( stdout, "event!\n" );
    }
}

void connection_handshake_cb(struct bufferevent* bev, void* arg)
{
struct connection* conn = (struct connection*)arg;
struct evbuf_tls read_p;
struct evbuf_tls write_p;
read_p.m_bev = conn->m_bev;
read_p.m_evbuf = bufferevent_get_input( conn->m_bev );
read_p.m_tls = conn->m_tls;
write_p.m_bev = conn->m_bev;
write_p.m_evbuf = bufferevent_get_output( conn->m_bev );
write_p.m_tls = conn->m_tls;
gnutls_transport_set_ptr2( conn->m_tls, &read_p, &write_p );
int ret = gnutls_handshake( conn->m_tls );
switch ( ret )
    {
    case 0:
        fprintf( stdout, "bingo\n" );
        struct bufferevent* fbev = bufferevent_filter_new( bev, connection_tls_read_filter, connection_tls_write_filter, BEV_NORMAL, NULL, conn);
        bufferevent_setcb( fbev, connection_read_cb, NULL, connection_event_cb, conn );
        bufferevent_enable( bev, EV_READ | EV_WRITE );
        bufferevent_enable( fbev, EV_READ | EV_WRITE );
        char header[] = "HTTP/1.0 200 OK\r\nConnection: close\r\n\r\n";
        bufferevent_write( fbev, header, sizeof(header) );
        break;
    case GNUTLS_E_NO_PRIORITIES_WERE_SET:
        fprintf( stdout, "warn: %d\n", ret );
    case GNUTLS_E_AGAIN:
    case GNUTLS_E_INTERRUPTED:
        {
        //bufferevent_disable( bev, EV_WRITE );
        int need = EV_READ;
        if ( evbuffer_get_length( write_p.m_evbuf ) )
            need |= EV_WRITE;
        bufferevent_enable( bev, need );
        break;
        }
    default:
        if ( gnutls_error_is_fatal( ret ) )
            {
            fprintf( stderr, "fatal error: %d\n", ret );
            exit( EXIT_FAILURE );
            }
        else
            {
            fprintf( stdout, "not fatal error: %d\n", ret );
            }
    }
}

struct connection* connection_new(struct event_base* base, evutil_socket_t c)
{
fprintf( stderr, "connect!\n" );
evutil_make_socket_nonblocking( c );
//event
struct connection* conn = (struct connection*)malloc( sizeof(struct connection) );
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

struct bufferevent* bev = bufferevent_socket_new( base, c, BEV_OPT_CLOSE_ON_FREE );
conn->m_bev = bev;
bufferevent_setcb( bev, connection_handshake_cb, connection_handshake_cb, connection_event_cb, conn );
bufferevent_enable( bev, EV_READ | EV_WRITE );
return NULL;
}

