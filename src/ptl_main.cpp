#include <stdlib.h>
#include <cstring>

#include <syslog.h>
#include <syslogpp.h>

#include "ptl_main.hpp"
#include "core.hpp"

int ptl_main(const pugi::xml_node& cfg, bool nonblock)
{
syslog( LOG_NOTICE, "starting..." );
core::core_t core( cfg );
core.run( nonblock );
syslog( LOG_NOTICE, "stopping..." );
return EXIT_SUCCESS;
}

