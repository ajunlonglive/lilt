/*
  +----------------------------------------------------------------------+
  | lilt                                                                 |
  +----------------------------------------------------------------------+
  | Copyright (c) Abel Lucas 2016                                        |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Abel Lucas <ylilt71@gmail.com>                               |
  +----------------------------------------------------------------------+
 */

#ifndef CLASS
#   error You have to define CLASS before including that header
#else
#   define INIT EXT_CLASS_INIT(CLASS)
#   define INIT_FUNCTION EXT_CLASS_INIT_FUNCTION(CLASS)
#   ifdef CLASS_NAME
#       define CLASS_STR CLASS_NAME
#   else
#       define CLASS_STR EXT_CLASS_STR(CLASS)
#   endif
#   define CE EXT_CLASS_CE(CLASS)
#   define CLASS_ENTRY EXT_CLASS_CLASS_ENTRY(CLASS)
#   define CEINIT EXT_CLASS_CEINIT(CLASS)
#   define CEINIT_FUNCTION EXT_CLASS_CEINIT_FUNCTION(CLASS)
#   define OH EXT_CLASS_OH(CLASS)
#   define OBJECT_HANDLERS EXT_CLASS_OBJECT_HANDLERS(CLASS)
#   define OHINIT EXT_CLASS_OHINIT(CLASS)
#   define OHINIT_FUNCTION EXT_CLASS_OHINIT_FUNCTION(CLASS)
#   define STRUCT EXT_CLASS_STRUCT(CLASS)
#   define PHP_STRUCT EXT_CLASS_PHP_STRUCT(CLASS)
#   define STRUCT_BEGIN EXT_CLASS_STRUCT_BEGIN(CLASS)
#   define STRUCT_END EXT_CLASS_STRUCT_END(CLASS)
#   define PHP_STRUCT_BEGIN EXT_CLASS_PHP_STRUCT_BEGIN(CLASS)
#   define PHP_STRUCT_END EXT_CLASS_PHP_STRUCT_END(CLASS)
#   ifdef CUSTOM_STRUCT
#       define Z_THIS(z) EXT_CLASS_CUSTOM_Z_THIS(CLASS, z)
#       define Z_THIS_P(z) EXT_CLASS_CUSTOM_Z_THIS_P(CLASS, z)
#       define $this EXT_CLASS_CUSTOM_THIS(CLASS)
#       define INIT_THIS EXT_CLASS_INIT_CUSTOM_THIS(CLASS)
#   else
#       define Z_THIS(z) EXT_CLASS_Z_THIS(CLASS, z)
#       define Z_THIS_P(z) EXT_CLASS_Z_THIS_P(CLASS, z)
#       define $this EXT_CLASS_THIS(CLASS)
#       define INIT_THIS EXT_CLASS_INIT_THIS(CLASS)
#   endif
#   define METHODS EXT_CLASS_METHODS(CLASS)
#   define NO_METHODS EXT_CLASS_NO_METHODS(CLASS)
#   define METHODS_BEGIN EXT_CLASS_METHODS_BEGIN(CLASS)
#   define METHOD(name) EXT_CLASS_METHOD(CLASS, name)
#   define ME(name, flags) EXT_CLASS_ME(CLASS, name, flags)
#   define ABSTRACT_ME(name, arginfo, flags) EXT_CLASS_ABSTRACT_ME(name, arginfo, flags)
#   define MAGIC_ME(name, arginfo, flags) EXT_CLASS_MAGIC_ME(name, arginfo, flags)
#   define CTOR EXT_CLASS_CTOR(CLASS)
#   define MEM(name) EXT_CLASS_MEM(CLASS, name)
#   define FUNC(name, ...) EXT_CLASS_FUNC(CLASS, name, __VA_ARGS__)
#   define INIT_CLASS EXT_CLASS_INIT_CLASS(CLASS, CLASS_STR)
#   define INIT_INTERFACE EXT_CLASS_INIT_INTERFACE(CLASS, CLASS_STR)
#   ifdef CUSTOM_STRUCT
#       define INIT_HANDLERS EXT_CLASS_INIT_HANDLERS_CUSTOM_STRUCT(CLASS)
#   else
#       define INIT_HANDLERS EXT_CLASS_INIT_HANDLERS(CLASS)
#   endif
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */