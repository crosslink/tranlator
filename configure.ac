#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.63])
AC_INIT([corpus-translator], [0.1], [lingxiang.tang@gmailc.om])
AC_CONFIG_SRCDIR([src/thread_master.h])
#AC_CONFIG_HEADERS([config.h])

LT_INIT

AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])

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
