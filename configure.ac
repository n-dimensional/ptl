AC_INIT([ptl],[0.1])
AM_INIT_AUTOMAKE([ptl],[0.1])
AC_CONFIG_MACRO_DIR([m4])
: ${CXXFLAGS=""}
AC_C_INLINE
AC_PROG_CXX
AC_PROG_LIBTOOL

AC_ARG_ENABLE([debug],[AS_HELP_STRING(--enable-debug,enable debug)])
if [ test "_$enable_debug" = "_yes" ]; then
    CXXFLAGS="-O0 -g ${CXXFLAGS}"
    fi

AC_CONFIG_HEADERS(src/config.h)
AC_CONFIG_FILES([Makefile])
AC_OUTPUT

