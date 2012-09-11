ACLOCAL_AMFLAGS = -I m4
bin_PROGRAMS = ptld
PUGIXML_CFLAGS=-Ipugixml/src
PTHREAD_CFLAGS=@PTHREAD_CFLAGS@
AM_CFLAGS=@CFLAGS@ $(PTHREAD_CFLAGS) $(PUGIXML_CFLAGS)
AM_CPPFLAGS=@CPPFLAGS@ $(PTHREAD_CFLAGS) $(PUGIXML_CFLAGS)
CSOURCES = src/unix_help.c 
CPPSOURCES =
EFFSOURCES = src/ptl_main.cpp src/unix_lib.cpp src/event_pool.cpp src/core.cpp
EXTSOURCES = pugixml/src/pugixml.cpp
SOURCES = $(CSOURCES) $(CPPSOURCES) $(EFFSOURCES) $(EXTSOURCES)
LIBS = @DL_LIBS@ @SYSLOGPP_LIBS@ @PTHREAD_LIBS@ @LIBS@ @LDFLAGS@ $(PTHREAD_CFLAGS)

ptld_SOURCES = $(SOURCES) src/unix_main.cpp
ptld_LDADD = 

plugindir = $(prefix)/share/ptl/
plugin_LTLIBRARIES = ip.la base.la
base_la_SOURCES = src/modules/base/base.cpp
base_la_LDFLAGS = -module -avoid-version -shared
ip_la_SOURCES = src/modules/ip/ip.c src/modules/ip/tcp.c src/modules/ip/connection.c
ip_la_LDFLAGS = -module -avoid-version -shared

$(EFFSOURCES:src/%.cpp=%.$(OBJEXT)): CPPFLAGS += -Weffc++

