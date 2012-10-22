#include <dlfcn.h>
#include "unix_lib.h"

namespace abstract
{

lib_t lib_open(const char* libname)
{
return dlopen( libname, RTLD_LAZY );
}

func_t lib_sym(lib_t lib, const char* funcname)
{
return dlsym( lib, funcname );
}

int lib_close(lib_t lib)
{
return dlclose( lib );
}

char* lib_error()
{
return dlerror();
}

} //namespace abstract

