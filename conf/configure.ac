dnl                                               -*- Autoconf -*-
dnl Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT(main.c, 0.0.1, [BUG-REPORT-ADDRESS])

dnl Nosso projeto é escrito em C
AC_LANG(C)

dnl Diretório para os arquivos-fonte
AC_CONFIG_SRCDIR([src])
dnl AC_CONFIG_HEADERS([include/*.h])

dnl Checks for programs.
AC_PROG_CC
AC_PROG_SED

dnl Checks for libraries.
dnl FIXME: Replace `main' with a function in `-lc':
dnl AC_CHECK_LIB([c], [main])
dnl FIXME: Replace `main' with a function in `-lm':
AC_CHECK_LIB([m], sqrt)
AC_CHECK_LIB([lib/stat],[stat_set_seed])

dnl Procura pela ferramenta 'make'
AC_PROG_MAKE_SET

dnl Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([include/*.h])

dnl Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

dnl Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([sqrt])

AC_CONFIG_FILES([makefile])
AC_OUTPUT
