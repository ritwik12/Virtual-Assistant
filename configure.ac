AC_INIT(virtual_assistant, git, [noone@localhost])
AM_INIT_AUTOMAKE([subdir-objects])
AC_PREREQ(2.69)
AC_CONFIG_HEADERS([config.h:config.in])
AC_PROG_CC([cc])
AC_CONFIG_MACRO_DIRS([m4])
AC_PROG_LIBTOOL
AC_PROG_INSTALL
AM_PROG_CC_C_O

AC_CHECK_LIB([json], [json_tokener_parse], found_json=yes, found_json=no)
if test "x$found_json" = xyes; then
  LDFLAGS=" -ljson"
fi

if test "x$found_json" = xno; then
  AC_CHECK_LIB([json-c], [json_tokener_parse], found_json_c=yes, found_json_c=no)
  if test "x$found_json_c" = xyes; then
    LDFLAGS="-ljson-c"
  else
    AC_MSG_ERROR("required json library not found. Please install libjson0-dev")
  fi
fi

AC_OUTPUT(Makefile)
