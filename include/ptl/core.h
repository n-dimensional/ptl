#ifndef CORE_H
#define CORE_H

#include <event2/event.h>

#ifdef __cplusplus
    namespace core {
    namespace c {
    extern "C" {
#endif

typedef void*   core_handle_t;
typedef core_handle_t   (*core_copy_func_t)(core_handle_t handle);
typedef void            (*core_cleanup_func_t)(core_handle_t handle);

typedef struct event_base*  (*core_get_event_base_func_t)(core_handle_t handle);

typedef struct
{
core_copy_func_t            copy;
core_cleanup_func_t         cleanup;

core_get_event_base_func_t  get_event_base;
} core_interface_t;

#ifdef __cplusplus
    } //ectern "C"
    } //namespace c
    } //namespace core
#endif

#endif

