#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <stddef.h>

#undef STR_
#undef STR
#define STR_(X) # X
#define STR(X) STR_(X)

#define TRANSPORT_INTERFACE_FUNC_NAME transport_interface_func
#define TRANSPORT_COUNT_FUNC_NAME transport_count_func

#include "core.h"

#ifdef __cplusplus
    namespace transport {
    namespace c {
    using namespace core::c;
    extern "C" {
#endif

typedef void*       transport_handle_t;
typedef void*       transport_storage_handle_t;
typedef void*       transport_storage_iterator_t;
typedef void*       transport_connection_handle_t;
typedef const char* transport_name_t;

/* core begin */
typedef char        key_hash_t[32];
typedef char*       addr_t;
/* core end */

/* connection begin */
typedef void (*transport_connection_listen_func_t)(const transport_handle_t transport, const addr_t addr, size_t size);
typedef void (*transport_connection_connect_func_t)(const transport_handle_t transport, const addr_t addr, size_t size);
typedef void (*transport_connection_close_func_t)(const transport_connection_handle_t connection);

typedef struct
{
transport_connection_listen_func_t  listen;
transport_connection_connect_func_t connect;
transport_connection_close_func_t   close;
} transport_connection_interface_t;
/* connection end */

/* storage iterator */
typedef transport_storage_iterator_t    (*transport_storage_iterator_copy_func_t)(const transport_storage_iterator_t it);
typedef transport_storage_iterator_t    (*transport_storage_iterator_del_func_t)(transport_storage_iterator_t it);
typedef int                             (*transport_storage_iterator_eq_func_t)(const transport_storage_iterator_t rvalue, const transport_storage_iterator_t lvalue);
typedef void                            (*transport_storage_iterator_next_func_t)(transport_storage_iterator_t it);
typedef const addr_t                    (*transport_storage_iterator_get_func_t)(const transport_storage_iterator_t it);
typedef size_t                          (*transport_storage_iterator_size_func_t)(const transport_storage_iterator_t it);
typedef void                            (*transport_storage_iterator_set_func_t)(transport_storage_iterator_t it, const addr_t addr, size_t size);

typedef struct 
{
transport_storage_iterator_copy_func_t  copy;
transport_storage_iterator_del_func_t   del;
transport_storage_iterator_eq_func_t    eq;
transport_storage_iterator_next_func_t  next;
transport_storage_iterator_get_func_t   get;
transport_storage_iterator_size_func_t  size;
transport_storage_iterator_set_func_t   set;
} transport_storage_iterator_interface_t;
/* storage iterator end */

/* storage begin */
typedef transport_storage_iterator_t    (*transport_storage_insert_func_t)(transport_storage_handle_t storage, key_hash_t id, const addr_t* addr, size_t size);
typedef transport_storage_iterator_t    (*transport_storage_find_func_t)(const transport_storage_handle_t storage, key_hash_t id);
typedef void                            (*transport_storage_delete_func_t)(transport_storage_handle_t storage, transport_storage_iterator_t it);
typedef transport_storage_iterator_t    (*transport_storage_begin_func_t)(const transport_storage_handle_t storage);
typedef transport_storage_iterator_t    (*transport_storage_end_func_t)(const transport_storage_handle_t storage);

typedef struct
{
transport_storage_insert_func_t insert;
transport_storage_find_func_t   find;
transport_storage_delete_func_t del;
transport_storage_begin_func_t  begin;
transport_storage_end_func_t    end;
} transport_storage_interface_t;
/* storage end */

/* transport begin */
typedef transport_handle_t  (*transport_init_func_t)(const core_interface_t* interface, core_handle_t handle);
typedef transport_handle_t  (*transport_copy_func_t)(transport_handle_t transport);
typedef void                (*transport_cleanup_func_t)(transport_handle_t transport);

typedef struct
{
transport_name_t                    full_name;
transport_name_t                    short_name;
transport_init_func_t               init;
transport_copy_func_t               copy;
transport_cleanup_func_t            cleanup;
transport_connection_interface_t    connection;
} transport_interface_t;
/* transport end */

typedef size_t                  transport_count_t;
typedef transport_count_t       (*transport_count_func_t)();
typedef transport_interface_t*  (*transport_interface_func_t)();

#ifdef __cplusplus
    } //extern "C"
    } //namespace c
    } //namespace transport
#endif

#endif

