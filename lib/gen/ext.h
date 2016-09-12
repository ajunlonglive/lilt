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

#ifndef LILT_GEN_EXT_H
#define LILT_GEN_EXT_H

#if !defined(EXT_NAME) || !defined(EXT_NAME_UC) || !defined(EXT_VERSION)
#error You have to define EXT_NAME & EXT_VERSION before including that header
#else

#define EXT_ME EXT_ME_NX(EXT_NAME)
#define EXT_MODULE_ENTRY EXT_MODULE_ENTRY_NX(EXT_NAME)
#define EXT_EXTERN_MODULE_ENTRY EXT_EXTERN_MODULE_ENTRY_NX(EXT_NAME)
#define EXT_MG EXT_MG_NX(EXT_NAME)
#define EXT_MGSTRUCT EXT_MGSTRUCT_NX(EXT_NAME)
#define EXT_EXTERN_MODULE_GLOBALS EXT_EXTERN_MODULE_GLOBALS_NX(EXT_NAME)
#define EXT_BEGIN_MODULE_GLOBALS EXT_BEGIN_MODULE_GLOBALS_NX(EXT_NAME)
#define EXT_END_MODULE_GLOBALS EXT_END_MODULE_GLOBALS_NX(EXT_NAME)
#define EXT_MEMSET_GLOBALS EXT_MEMSET_GLOBALS_NX(EXT_NAME)
#define EXT_MODULE_GLOBALS EXT_MODULE_GLOBALS_NX(EXT_NAME)
#define EXT_MGINIT EXT_MGINIT_NX(EXT_NAME)
#define EXT_MGINIT_FUNCTION EXT_MGINIT_FUNCTION_NX(EXT_NAME)
#define EXT_GINIT EXT_GINIT_NX(EXT_NAME)
#define EXT_GINIT_FUNCTION EXT_GINIT_FUNCTION_NX(EXT_NAME)
#define EXT_MINIT EXT_MINIT_NX(EXT_NAME)
#define EXT_MINIT_FUNCTION EXT_MINIT_FUNCTION_NX(EXT_NAME)
#define EXT_MSHUTDOWN EXT_MSHUTDOWN_NX(EXT_NAME)
#define EXT_MSHUTDOWN_FUNCTION EXT_MSHUTDOWN_FUNCTION_NX(EXT_NAME)
#define EXT_RINIT EXT_RINIT_NX(EXT_NAME)
#define EXT_RINIT_FUNCTION EXT_RINIT_FUNCTION_NX(EXT_NAME)
#define EXT_RSHUTDOWN EXT_RSHUTDOWN_NX(EXT_NAME)
#define EXT_RSHUTDOWN_FUNCTION EXT_RSHUTDOWN_FUNCTION_NX(EXT_NAME)
#define EXT_MINFO EXT_MINFO_NX(EXT_NAME)
#define EXT_MINFO_FUNCTION EXT_MINFO_FUNCTION_NX(EXT_NAME)
#define EXT_DEPS EXT_DEPS_NX(EXT_NAME)
#define EXT_DEPS_TABLE EXT_DEPS_TABLE_NX(EXT_NAME)
#define EXT_FUNCTIONS EXT_FUNCTIONS_NX(EXT_NAME)
#define EXT_FUNCTIONS_TABLE EXT_FUNCTIONS_TABLE_NX(EXT_NAME)
#define EXT_MINFO_BODY EXT_MINFO_BODY_NX(EXT_NAME, EXT_VERSION)
#define EXT_MODULE_PROPERTIES EXT_MODULE_PROPERTIES_NX(EXT_NAME, EXT_VERSION)

#define EXT_HINIT EXT_HINIT_NX(EXT_NAME)
#define EXT_HINIT_FUNCTION EXT_HINIT_FUNCTION_NX(EXT_NAME)
#define EXT_HFREE EXT_HFREE_NX(EXT_NAME)
#define EXT_HFREE_FUNCTION EXT_HFREE_FUNCTION_NX(EXT_NAME)
#define EXT_HANDLER(opcode) EXT_HANDLER_NX(EXT_NAME, opcode)
#define EXT_DFT_HANDLER(opcode) EXT_DFT_HANDLER_NX(EXT_NAME, opcode)
#define EXT_DFT_HANDLER_DECLARE(opcode) EXT_DFT_HANDLER_DECLARE_NX(EXT_NAME, opcode)
#define EXT_HANDLER_FUNCTION(opcode) EXT_HANDLER_FUNCTION_NX(EXT_NAME, opcode)
#define EXT_SET_HANDLER(opcode) EXT_SET_HANDLER_NX(EXT_NAME, opcode)
#define EXT_UNSET_HANDLER(opcode) EXT_UNSET_HANDLER_NX(EXT_NAME, opcode)

#define EXT_CLASS_INIT(class) EXT_CLASS_INIT_NX(EXT_NAME, class)
#define EXT_CLASS_INIT_FUNCTION(class) EXT_CLASS_INIT_FUNCTION_NX(EXT_NAME, class)
#define EXT_CLASS_STR(class) STRINGIZE(class)
#define EXT_CLASS_NS(ns_underscored, class) CONCAT(ns_underscored, _, class)
#define EXT_CLASS_NS_STR(nsname, class) PHP_NSIZE(nsname, EXT_CLASS_STR(class))
#define EXT_CLASS_CE(class) EXT_CLASS_CE_NX(EXT_NAME, class)
#define EXT_CLASS_CLASS_ENTRY(class) EXT_CLASS_CLASS_ENTRY_NX(EXT_NAME, class)
#define EXT_CLASS_CEINIT(class) EXT_CLASS_CEINIT_NX(EXT_NAME, class)
#define EXT_CLASS_CEINIT_FUNCTION(class) EXT_CLASS_CEINIT_FUNCTION_NX(EXT_NAME, class)
#define EXT_CLASS_OH(class) EXT_CLASS_OH_NX(EXT_NAME, class)
#define EXT_CLASS_OBJECT_HANDLERS(class) EXT_CLASS_OBJECT_HANDLERS_NX(EXT_NAME, class)
#define EXT_CLASS_OHINIT(class) EXT_CLASS_OHINIT_NX(EXT_NAME, class)
#define EXT_CLASS_OHINIT_FUNCTION(class) EXT_CLASS_OHINIT_FUNCTION_NX(EXT_NAME, class)
#define EXT_CLASS_STRUCT(class) EXT_CLASS_STRUCT_NX(EXT_NAME, class)
#define EXT_CLASS_PHP_STRUCT(class) EXT_CLASS_PHP_STRUCT_NX(EXT_NAME, class)
#define EXT_CLASS_STRUCT_BEGIN(class) EXT_CLASS_STRUCT_BEGIN_NX(EXT_NAME, class)
#define EXT_CLASS_STRUCT_END(class) EXT_CLASS_STRUCT_END_NX(EXT_NAME, class)
#define EXT_CLASS_PHP_STRUCT_BEGIN(class) EXT_CLASS_PHP_STRUCT_BEGIN_NX(EXT_NAME, class)
#define EXT_CLASS_PHP_STRUCT_END(class) EXT_CLASS_PHP_STRUCT_END_NX(EXT_NAME, class)
#define EXT_CLASS_CUSTOM_Z_THIS(class, z) EXT_CLASS_CUSTOM_Z_THIS_NX(EXT_NAME, class, z)
#define EXT_CLASS_CUSTOM_Z_THIS_P(class, z) EXT_CLASS_CUSTOM_Z_THIS_P_NX(EXT_NAME, class, z)
#define EXT_CLASS_CUSTOM_THIS(class) EXT_CLASS_CUSTOM_THIS_NX(EXT_NAME, class)
#define EXT_CLASS_INIT_CUSTOM_THIS(class) EXT_CLASS_INIT_CUSTOM_THIS_NX(EXT_NAME, class)
#define EXT_CLASS_METHODS(class) EXT_CLASS_METHODS_NX(EXT_NAME, class)
#define EXT_CLASS_METHODS_BEGIN(class) EXT_CLASS_METHODS_BEGIN_NX(EXT_NAME, class)
#define EXT_CLASS_METHOD(class, name) EXT_CLASS_METHOD_NX(EXT_NAME, class, name)
#define EXT_CLASS_ME(class, name, arginfo, flags) EXT_CLASS_ME_NX(EXT_NAME, class, name, arginfo, flags)
#define EXT_CLASS_ABSTRACT_ME(name, arginfo, flags) EXT_CLASS_ABSTRACT_ME_NX(name, arginfo, flags)
#define EXT_CLASS_MAGIC_ME(name, arginfo, flags) EXT_CLASS_MAGIC_ME_NX(name, arginfo, flags)
#define EXT_CLASS_CTOR(class) EXT_CLASS_CTOR_NX(EXT_NAME, class)
#define EXT_CLASS_MEM(class, name) EXT_CLASS_MEM_NX(EXT_NAME, class, name)
#define EXT_CLASS_FUNC(class, name, ...) EXT_CLASS_FUNC_NX(EXT_NAME, class, name, __VA_ARGS__)
#define EXT_CLASS_INIT_CLASS(class, classname) EXT_CLASS_INIT_CLASS_NX(EXT_NAME, class, classname)
#define EXT_CLASS_INIT_INTERFACE(class, classname) EXT_CLASS_INIT_INTERFACE_NX(EXT_NAME, class, classname)
#define EXT_CLASS_INIT_HANDLERS(class) EXT_CLASS_INIT_HANDLERS_NX(EXT_NAME, class)

#endif

#endif /* LILT_GEN_EXT_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */