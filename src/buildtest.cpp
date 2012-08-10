#include <syslog.h>
#include <syslogpp.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
syslog << "test" << std::endl;
return EXIT_SUCCESS;
}

