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

#ifndef LILT_TYPE_H
#define LILT_TYPE_H

#include "lilt.h"

#define Type Type
#define TypeStruct EXT_CLASS_STRUCT(Type)
#define TypePhpStruct EXT_CLASS_PHP_STRUCT(Type)
#define TypeCe EXT_CLASS_CE(Type)
#define TypeCtor EXT_CLASS_CTOR(Type)
#define TypeMem(name) EXT_CLASS_MEM(Type, name)
#define TypeFunc(name, ...) EXT_CLASS_FUNC(Type, name, __VA_ARGS__)

#define ZVAL_TYPEOF(zv, value) ZVAL_OBJ(zv, TypeFunc(of, value)); Z_TRY_ADDREF_P(zv)
#define ZVAL_TYPEOF_TYPE_EX(zv, type, object) ZVAL_OBJ(zv, TypeFunc(of_type, type, object)); Z_TRY_ADDREF_P(zv)
#define ZVAL_TYPEOF_TYPE(zv, type) ZVAL_TYPEOF_TYPE_EX(zv, type, NULL)
#define ZVAL_TYPEOF_CE(zv, ce) ZVAL_OBJ(zv, TypeFunc(of_ce, ce)); Z_TRY_ADDREF_P(zv)
#define ZVAL_TYPEOF_CLASS_NAME(zv, class_name) ZVAL_OBJ(zv, TypeFunc(of_class_name, class_name)); Z_TRY_ADDREF_P(zv)

#define RETURN_TYPEOF(value) ZVAL_TYPEOF(return_value, value); return
#define RETURN_TYPEOF_CE(ce) ZVAL_TYPEOF_CE(return_value, ce); return
#define RETURN_TYPEOF_CLASS_NAME(class_name) ZVAL_TYPEOF_CLASS_NAME(return_value, class_name); return

/**
 * API
 * * * * * * * * * */
EXT_CLASS_STRUCT_BEGIN(Type)
    zend_class_entry *ce;
    zend_string *type_name;
    zend_object *mock;
    HashTable properties;
    zval constants;
    zval functions;
    zval class_properties;
EXT_CLASS_STRUCT_END(Type);
EXT_CLASS_PHP_STRUCT_BEGIN(Type)
EXT_CLASS_PHP_STRUCT_END(Type);
EXT_CLASS_INIT_FUNCTION(Type);
EXT_CLASS_SHUTDOWN_FUNCTION(Type);
PHP_API TypeStruct *TypeCtor(zend_string *type_name, zend_class_entry *ce);
PHP_API zend_object *TypeFunc(enclose, TypeStruct *type);
PHP_API void TypeFunc(free, TypeStruct *intern);
PHP_API HashTable *TypeFunc(properties, TypeStruct *intern);
PHP_API zval *TypeFunc(constants, TypeStruct *intern);
PHP_API zval *TypeFunc(functions, TypeStruct *intern);
PHP_API zval *TypeFunc(class_properties, TypeStruct *intern);
PHP_API zend_object *TypeFunc(create_mock, zend_class_entry *ce);
PHP_API zend_function *TypeFunc(get_static_method_mock, zend_class_entry *ce, zend_string *name);
PHP_API zend_object *TypeFunc(of, zval *value);
PHP_API zend_object *TypeFunc(of_type, int type, zend_object *object);
PHP_API zend_object *TypeFunc(of_ce, zend_class_entry *ce);
PHP_API zend_object *TypeFunc(of_class_name, zend_string *class_name);

/**
 * Class entry
 * * * * * * * * * */
extern EXT_CLASS_CLASS_ENTRY(Type);
EXT_CLASS_CEINIT_FUNCTION(Type);
EXT_CLASS_CESHUTDOWN_FUNCTION(Type);
zend_function TypeMem(fn_mock);
zend_function TypeMem(fn_unmock);
EXT_CLASS_DECLARE_METHOD(Type, of, AI_RETURN_OBJECT(STRINGIZE(Type), 1, 0, ARG(0, value)));
zend_object *TypeFunc(create_object, zend_class_entry *ce);

/**
 * Object handlers
 * * * * * * * * * */
EXT_CLASS_OBJECT_HANDLERS(Type);
EXT_CLASS_OHINIT_FUNCTION(Type);
PHP_API int TypeFunc(call_method, zend_string *method, zend_object *object, INTERNAL_FUNCTION_PARAMETERS);
PHP_API void TypeFunc(free_object, zend_object *object);
PHP_API HashTable *TypeFunc(get_debug_info, zval *object, int *is_temp);
PHP_API zend_function *TypeFunc(get_method, zend_object **object, zend_string *method, const zval *key);
PHP_API zval *TypeFunc(read_property, zval *object, zval *member, int type, void **cache_slot, zval *rv);

#endif /* LILT_TYPE_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */