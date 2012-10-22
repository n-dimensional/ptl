#ifndef MODULE_HPP
#define MODULE_HPP

#include <stdint.h>
#include <ptl/module.h>

namespace module
{
typedef ::module_api_version_t  api_version_t;
typedef ::module_info_func_t    info_func_t;

enum version_hack
{
api_version = MODULE_API_VERSION
};

namespace type
{
enum type_t
{
transport   = MODULE_TYPE_TRANSPORT,
payload     = MODULE_TYPE_PAYLOAD
};
} //namespace type

using type::type_t;

struct info_t
{
api_version_t   api_version;
type_t          type;
inline  info_t(const api_version_t version, const type_t type);
inline  info_t(const module_info_t& info);
};

} //namespace module

#include <ptl/module.inc>

#endif

