#include <stddef.h>

namespace ext
{

exception::exception(const char* m) throw():
    m_file( NULL ), m_line( -1 ), m_msg( m ), m_err( 0 )
{
}

exception::exception(const char* f, int l, const char* m) throw():
    m_file( f ), m_line( l ), m_msg( m ), m_err( 0 )
{
}

exception::exception(const char* f, int l, const int e) throw():
    m_file( f ), m_line( l ), m_msg( NULL ), m_err( e )
{
}

exception::exception(const char* f, int l, const char* m, const int e) throw():
    m_file( f ), m_line( l ), m_msg( m ), m_err( e )
{
}

const char* exception::file() const throw()
{
return m_file;
}

const int exception::line() const throw()
{
return m_line;
}

const char* exception::what() const throw()
{
return m_msg;
}

const int exception::err() const throw()
{
return m_err;
}

}//namespace exception

std::ostream& operator << (std::ostream& os, const ext::exception& e)
{
if ( e.file() )
    os << e.file();
if ( -1 != e.line() )
    os << ':' << e.line();
if ( e.what() )
    os << ": " << e.what();
return os;
}

