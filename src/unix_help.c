#include "unix_help.h"

void help(FILE* os, int argc, char* argv[])
{
fprintf( os, "usage: %s -hvD [-c config] [-d|--debug[=debuglevel]]\n", argv[0] );
fprintf( os, "-h --help                 show this message\n" );
fprintf( os, "-v --version              show version\n" );
fprintf( os, "-c --config <file>        set config file name\n" );
fprintf( os, "-d --debug[=debug level]  enable debug level\n" );
fprintf( os, "-D --demon                do demonize\n" );
}

