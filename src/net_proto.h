#ifndef NET_PROTOH
#define NET_PROTOH

namespace net
{

class proto
{
public:
enum enum_proto
    {
    //0-255 reserved by system
    system_0 = 0,
    //...
    system_255 = 255,
    vote_0
    };
enum_proto  m_proto;

inline  proto(const enum_proto p) throw();
inline  operator enum_proto& () throw();
inline  operator const enum_proto& () const throw();
};

proto::proto(const enum_proto p) throw():
    m_proto( p )
{
}

proto::operator enum_proto& () throw()
{
return m_proto;
}

proto::operator const enum_proto& () const throw()
{
return m_proto;
}

}//namespace net

#endif

