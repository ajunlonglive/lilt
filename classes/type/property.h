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

#ifndef LILT_TYPE_PROPERTY_H
#define LILT_TYPE_PROPERTY_H

#include "lilt.h"

#define Type_Property Type_Property
#define Type_PropertyName PHP_NSIZE(STRINGIZE(Type), "Property")
#define Type_PropertyStruct EXT_CLASS_STRUCT(Type_Property)
#define Type_PropertyCtor EXT_CLASS_CTOR(Type_Property)
#define Type_PropertyMem(name) EXT_CLASS_MEM(Type_Property, name)
#define Type_PropertyFunc(name, ...) EXT_CLASS_FUNC(Type_Property, name, __VA_ARGS__)

/**
 * API
 * * * * * * * * * */
EXT_CLASS_STRUCT_BEGIN(Type_Property)
    zend_property_info *property_info;
    zend_string *name;
    HashTable properties;
    zval class;
EXT_CLASS_STRUCT_END(Type_Property);
EXT_CLASS_PHP_STRUCT_BEGIN(Type_Property)
EXT_CLASS_PHP_STRUCT_END(Type_Property);
EXT_CLASS_INIT_FUNCTION(Type_Property);
EXT_CLASS_SHUTDOWN_FUNCTION(Type_Property);
PHP_API Type_PropertyStruct *Type_PropertyCtor(zend_property_info *property_info, zend_string *name);
PHP_API zend_object *Type_PropertyFunc(enclose, Type_PropertyStruct *type);
PHP_API void Type_PropertyFunc(free, Type_PropertyStruct *intern);
PHP_API HashTable *Type_PropertyFunc(properties, Type_PropertyStruct *intern);
PHP_API zval *Type_PropertyFunc(class, Type_PropertyStruct *intern);

/**
 * Class entry
 * * * * * * * * * */
extern EXT_CLASS_CLASS_ENTRY(Type_Property);
EXT_CLASS_CEINIT_FUNCTION(Type_Property);
PHP_API zend_object *Type_PropertyFunc(create_object, zend_class_entry *ce);

/**
 * Object handlers
 * * * * * * * * * */
EXT_CLASS_OBJECT_HANDLERS(Type_Property);
EXT_CLASS_OHINIT_FUNCTION(Type_Property);
PHP_API void Type_PropertyFunc(free_object, zend_object *object);
PHP_API HashTable *Type_PropertyFunc(get_debug_info, zval *object, int *is_temp);
PHP_API zval *Type_PropertyFunc(read_property, zval *object, zval *member, int type, void **cache_slot, zval *rv);

#endif /* LILT_TYPE_PROPERTY_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */