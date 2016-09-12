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

#include "classes/type/arg_info.h"

#define CUSTOM_STRUCT
#define CLASS_NAME Type_ArgInfoName
#define CLASS Type_ArgInfo
#include "gen/class.h"

INIT_FUNCTION {
    CEINIT;
    OHINIT;
}

PHP_API STRUCT *CTOR(zend_arg_info *arg_info) {
    STRUCT *object = ecalloc(1, sizeof(STRUCT));
    object->arg_info = arg_info;

    return object;
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

PHP_API zval *FUNC(get_by_reference, STRUCT *intern) {
    if (Z_TYPE(intern->by_reference) == IS_UNDEF) {
        if (intern->arg_info) {
            ZVAL_BOOL(&intern->by_reference, intern->arg_info->pass_by_reference);
        }
        else {
            ZVAL_NULL(&intern->by_reference);
        }
    }

    return &intern->by_reference;
}

PHP_API zval *FUNC(get_name, STRUCT *intern) {
    if (Z_TYPE(intern->name) == IS_UNDEF) {
        if (intern->arg_info) {
            ZVAL_STR(&intern->name, intern->arg_info->name);
        }
        else {
            ZVAL_NULL(&intern->name);
        }
    }

    return &intern->name;
}

PHP_API zval *FUNC(get_nullable, STRUCT *intern) {
    if (Z_TYPE(intern->nullable) == IS_UNDEF) {
        if (intern->arg_info) {
            ZVAL_BOOL(&intern->nullable, intern->arg_info->allow_null);
        }
        else {
            ZVAL_NULL(&intern->nullable);
        }
    }

    return &intern->nullable;
}

PHP_API zval *FUNC(get_type_hint, STRUCT *intern) {
    if (Z_TYPE(intern->type_hint) == IS_UNDEF) {
        if (intern->arg_info) {
            ZVAL_BOOL(&intern->type_hint, intern->arg_info->type_hint);
        }
        else {
            ZVAL_NULL(&intern->type_hint);
        }
    }

    return &intern->type_hint;
}

PHP_API zval *FUNC(get_variadic, STRUCT *intern) {
    if (Z_TYPE(intern->variadic) == IS_UNDEF) {
        if (intern->arg_info) {
            ZVAL_BOOL(&intern->variadic, intern->arg_info->is_variadic);
        }
        else {
            ZVAL_NULL(&intern->variadic);
        }
    }

    return &intern->variadic;
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