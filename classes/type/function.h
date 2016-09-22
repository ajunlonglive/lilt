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

#ifndef LILT_TYPE_FUNCTION_H
#define LILT_TYPE_FUNCTION_H

#include "lilt.h"

#define Type_Function Type_Method
#define Type_FunctionName PHP_NSIZE(STRINGIZE(Type), "Method")
#define Type_FunctionStruct EXT_CLASS_STRUCT(Type_Function)
#define Type_FunctionCtor EXT_CLASS_CTOR(Type_Function)
#define Type_FunctionMem(name) EXT_CLASS_MEM(Type_Function, name)
#define Type_FunctionFunc(name, ...) EXT_CLASS_FUNC(Type_Function, name, __VA_ARGS__)

/**
 * API
 * * * * * * * * * */
EXT_CLASS_STRUCT_BEGIN(Type_Function)
    zend_function *function;
    HashTable properties;
    zval arg_infos;
    zval class;
EXT_CLASS_STRUCT_END(Type_Function);
EXT_CLASS_PHP_STRUCT_BEGIN(Type_Function)
EXT_CLASS_PHP_STRUCT_END(Type_Function);
EXT_CLASS_INIT_FUNCTION(Type_Function);
EXT_CLASS_SHUTDOWN_FUNCTION(Type_Function);
PHP_API Type_FunctionStruct *Type_FunctionCtor(zend_function *function);
PHP_API zend_object *Type_FunctionFunc(enclose, Type_FunctionStruct *type);
PHP_API void Type_FunctionFunc(free, Type_FunctionStruct *intern);
PHP_API HashTable *Type_FunctionFunc(properties, Type_FunctionStruct *intern);
PHP_API zval *Type_FunctionFunc(arg_infos, Type_FunctionStruct *intern);
PHP_API zval *Type_FunctionFunc(class, Type_FunctionStruct *intern);

/**
 * Class entry
 * * * * * * * * * */
extern EXT_CLASS_CLASS_ENTRY(Type_Function);
EXT_CLASS_CEINIT_FUNCTION(Type_Function);
PHP_API zend_object *Type_FunctionFunc(create_object, zend_class_entry *ce);

/**
 * Object handlers
 * * * * * * * * * */
EXT_CLASS_OBJECT_HANDLERS(Type_Function);
EXT_CLASS_OHINIT_FUNCTION(Type_Function);
PHP_API void Type_FunctionFunc(free_object, zend_object *object);
PHP_API HashTable *Type_FunctionFunc(get_debug_info, zval *object, int *is_temp);
PHP_API zval *Type_FunctionFunc(read_property, zval *object, zval *member, int type, void **cache_slot, zval *rv);

#endif /* LILT_TYPE_FUNCTION_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */