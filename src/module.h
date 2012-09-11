#ifndef MODULE_H
#define MODULE_H

#include <stdint.h>

#undef STR_
#undef STR
#define STR_(X) # X
#define STR(X) STR_(X)

#define MODULE_INFO_FUNC_NAME module_info_func
#define MODULE_API_VERSION 0x00000001

#ifdef __cplusplus
extern "C"
{
#endif

typedef uint32_t module_api_version_t;
enum module_type_t
{
MODULE_TYPE_TRANSPORT,
MODULE_TYPE_PAYLOAD
};

struct module_info_t
{
module_api_version_t    api_version;
enum module_type_t      type;
};

typedef struct module_info_t (*module_info_func_t)();

#ifdef __cplusplus
} //extern "C"
#endif

#endif

