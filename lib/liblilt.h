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

#ifndef LILT_LIBLILT_H
#define LILT_LIBLILT_H

#include "php.h"
#include "ext/standard/info.h"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"
#include "p99/p99/p99.h"
#pragma GCC diagnostic pop

#define STRINGIZE_NX(A) #A
#define STRINGIZE(A) STRINGIZE_NX(A)
#define PPGET_NX(A) A
#define PPGET(A) PPGET_NX(A)
#define PPCAT_NX(A, B) A ## B
#define PPCAT(A, B) PPCAT_NX(A, B)
#define STR_AND_LEN(str) str, sizeof(str) - 1

#define EVAL0(...) __VA_ARGS__
#define EVAL1(...) EVAL0(EVAL0(EVAL0(__VA_ARGS__)))
#define EVAL2(...) EVAL1(EVAL1(EVAL1(__VA_ARGS__)))
#define EVAL3(...) EVAL2(EVAL2(EVAL2(__VA_ARGS__)))
#define EVAL4(...) EVAL3(EVAL3(EVAL3(__VA_ARGS__)))
#define EVAL(...) EVAL4(EVAL4(EVAL4(__VA_ARGS__)))

#define MAP_END(...)
#define MAP_OUT
#define MAP_GET_END() 0, MAP_END
#define MAP_NEXT0(test, next, ...) next MAP_OUT
#define MAP_NEXT1(test, next) MAP_NEXT0(test, next, 0)
#define MAP_NEXT(test, next) MAP_NEXT1(MAP_GET_END test, next)
#define MAP0(f, x, peek, ...) f(x) MAP_NEXT(peek, MAP1)(f, peek, __VA_ARGS__)
#define MAP1(f, x, peek, ...) f(x) MAP_NEXT(peek, MAP0)(f, peek, __VA_ARGS__)
#define MAP(f, ...) EVAL(MAP1(f, __VA_ARGS__, (), 0))

#define CONCAT_FN_1(what, x, ...) what(x)
#define CONCAT_FN_2(what, x, ...) \
  PPCAT(what(x), CONCAT_FN_1(what, __VA_ARGS__))
#define CONCAT_FN_3(what, x, ...) \
  PPCAT(what(x), CONCAT_FN_2(what, __VA_ARGS__))
#define CONCAT_FN_4(what, x, ...) \
  PPCAT(what(x), CONCAT_FN_3(what, __VA_ARGS__))
#define CONCAT_FN_5(what, x, ...) \
  PPCAT(what(x), CONCAT_FN_4(what, __VA_ARGS__))
#define CONCAT_FN_6(what, x, ...) \
  PPCAT(what(x), CONCAT_FN_5(what, __VA_ARGS__))
#define CONCAT_FN_7(what, x, ...) \
  PPCAT(what(x), CONCAT_FN_6(what, __VA_ARGS__))
#define CONCAT_FN_8(what, x, ...) \
  PPCAT(what(x), CONCAT_FN_7(what, __VA_ARGS__))
#define CONCAT_FN_9(what, x, ...) \
  PPCAT(what(x), CONCAT_FN_8(what, __VA_ARGS__))
#define CONCAT_FN_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, N, ...) N
#define CONCAT_FN_RSEQ_N() 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
#define CONCAT_FN_NARG_(...) CONCAT_FN_ARG_N(__VA_ARGS__)
#define CONCAT_FN_NARG(...) CONCAT_FN_NARG_(__VA_ARGS__, CONCAT_FN_RSEQ_N())
#define CONCAT_FN_(N, what, x, ...) PPCAT(CONCAT_FN_, N)(what, x, __VA_ARGS__)
#define CONCAT_FN(what, x, ...) CONCAT_FN_(CONCAT_FN_NARG(x, __VA_ARGS__), what, x, __VA_ARGS__)
#define CONCAT(...) CONCAT_FN(PPGET, __VA_ARGS__)

#define z_string_nx(str, persistent) zend_string_init(STR_AND_LEN(str), persistent)
#define z_string(str) zend_string_init(STR_AND_LEN(str), 0)
#define PHP_NSIZE(nsname, class) ZEND_NS_NAME(nsname, class)
#define FUNCTIONS_END PHP_FE_END };
#define METHODS_END PHP_FE_END };
#define ZVAL_STR_OR_NULL(zv, str) if (str) { ZVAL_STR(zv, str); } else { ZVAL_NULL(zv); }
#define EX_ARG(n) ZEND_CALL_ARG(execute_data, n)
#define IS_A_P(zv, _ce) (Z_TYPE_P(zv) == IS_OBJECT && Z_OBJ_P(zv)->ce == _ce)
#define IS_A(zv, _ce) (Z_TYPE(zv) == IS_OBJECT && Z_OBJ(zv)->ce == _ce)
#define INSTANCE_OF_P(zv, _ce) \
  (Z_TYPE_P(zv) == IS_OBJECT && (Z_OBJ_P(zv)->ce == _ce || instanceof_function(Z_OBJ_P(zv)->ce, _ce)))
#define INSTANCE_OF(zv, _ce) INSTANCE_OF_P(&zv, _ce)

#define EXT_ME_NX(name) CONCAT(name, _module_entry)
#define EXT_MODULE_ENTRY_NX(name) zend_module_entry EXT_ME_NX(name)
#define EXT_EXTERN_MODULE_ENTRY_NX(name) extern EXT_MODULE_ENTRY_NX(name)
#define EXT_MG_NX(name) CONCAT(name, _globals)
#define EXT_MGSTRUCT_NX(name) CONCAT(zend_, name, _globals)
#define EXT_DECLARE_MODULE_GLOBALS_NX(name) ZEND_DECLARE_MODULE_GLOBALS(name)
#define EXT_EXTERN_MODULE_GLOBALS_NX(name) ZEND_EXTERN_MODULE_GLOBALS(name)
#define EXT_BEGIN_MODULE_GLOBALS_NX(name) ZEND_BEGIN_MODULE_GLOBALS(name)
#define EXT_END_MODULE_GLOBALS_NX(name) ZEND_END_MODULE_GLOBALS(name)
#define EXT_MEMSET_GLOBALS_NX(name) memset(global, 0, sizeof(EXT_MGSTRUCT_NX(name)))
#define EXT_MODULE_GLOBALS_NX(name) PHP_MODULE_GLOBALS(name)
#define EXT_MGINIT_NX(name) CONCAT(php_, name, _init_globals)
#define EXT_MGINIT_FUNCTION_NX(name) static inline void EXT_MGINIT_NX(name)(CONCAT(zend_, name, _globals) *global)
#define EXT_GINIT_NX(name) PHP_GINIT(name)
#define EXT_GINIT_FUNCTION_NX(name) PHP_GINIT_FUNCTION(name)
#define EXT_MINIT_NX(name) PHP_MINIT(name)
#define EXT_MINIT_FUNCTION_NX(name) PHP_MINIT_FUNCTION(name)
#define EXT_MSHUTDOWN_NX(name) PHP_MSHUTDOWN(name)
#define EXT_MSHUTDOWN_FUNCTION_NX(name) PHP_MSHUTDOWN_FUNCTION(name)
#define EXT_RINIT_NX(name) PHP_RINIT(name)
#define EXT_RINIT_FUNCTION_NX(name) PHP_RINIT_FUNCTION(name)
#define EXT_RSHUTDOWN_NX(name) PHP_RSHUTDOWN(name)
#define EXT_RSHUTDOWN_FUNCTION_NX(name) PHP_RSHUTDOWN_FUNCTION(EXT_NAME)
#define EXT_MINFO_NX(name) PHP_MINFO(name)
#define EXT_MINFO_FUNCTION_NX(name) PHP_MINFO_FUNCTION(name)
#define EXT_DEPS_NX(name) CONCAT(name, _deps)
#define EXT_DEPS_TABLE_NX(name) static const zend_module_dep EXT_DEPS_NX(name)[]
#define EXT_FUNCTIONS_NX(name) CONCAT(name, _functions)
#define EXT_FUNCTIONS_TABLE_NX(name) static const zend_function_entry EXT_FUNCTIONS_NX(name)[]
#define EXT_MINFO_BODY_NX(name, version) \
  php_info_print_table_start(); \
  php_info_print_table_row(2, CONCAT(STRINGIZE(name)), "enabled"); \
  php_info_print_table_row(2, CONCAT(STRINGIZE(name)), version); \
  php_info_print_table_end()
#define EXT_MODULE_PROPERTIES_NX(name, version) \
  STANDARD_MODULE_HEADER_EX, \
  NULL, \
  EXT_DEPS_NX(name), \
  STRINGIZE(EXT_NAME), \
  EXT_FUNCTIONS_NX(name), \
  EXT_MINIT_NX(name), \
  EXT_MSHUTDOWN_NX(name), \
  EXT_RINIT_NX(name), \
  EXT_RSHUTDOWN_NX(name), \
  EXT_MINFO_NX(name), \
  version, \
  EXT_MODULE_GLOBALS_NX(name), \
  EXT_GINIT_NX(name), \
  NULL, \
  NULL, \
  STANDARD_MODULE_PROPERTIES_EX
#define EXT_FN(name) PHP_FN(name)
#define EXT_MN(name) PHP_MN(name)
#define EXT_METH_E(class, name, arg_info, flags) PHP_ME(class, name, arg_info, flags)
#define EXT_FE(name, arg_info) ZEND_FE(name, arg_info)

#ifdef ZEND_VM_FP_GLOBAL_REG
#define LILT_OPCODE_HANDLER_ARGS
#define LILT_OPCODE_HANDLER_ARGS_PASSTHRU
#else
#define LILT_OPCODE_HANDLER_ARGS zend_execute_data *execute_data
#define LILT_OPCODE_HANDLER_ARGS_PASSTHRU execute_data
#endif
typedef int (*lilt_opcode_handler_t)(LILT_OPCODE_HANDLER_ARGS);
#define EXT_HINIT_NX(module) CONCAT(module, _opcode_handlers_init)
#define EXT_HINIT_FUNCTION_NX(module) void EXT_HINIT_NX(module)()
#define EXT_HSHUTDOWN_NX(module) CONCAT(module, _opcode_handlers_free)
#define EXT_HFREE_FUNCTION_NX(module) void EXT_HSHUTDOWN_NX(module)()
#define EXT_HANDLER_NX(module, opcode) CONCAT(module, _, opcode, _opcode_handler)
#define EXT_DFT_HANDLER_NX(module, opcode) CONCAT(EXT_HANDLER_NX(module, opcode), _default)
#define EXT_DFT_HANDLER_DECLARE_NX(module, opcode) lilt_opcode_handler_t EXT_DFT_HANDLER_NX(module, opcode)
#define EXT_HANDLER_FUNCTION_NX(module, opcode) \
  EXT_DFT_HANDLER_DECLARE_NX(module, opcode); \
  int EXT_HANDLER_NX(module, opcode)(LILT_OPCODE_HANDLER_ARGS)
#define EXT_SET_HANDLER_NX(module, opcode) \
  EXT_DFT_HANDLER_NX(module, opcode) = zend_get_user_opcode_handler(opcode); \
  zend_set_user_opcode_handler(opcode, EXT_HANDLER_NX(module, opcode))
#define EXT_UNSET_HANDLER_NX(module, opcode) \
  zend_set_user_opcode_handler(opcode, EXT_DFT_HANDLER_NX(module, opcode))

#define EXT_CLASS_INIT_NX(module, class) CONCAT(module, _, class, _init)()
#define EXT_CLASS_INIT_FUNCTION_NX(module, class) void EXT_CLASS_INIT_NX(module, class)
#define EXT_CLASS_SHUTDOWN_NX(module, class) CONCAT(module, _, class, _shutdown)()
#define EXT_CLASS_SHUTDOWN_FUNCTION_NX(module, class) void EXT_CLASS_SHUTDOWN_NX(module, class)
#define EXT_CLASS_CE_NX(module, class) CONCAT(module, _ce_, class)
#define EXT_CLASS_CLASS_ENTRY_NX(module, class) zend_class_entry *EXT_CLASS_CE_NX(module, class)
#define EXT_CLASS_CEINIT_NX(module, class) CONCAT(EXT_CLASS_CE_NX(module, class), _init)()
#define EXT_CLASS_CEINIT_FUNCTION_NX(module, class) void EXT_CLASS_CEINIT_NX(module, class)
#define EXT_CLASS_CESHUTDOWN_NX(module, class) CONCAT(EXT_CLASS_CE_NX(module, class), _shutdown)()
#define EXT_CLASS_CESHUTDOWN_FUNCTION_NX(module, class) void EXT_CLASS_CESHUTDOWN_NX(module, class)
#define EXT_CLASS_OH_NX(module, class) CONCAT(module, _oh_, class)
#define EXT_CLASS_OBJECT_HANDLERS_NX(module, class) zend_object_handlers EXT_CLASS_OH_NX(module, class)
#define EXT_CLASS_OHINIT_NX(module, class) CONCAT(EXT_CLASS_OH_NX(module, class), _init)()
#define EXT_CLASS_OHINIT_FUNCTION_NX(module, class) void EXT_CLASS_OHINIT_NX(module, class)
#define EXT_CLASS_STRUCT_NX(module, class) CONCAT(module, _, class, _t)
#define EXT_CLASS_PHP_STRUCT_NX(module, class) CONCAT(php_, EXT_CLASS_STRUCT_NX(module, class))
#define EXT_CLASS_STRUCT_BEGIN_NX(module, class) typedef struct CONCAT(_, EXT_CLASS_STRUCT_NX(module, class)) {
#define EXT_CLASS_STRUCT_END_NX(module, class) } EXT_CLASS_STRUCT_NX(module, class);
#define EXT_CLASS_INTERN_STRUCT intern
#define EXT_CLASS_PHP_STRUCT_BEGIN_NX(module, class) \
  typedef struct CONCAT(_, EXT_CLASS_PHP_STRUCT_NX(module, class)) { \
      zend_object std; \
      EXT_CLASS_STRUCT_NX(module, class) *EXT_CLASS_INTERN_STRUCT;
#define EXT_CLASS_PHP_STRUCT_END_NX(module, class) } EXT_CLASS_PHP_STRUCT_NX(module, class);
#define EXT_CLASS_Z_THIS(z) Z_OBJ(z)
#define EXT_CLASS_Z_THIS_P(z) Z_OBJ(*z)
#define EXT_CLASS_CUSTOM_Z_THIS_NX(module, class, z) ((EXT_CLASS_PHP_STRUCT_NX(module, class)*) (Z_OBJ(z)))->EXT_CLASS_INTERN_STRUCT
#define EXT_CLASS_CUSTOM_Z_THIS_P_NX(module, class, z) EXT_CLASS_CUSTOM_Z_THIS_NX(module, class, *z)
#define EXT_CLASS_THIS EXT_CLASS_Z_THIS(EX(This))
#define EXT_CLASS_INIT_THIS zend_object *this = EXT_CLASS_THIS()
#define EXT_CLASS_CUSTOM_THIS_NX(module, class) EXT_CLASS_CUSTOM_Z_THIS_NX(module, class, EX(This))
#define EXT_CLASS_INIT_CUSTOM_THIS_NX(module, class) EXT_CLASS_STRUCT_NX(module, class) *this = EXT_CLASS_CUSTOM_THIS_NX(module, class)
#define EXT_CLASS_METHODS_NX(module, class) CONCAT(module, _, class, _methods)
#define EXT_CLASS_NO_METHODS_NX(module, class) zend_function_entry *EXT_CLASS_METHODS_NX(module, class) = NULL
#define EXT_CLASS_METHODS_BEGIN_NX(module, class) zend_function_entry EXT_CLASS_METHODS_NX(module, class)[] = {
#define EXT_CLASS_METHOD_NX(module, class, name) ZEND_NAMED_FUNCTION(EXT_MN(CONCAT(class, _, name)))
#define EXT_ARGINFO_NX(module, class, name) CONCAT(module, _, class, _, arginfo, _, name)
#define EXT_CLASS_ME_NX(module, class, name, flags) ZEND_FENTRY(name, EXT_MN(CONCAT(class, _, name)), EXT_ARGINFO_NX(module, class, name), flags)
#define ARG(pass_by_ref, name) { #name, NULL, 0, pass_by_ref, 0, 0 }
#define ARG_PASS(pass_by_ref) { NULL,  NULL, 0, pass_by_ref, 0, 0 }
#define ARG_OBJ(pass_by_ref, name, classname, allow_null) { #name, #classname, IS_OBJECT, pass_by_ref, allow_null, 0 }
#define ARG_ARRAY(pass_by_ref, name, allow_null) { #name, NULL, IS_ARRAY, pass_by_ref, allow_null, 0 }
#define ARG_CALLABLE(pass_by_ref, name, allow_null) { #name, NULL, IS_CALLABLE, pass_by_ref, allow_null, 0 }
#define ARG_TYPE(pass_by_ref, name, type_hint, allow_null) { #name, NULL, type_hint, pass_by_ref, allow_null, 0 }
#define ARG_VARIADIC(pass_by_ref, name) { #name, NULL, 0, pass_by_ref, 0, 1 }
#define EXT_BEGIN_ARG_WITH_RETURN_TYPE_INFO_NX(name) static const zend_internal_arg_info name[] = {
#define EXT_ARG_INFOS_NX(module, class, name, arg_infos) \
  EXT_BEGIN_ARG_WITH_RETURN_TYPE_INFO_NX(EXT_ARGINFO_NX(module, class, name)) \
      arg_infos \
  ZEND_END_ARG_INFO()
#define EXT_CLASS_DECLARE_METHOD_NX(module, class, name, arg_infos) \
  EXT_BEGIN_ARG_WITH_RETURN_TYPE_INFO_NX(EXT_ARGINFO_NX(module, class, name)) \
      arg_infos \
  ZEND_END_ARG_INFO() \
  EXT_CLASS_METHOD_NX(module, class, name)
#define AI_RETURN(type, class_name, ref, nullable, ...) \
  { (const char*)(zend_uintptr_t)(P99_NARG(__VA_ARGS__)/P99_NARG(ARG(0, foo))), class_name, type, ref, nullable, 0 }, \
  ##__VA_ARGS__
#define AI(...) AI_RETURN(0, NULL, 0, 0, __VA_ARGS__)
#define AI_EMPTY AI()
#define AI_RETURN_OBJECT(class_name, ref, nullable, ...) AI_RETURN(IS_OBJECT, class_name, ref, nullable, __VA_ARGS__)
#define AI_RETURN_ARRAY(ref, nullable, ...) AI_RETURN(IS_ARRAY, NULL, ref, nullable, __VA_ARGS__)
#define AI_RETURN_BOOL(ref, nullable, ...) AI_RETURN(_IS_BOOL, NULL, ref, nullable, __VA_ARGS__)
#define AI_RETURN_DOUBLE(ref, nullable, ...) AI_RETURN(IS_DOUBLE, NULL, ref, nullable, __VA_ARGS__)
#define AI_RETURN_LONG(ref, nullable, ...) AI_RETURN(IS_LONG, NULL, ref, nullable, __VA_ARGS__)
#define AI_RETURN_STRING(ref, nullable, ...) AI_RETURN(IS_STRING, NULL, ref, nullable, __VA_ARGS__)
#define AI_RETURN_RESOURCE(ref, nullable, ...) AI_RETURN(IS_RESOURCE, NULL, ref, nullable, __VA_ARGS__)
#define AI_RETURN_VOID(ref, nullable, ...) AI_RETURN(IS_VOID, NULL, ref, nullable, __VA_ARGS__)
#define EXT_CLASS_ABSTRACT_ME_NX(name, arginfo, flags) ZEND_FENTRY(name, NULL, arginfo, ZEND_ACC_ABSTRACT|flags)
#define EXT_CLASS_MAGIC_ME_NX(name, arginfo, flags) ZEND_FENTRY(name, NULL, arginfo, flags)
#define EXT_CLASS_CTOR_NX(module, class) CONCAT(module, _, class)
#define EXT_CLASS_MEM_NX(module, class, name) CONCAT(EXT_CLASS_CTOR_NX(module, class), _, name)
#define EXT_CLASS_FUNC_NX(module, class, name, ...) EXT_CLASS_MEM_NX(module, class, name)(__VA_ARGS__)
#define EXT_CLASS_INIT_CLASS_NX(module, class, classname) { \
      zend_class_entry ce; \
      INIT_CLASS_ENTRY(ce, classname, EXT_CLASS_METHODS_NX(module, class)); \
      EXT_CLASS_CE_NX(module, class) = zend_register_internal_class(&ce); \
  }
#define EXT_CLASS_INIT_INTERFACE_NX(module, class, classname) { \
      zend_class_entry ce; \
      INIT_CLASS_ENTRY(ce, classname, EXT_CLASS_METHODS_NX(module, class)); \
      EXT_CLASS_CE_NX(module, class) = zend_register_internal_interface(&ce); \
  }
#define EXT_CLASS_INIT_HANDLERS_CUSTOM_STRUCT_NX(module, class) \
  memcpy(&EXT_CLASS_OH_NX(module, class), zend_get_std_object_handlers(), sizeof(zend_object_handlers)); \
  EXT_CLASS_OH_NX(module, class).offset = XtOffsetOf(EXT_CLASS_PHP_STRUCT_NX(module, class), std)
#define EXT_CLASS_INIT_HANDLERS_NX(module, class) \
  memcpy(&EXT_CLASS_OH_NX(module, class), zend_get_std_object_handlers(), sizeof(zend_object_handlers));

#endif /* LILT_LIBLILT_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */