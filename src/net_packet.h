#ifndef NET_PACKETH
#define NET_PACKETH

#include <stdint.h>
#include <stddef.h>
#include "proto.h"

namespace net
{
//           packet
//--------------------------------
//|   0 1   |   2 3  |    size   |
//|get_proto|get_size|           |
//--------------------------------
//|    get_header    | get_data  |
//--------------------------------
//|            get_all           |
//--------------------------------

class header
{
protected:
uint16_t                m_proto;
uint16_t                m_size;

public:
inline                  header(const proto::enum_proto p) throw();
inline                  header(const proto::enum_proto p, const size_t size) throw();
inline  const header*   get_header() const throw();
inline  const proto     get_proto() const throw();
inline  const size_t    get_size() const throw();
inline  const char*     get_data() const throw();
};

//---- class header methods
header::header(const proto::enum_proto p) throw():
    m_proto( (uint16_t)p )
{
}

header::header(const proto::enum_proto p, const size_t size) throw():
    m_proto( (uint16_t)p ), m_size( size )
{
}

const header* header::header() const throw()
{
return this;
}

const proto header::proto() const throw()
{
return (proto::enum_proto)m_proto;
}

const size_t header::size() const throw()
{
return m_size;
}

const char* header::get_data() const throw()
{
return ((char*)this) + sizeof( header );
}

}//namespace packet
}//namespace net

#endif

