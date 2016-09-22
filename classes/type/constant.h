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

#ifndef LILT_TYPE_CONSTANT_H
#define LILT_TYPE_CONSTANT_H

#include "lilt.h"

#define Type_Constant Type_Constant
#define Type_ConstantName PHP_NSIZE(STRINGIZE(Type), "Constant")
#define Type_ConstantStruct EXT_CLASS_STRUCT(Type_Constant)
#define Type_ConstantCtor EXT_CLASS_CTOR(Type_Constant)
#define Type_ConstantMem(name) EXT_CLASS_MEM(Type_Constant, name)
#define Type_ConstantFunc(name, ...) EXT_CLASS_FUNC(Type_Constant, name, __VA_ARGS__)

/**
 * API
 * * * * * * * * * */
EXT_CLASS_STRUCT_BEGIN(Type_Constant)
    zend_string *const_name;
    zend_class_constant *constant;
    HashTable properties;
    zval class;
EXT_CLASS_STRUCT_END(Type_Constant);
EXT_CLASS_PHP_STRUCT_BEGIN(Type_Constant)
EXT_CLASS_PHP_STRUCT_END(Type_Constant);
EXT_CLASS_INIT_FUNCTION(Type_Constant);
PHP_API Type_ConstantStruct *Type_ConstantCtor(zend_string *const_name, zend_class_constant *constant);
PHP_API zend_object *Type_ConstantFunc(enclose, Type_ConstantStruct *type);
PHP_API void Type_ConstantFunc(free, Type_ConstantStruct *intern);
PHP_API HashTable *Type_ConstantFunc(properties, Type_ConstantStruct *intern);
PHP_API zval *Type_ConstantFunc(class, Type_ConstantStruct *intern);

/**
 * Class entry
 * * * * * * * * * */
extern EXT_CLASS_CLASS_ENTRY(Type_Constant);
EXT_CLASS_CEINIT_FUNCTION(Type_Constant);
PHP_API zend_object *Type_ConstantFunc(create_object, zend_class_entry *ce);

/**
 * Object handlers
 * * * * * * * * * */
EXT_CLASS_OBJECT_HANDLERS(Type_Constant);
EXT_CLASS_OHINIT_FUNCTION(Type_Constant);
PHP_API void Type_ConstantFunc(free_object, zend_object *object);
PHP_API HashTable *Type_ConstantFunc(get_debug_info, zval *object, int *is_temp);
PHP_API zval *Type_ConstantFunc(read_property, zval *object, zval *member, int type, void **cache_slot, zval *rv);

#endif /* LILT_TYPE_CONSTANT_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */