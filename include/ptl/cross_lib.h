#ifndef ABSTRACT_LIB_HPP
#define ABSTRACT_LIB_HPP

namespace abstract
{
typedef void* lib_t;
typedef void* func_t;

lib_t   lib_open(const char* libname);
int     lib_close(lib_t lib); //zero = success
char*   lib_error();
func_t  lib_sym(lib_t lib, const char* funcname);
template <class T>
T       lib_sym(lib_t lib, const char* funcname)
    {
    return reinterpret_cast<T>( lib_sym( lib, funcname ) );
    }
} //namespace abstract

#endif

