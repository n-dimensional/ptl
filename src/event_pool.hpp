#ifndef EVENT_POOL_HPP
#define EVENT_POOL_HPP

#include <vector>

#include <pugixml.hpp>
#include <event2/event.h>

namespace core
{

class event_pool_t:
    protected std::vector<struct event_base*>
{
public:
typedef std::vector<struct event_base*> base;

            event_pool_t();
            ~event_pool_t();
void        run(bool nonblock);
void        resize(uint32_t size);
using       base::operator [];
using       base::size;

event_base* get();
};

} //namespace event

#endif

