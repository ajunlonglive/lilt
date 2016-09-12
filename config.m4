PHP_ARG_ENABLE(lilt, whether to enable lilt support,
[  --enable-lilt           Enable lilt support])

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
  src/typed_ce.c \
  src/functions.c \
  src/handlers.c \
  \
  , $ext_shared, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)

  PHP_ADD_BUILD_DIR($ext_builddir/src, 1)
  PHP_ADD_INCLUDE($ext_builddir/lib)
  PHP_ADD_INCLUDE($ext_builddir)

  PHP_ADD_EXTENSION_DEP(lilt, reflection)
  PHP_ADD_EXTENSION_DEP(lilt, spl)
fi