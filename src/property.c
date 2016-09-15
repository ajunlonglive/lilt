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
    if (intern->property_info) {
        if (intern->property_info->doc_comment) {
            ZVAL_STR(&intern->doc_comment, intern->property_info->doc_comment);
        }
        else {
            ZVAL_NULL(&intern->doc_comment);
        }
        ZVAL_LONG(&intern->flags, intern->property_info->flags);
        ZVAL_STR(&intern->name, name != NULL ? name : intern->property_info->name);
    }
    else {
        ZVAL_NULL(&intern->doc_comment);
        ZVAL_NULL(&intern->flags);
        ZVAL_NULL(&intern->name);
    }

    return intern;
}

PHP_API zend_object *FUNC(enclose, STRUCT *type) {
    PHP_STRUCT *object = ecalloc(1, sizeof(PHP_STRUCT));
    zend_object_std_init(&object->std, CE);
    object->std.handlers = &OH;
    object->EXT_CLASS_INTERN_STRUCT = type;

    return &object->std;
}

PHP_API void FUNC(free, STRUCT *intern) {
    zval_ptr_dtor(&intern->class);
    zval_ptr_dtor(&intern->doc_comment);
    zval_ptr_dtor(&intern->flags);
    zval_ptr_dtor(&intern->name);
    efree(intern);
}

PHP_API zval *FUNC(get_class, STRUCT *intern) {
    if (Z_TYPE(intern->class) == IS_UNDEF) {
        if (intern->property_info && intern->property_info->ce) {
            TypeFunc(zval_of_ce, intern->property_info->ce, &intern->class);
        }
        else {
            ZVAL_NULL(&intern->class);
        }
    }


    return &intern->class;
}

PHP_API zval *FUNC(get_doc_comment, STRUCT *intern) {
    return &intern->doc_comment;
}

PHP_API zval *FUNC(get_flags, STRUCT *intern) {
    return &intern->flags;
}

PHP_API zval *FUNC(get_name, STRUCT *intern) {
    return &intern->name;
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