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
#define TypeCe EXT_CLASS_CE(Type)
#define TypeCtor EXT_CLASS_CTOR(Type)
#define TypeMem(name) EXT_CLASS_MEM(Type, name)
#define TypeFunc(name, ...) EXT_CLASS_FUNC(Type, name, __VA_ARGS__)

/**
 * API
 * * * * * * * * * */
EXT_CLASS_STRUCT_BEGIN(Type)
    zend_class_entry *ce;
    zend_string *type_name;
    HashTable properties;
    zval constants;
    zval functions;
    zval class_properties;
EXT_CLASS_STRUCT_END(Type);
EXT_CLASS_PHP_STRUCT_BEGIN(Type)
EXT_CLASS_PHP_STRUCT_END(Type);
EXT_CLASS_INIT_FUNCTION(Type);
PHP_API TypeStruct *TypeCtor(zend_string *type_name, zend_class_entry *ce);
PHP_API zend_object *TypeFunc(enclose, TypeStruct *type);
PHP_API void TypeFunc(free, TypeStruct *intern);
PHP_API HashTable *TypeFunc(properties, TypeStruct *intern);
PHP_API zval *TypeFunc(constants, TypeStruct *intern);
PHP_API zval *TypeFunc(functions, TypeStruct *intern);
PHP_API zval *TypeFunc(class_properties, TypeStruct *intern);
PHP_API int TypeFunc(zval_of, zval *value, zval *rv);
PHP_API int TypeFunc(zval_of_ce, zend_class_entry *ce, zval *rv);
PHP_API int TypeFunc(zval_of_classname, zval *value, zval *rv);

/**
 * Class entry
 * * * * * * * * * */
extern EXT_CLASS_CLASS_ENTRY(Type);
EXT_CLASS_CEINIT_FUNCTION(Type);
PHP_API EXT_CLASS_METHOD(Type, of);
PHP_API zend_object *TypeFunc(create_object, zend_class_entry *ce);

/**
 * Object handlers
 * * * * * * * * * */
EXT_CLASS_OBJECT_HANDLERS(Type);
EXT_CLASS_OHINIT_FUNCTION(Type);
PHP_API int TypeFunc(do_operation, zend_uchar opcode, zval *result, zval *op1, zval *op2);
PHP_API void TypeFunc(free_object, zend_object *object);
PHP_API HashTable *TypeFunc(get_debug_info, zval *object, int *is_temp);
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