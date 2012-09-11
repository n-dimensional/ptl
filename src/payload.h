#ifndef PAYLOAD_H
#define PAYLOAD_H

#include <stddef.h>

#undef STR_
#undef STR
#define STR_(X) # X
#define STR(X) STR_(X)

#define PAYLOAD_INTERFACE_FUNC_NAME payload_interface_func

#include "core.h"

#ifdef __cplusplus
    namespace payload {
    namespace c {
    using namespace core::c;
    extern "C" {
#endif

typedef const char* payload_name_t;
typedef void*       payload_handle_t;

/* payload_interface */
typedef payload_handle_t    (*payload_init_func_t)(const core_interface_t* intreface, core_handle_t handle);
typedef payload_handle_t    (*payload_copy_func_t)(payload_handle_t handle);
typedef void                (*payload_cleanup_func_t)(payload_handle_t handle);

typedef struct
{
payload_name_t          full_name;
payload_name_t          short_name;
payload_init_func_t     init;
payload_copy_func_t     copy;
payload_cleanup_func_t  cleanup;
} payload_interface_t;
/* payload_interface */

typedef payload_interface_t*    (*payload_interface_func_t)();

#ifdef __cplusplus
    } //extern "C"
    } //namespace c
    } //namespace payload
#endif

#endif

