#ifndef IP_CONNECTION_H
#define IP_CONNECTION_H

#include <event2/event.h>

void connection_handshake_cb(struct bufferevent* bev, void* arg);
void connection_event_cb(struct bufferevent* bev, short events, void* arg);
void connection_write_cb(struct bufferevent* bev, void* arg);
void connection_read_cb(struct bufferevent* bev, void* arg);

#endif

