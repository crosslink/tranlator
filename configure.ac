#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.63])
AC_INIT([corpus-translator], [0.7], [lingxiang.tang@gmailc.om])
AC_CONFIG_SRCDIR([src/thread_master.h])
#AC_CONFIG_HEADERS([config.h])

LT_INIT

AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.
AC_ARG_WITH([mysql-lib-path],
  [AS_HELP_STRING([--with-mysql-lib-path], [location of the MySQL libraries])],
  [MYSQL_LIBS="-L$withval -lmysqlclient"],
  [MYSQL_LIBS='-lmysqlclient'])
AC_SUBST([MYSQL_LIBS])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])

# Get MySQL library and include locations
AC_ARG_WITH([mysql-include-path],
  [AS_HELP_STRING([--with-mysql-include-path],
    [location of the MySQL headers, defaults to /usr/include/mysql])],
  [MYSQL_CFLAGS="-I$withval"],
  [MYSQL_CFLAGS='-I/usr/include/mysql'])
AC_SUBST([MYSQL_CFLAGS])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([strchr strstr strtol])

AC_CONFIG_FILES([
                 Makefile
                ])
AC_OUTPUT
