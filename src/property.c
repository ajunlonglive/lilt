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

#include "classes/type/property.h"

#define CUSTOM_STRUCT
#define CLASS_NAME Type_PropertyName
#define CLASS Type_Property
#include "gen/class.h"

INIT_FUNCTION {
    CEINIT;
    OHINIT;
}

PHP_API STRUCT *CTOR(zend_property_info *property_info, zend_string *name) {
    STRUCT *intern = ecalloc(1, sizeof(STRUCT));
    intern->property_info = property_info;
    intern->name = name ?: intern->property_info->name;
    zend_hash_init(&intern->properties, 4, NULL, zval_p_dtor, 0);
    return intern;
}

PHP_API zend_object *FUNC(enclose, STRUCT *intern) {
    PHP_STRUCT *object = ecalloc(1, sizeof(PHP_STRUCT));
    zend_object_std_init(&object->std, CE);
    object->std.handlers = &OH;
    object->EXT_CLASS_INTERN_STRUCT = intern;
    return &object->std;
}

PHP_API void FUNC(free, STRUCT *intern) {
    zval_ptr_dtor(&intern->class);
    efree(intern);
}

PHP_API HashTable *FUNC(properties, STRUCT *intern) {
    zval tmp;
    if (zend_hash_num_elements(&intern->properties) <= 0) {
        ZVAL_STR(&tmp, intern->name);
        _zend_hash_str_add_new(&intern->properties, STR_AND_LEN("name"), &tmp);
        ZVAL_LONG(&tmp, intern->property_info->flags);
        _zend_hash_str_add_new(&intern->properties, STR_AND_LEN("flags"), &tmp);
        ZVAL_STR_OR_NULL(&tmp, intern->property_info->doc_comment);
        _zend_hash_str_add_new(&intern->properties, STR_AND_LEN("docComment"), &tmp);
        ZVAL_COPY(&tmp, FUNC(class, intern));
        _zend_hash_str_add_new(&intern->properties, STR_AND_LEN("class"), &tmp);
    }
    return &intern->properties;
}

PHP_API zval *FUNC(class, STRUCT *intern) {
    if (Z_TYPE(intern->class) == IS_UNDEF) {
        TypeFunc(zval_of_ce, intern->property_info->ce, &intern->class);
    }
    return &intern->class;
}

#undef CUSTOM_STRUCT
#undef CLASS_NAME
#undef CLASS

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */