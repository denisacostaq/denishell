AC_PREREQ(2.69)
AC_INIT([denishell], [0.0.0], [denisacostaq@gmail.com], [denishell], [https://github.com/denisacostaq/denishell])

AM_INIT_AUTOMAKE([1.14])

AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

AC_CANONICAL_HOST
AC_CANONICAL_BUILD

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_AWK
AC_PROG_CPP
AC_PROG_MKDIR_P
#AC_PROG_INTLTOOL([0.50.2-2])


# Checks for libraries.
#PKG_CHECK_MODULES(AA, [glib-2.0 >= 2.36.4])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h unistd.h locale.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([setlocale])


# i18n
#--------------------------
GETTEXT_PACKAGE=MY_SHELL
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE",[The gettext package])
ALL_LINGUAS="es us"
#AM_GLIB_GNU_GETTEXT




AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
