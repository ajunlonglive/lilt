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

#include "classes/type/constant.h"

#define CUSTOM_STRUCT
#define CLASS_NAME Type_ConstantName
#define CLASS Type_Constant
#include "gen/class.h"

INIT_FUNCTION {
    CEINIT;
    OHINIT;
}

PHP_API STRUCT *CTOR(zend_string *const_name, zend_class_constant *constant) {
    STRUCT *intern = ecalloc(1, sizeof(STRUCT));
    intern->const_name = const_name;
    intern->constant = constant;
    if (const_name) {
        ZVAL_STR(&intern->name, const_name);
    }
    else {
        ZVAL_NULL(&intern->name);
    }
    if (constant) {
        if (constant->doc_comment) {
            ZVAL_STR(&intern->doc_comment, constant->doc_comment);
        }
        else {
            ZVAL_NULL(&intern->doc_comment);
        }
        ZVAL_COPY(&intern->value, &constant->value);
    }
    else {
        ZVAL_NULL(&intern->doc_comment);
        ZVAL_NULL(&intern->value);
    }

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
    efree(intern);
}

PHP_API zval *FUNC(get_class, STRUCT *intern) {
    if (Z_TYPE(intern->class) == IS_UNDEF) {
        if (intern->constant && intern->constant->ce) {
            TypeFunc(zval_of_ce, intern->constant->ce, &intern->class);
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

PHP_API zval *FUNC(get_name, STRUCT *intern) {
    return &intern->name;
}

PHP_API zval *FUNC(get_value, STRUCT *intern) {
    return &intern->value;
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