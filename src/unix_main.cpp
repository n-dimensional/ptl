#include <getopt.h>
#include <cstring>
#include <cstdlib>
#include <cstdio>

#include <syslog.h>
#include <syslogpp.h>

#include "unix_help.h"
#include "ptl_main.hpp"

const static char options[] = "hvc:d?D";
const static struct option long_options[] = {
    { "help",       0,  0,  'h' },
    { "version",    0,  0,  'v' },
    { "config",     1,  0,  'c' },
    { "debug",      2,  0,  'd' },
    { "daemon",     0,  0,  'D' },
    { NULL,         0,  0,   0  }
    };

const char* p_cfg_filename = "ptld.cfg"; //TODO: prefix
int         p_daemon = 0;
int         p_debug = 0;

int main(int argc, char* argv[])
{
int option_index;
while( true )
    {
    int option = getopt_long( argc, argv, options, long_options, &option_index );
    if ( -1 == option )
        break;
    switch( option )
        {
        case 'h':
            help( stdout, argc, argv );
            exit( EXIT_SUCCESS );
        case 'v':
            //TODO: version()
            break;
        case 'c':
            p_cfg_filename = strdup( optarg );
            break;
        case 'd':
            if ( NULL == optarg )
                p_debug = -1;
            else
                p_debug = atoi( optarg ); //TODO: strtol
            break;
        case 'D':
            {
            int ret = daemon( 1, 0 ); //TODO: retcode
            if ( 0 != ret )
                exit( EXIT_FAILURE );
            p_daemon = 1;
            }
            break;
        default:
            help( stderr, argc, argv );
            exit( EXIT_FAILURE );
        }
    }

int syslog_option = p_debug? LOG_PERROR : LOG_PID;
int syslog_facility = p_daemon? LOG_DAEMON : LOG_USER;
syslog.open( NULL, syslog_option, syslog_facility );

pugi::xml_document doc;
pugi::xml_parse_result result = doc.load_file( p_cfg_filename );
pugi::xml_node first = doc.first_child();
if ( !result || !first )
    {   
    syslog( LOG_ALERT, "file not found or invalid xml format" );
    return EXIT_FAILURE;
    }   
ptl_main( first, false );
syslog.close();
return EXIT_SUCCESS;
}

