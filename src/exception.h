#ifndef EXT_EXCEPTIONH
#define EXT_EXCEPTIONH

#include <ostream>
#include <exception>
#define EXCEPTION(...) exception(__FILE__,__LINE__,__VA_ARGS__)

namespace ext
{

class exception:
    public std::exception
{
protected:
const char* m_file;
const int   m_line;

const char* m_msg;
const int   m_err;

public:
inline              exception(const char* m) throw();
inline              exception(const char* f, int l, const char* m) throw();
inline              exception(const char* f, int l, const int e) throw();
inline              exception(const char* f, int l, const char* m, const int e) throw();
inline  const char* file() const throw();
inline  const int   line() const throw();
inline  const char* what() const throw();
inline  const int   err()  const throw();
};

}//namespace ext

inline std::ostream& operator << (std::ostream& os, const ext::exception& e);

#include "exception.inc"

#endif

