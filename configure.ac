AC_INIT([ptl],[0.1])
AM_INIT_AUTOMAKE([ptl],[0.1])
AC_CONFIG_MACRO_DIR([m4])
m4_include([m4/acx_pthread.m4])
: ${CFLAGS="-Wall"}
: ${CPPFLAGS="-Wall"}
AC_C_INLINE
AC_PROG_CXX
AC_PROG_LIBTOOL
ACX_PTHREAD([AC_SUBST(SYSLOGPP_LIBS,"-lsyslogpp_r")],[AC_SUBST(SYSLOGPP_LIBS,"-lsyslogpp")])
AC_CHECK_LIB([dl], [dlopen], [AC_SUBST(DL_LIBS,"-ldl")])

AC_ARG_ENABLE([debug],[AS_HELP_STRING(--enable-debug,enable debug)])
if [ test "_$enable_debug" = "_yes" ]; then
    CPPFLAGS="-O0 -g ${CPPFLAGS}"
    fi

AH_TEMPLATE([DLEXT],[Dynamic library filename extension])
AC_DEFINE([DLEXT],[".so"])
AC_CONFIG_HEADERS(src/config.h)
AC_CONFIG_FILES([Makefile])
AC_OUTPUT

