PHP_ARG_ENABLE(lilt, whether to enable lilt support,
[  --enable-lilt           Enable lilt support])

if test "$PHP_LILT" != "no"; then
  PHP_NEW_EXTENSION(lilt, \
  \
  ext/src/lilt.c \
  ext/src/arg_info.c \
  ext/src/arg_info_ce.c \
  ext/src/arg_info_oh.c \
  ext/src/constant.c \
  ext/src/constant_ce.c \
  ext/src/constant_oh.c \
  ext/src/function.c \
  ext/src/function_ce.c \
  ext/src/function_oh.c \
  ext/src/property.c \
  ext/src/property_ce.c \
  ext/src/property_oh.c \
  ext/src/type.c \
  ext/src/type_ce.c \
  ext/src/type_oh.c \
  ext/src/typed.c \
  ext/src/typed_ce.c \
  ext/src/functions.c \
  ext/src/handlers.c \
  \
  , $ext_shared, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)

  PHP_ADD_BUILD_DIR($ext_builddir/ext/src, 1)
  PHP_ADD_INCLUDE($ext_builddir/ext)
  PHP_ADD_INCLUDE($ext_builddir/ext/lib)

  PHP_ADD_EXTENSION_DEP(lilt, reflection)
  PHP_ADD_EXTENSION_DEP(lilt, spl)
fi