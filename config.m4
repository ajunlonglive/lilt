PHP_ARG_ENABLE(lilt, whether to enable lilt support,
[  --enable-lilt           Enable lilt support])

AC_MSG_CHECKING([for C11 support with -std=c11])
old_CFLAGS="$CFLAGS"
CFLAGS="${CFLAGS} -std=c11"
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([],[])],[AC_MSG_RESULT([yes])],[
	AC_MSG_RESULT([no])
	CFLAGS="$old_CFLAGS"
	echo "===== WARNING ============================================"
	echo "  lilt is written in C11, but your compiler lacks C11"
	echo "  support. Trying C99 instead, but compiling may fail."
	echo "=========================================================="
	AC_MSG_CHECKING([for C99 support with -std=c99])
	CFLAGS="${CFLAGS} -std=c99"
	AC_COMPILE_IFELSE([AC_LANG_PROGRAM([],[])],[AC_MSG_RESULT([yes])],[
		AC_MSG_RESULT([no])
		CFLAGS="$old_CFLAGS"
	])
])

if test "$PHP_LILT" != "no"; then
  PHP_NEW_EXTENSION(lilt, \
  \
  src/lilt.c \
  src/arg_info.c \
  src/arg_info_ce.c \
  src/arg_info_oh.c \
  src/constant.c \
  src/constant_ce.c \
  src/constant_oh.c \
  src/function.c \
  src/function_ce.c \
  src/function_oh.c \
  src/property.c \
  src/property_ce.c \
  src/property_oh.c \
  src/type.c \
  src/type_ce.c \
  src/type_oh.c \
  src/typed.c \
  src/i_static_init.c \
  src/functions.c \
  src/handlers.c \
  \
  , $ext_shared, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)

  PHP_ADD_BUILD_DIR($ext_builddir/src, 1)
  PHP_ADD_INCLUDE($ext_builddir/lib)
  PHP_ADD_INCLUDE($ext_builddir)
fi