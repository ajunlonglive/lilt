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

#include <Zend/zend_compile.h>
#include "classes/type/function.h"

#define CUSTOM_STRUCT
#define CLASS_NAME Type_FunctionName
#define CLASS Type_Function
#include "gen/class.h"

INIT_FUNCTION {
    CEINIT;
    OHINIT;
}

PHP_API STRUCT *CTOR(zend_function *function) {
    STRUCT *intern = ecalloc(1, sizeof(STRUCT));
    intern->function = function;
    if (function) {
        ZVAL_LONG(&intern->flags, function->internal_function.fn_flags);
        ZVAL_STR(&intern->name, intern->function->internal_function.function_name);
    }
    else {
        ZVAL_NULL(&intern->flags);
        ZVAL_NULL(&intern->name);
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

PHP_API zval *FUNC(get_arg_infos, STRUCT *intern) {
    if (Z_TYPE(intern->arg_infos) == IS_UNDEF) {
        if (intern->function) {
            zend_arg_info *ptr = intern->function->common.arg_info;
            array_init_size(&intern->arg_infos, 3);
            if (ptr) {
                while (ptr->name) {
                    zval zv;
                    ZVAL_OBJ(&zv, Type_ArgInfoMem(enclose)(Type_ArgInfoCtor(ptr)));
                    zend_hash_add(Z_ARRVAL(intern->arg_infos), ptr->name, &zv);
                    ptr++;
                }
            }
        }
        else {
            ZVAL_NULL(&intern->arg_infos);
        }
    }

    return &intern->arg_infos;
}

PHP_API zval *FUNC(get_class, STRUCT *intern) {
    if (Z_TYPE(intern->class) == IS_UNDEF) {
        if (intern->function && intern->function->internal_function.scope) {
            TypeFunc(zval_of_ce, intern->function->internal_function.scope, &intern->class);
        }
        else {
            ZVAL_NULL(&intern->class);
        }
    }

    return &intern->class;
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