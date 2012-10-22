#ifndef ABSTRACT_LIB_H
#define ABSTRACT_LIB_H

#ifdef HAVE_CONFIG_H
    #include "config.h"
#endif

#ifdef HAVE_DLFCN_H
    #include "unix_lib.h"
#else
    #include "win_lib.h"
#endif

namespace abstract
{
lib_t   lib_open(const char* libname);
func_t  lib_sym(lib_t lib, const char* funcname);
int     lib_close(lib_t lib); //zero = success
char*   lib_error();
} //namespace abstract

#endif

