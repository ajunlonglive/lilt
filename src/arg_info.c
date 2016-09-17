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
    STRUCT *intern = ecalloc(1, sizeof(STRUCT));
    intern->arg_info = arg_info;
    zend_hash_init(&intern->properties, 5, NULL, zval_p_dtor, 0);
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

PHP_API HashTable *FUNC(properties, STRUCT *intern) {
    if (zend_hash_num_elements(&intern->properties) <= 0) {
        zend_hash_add_string(&intern->properties, "name", intern->arg_info->name);
        zend_hash_add_bool(&intern->properties, "byReference", intern->arg_info->pass_by_reference);
        zend_hash_add_bool(&intern->properties, "nullable", intern->arg_info->allow_null);
        zend_hash_add_bool(&intern->properties, "typeHint", intern->arg_info->type_hint);
        zend_hash_add_bool(&intern->properties, "variadic", intern->arg_info->is_variadic);
    }
    return &intern->properties;
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