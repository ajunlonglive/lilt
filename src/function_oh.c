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

#include "classes/type/function.h"

#define CUSTOM_STRUCT
#define CLASS_NAME Type_FunctionName
#define CLASS Type_Function
#include "gen/class.h"

OHINIT_FUNCTION {
    INIT_HANDLERS;
    OH.dtor_obj = zend_objects_destroy_object;
    OH.free_obj = MEM(free_object);
    OH.get_debug_info = MEM(get_debug_info);
    OH.read_property = MEM(read_property);
}

PHP_API void FUNC(free_object, zend_object *object) {
    PHP_STRUCT *intern = (PHP_STRUCT *) object;

    zend_object_std_dtor(&intern->std);
    FUNC(free, intern->intern);
    efree(intern);
}

PHP_API HashTable *FUNC(get_debug_info, zval *object, int *is_temp) {
    *is_temp = 0;

    return FUNC(properties, Z_THIS_P(object));
}

PHP_API zval *FUNC(read_property, zval *object, zval *member, int type, void **cache_slot, zval *rv) {
    STRUCT *intern = Z_THIS_P(object);
    zend_string *property_name = Z_STR_P(member);

    if (zend_string_equals_literal(property_name, "name")) {
        ZVAL_STR(rv, intern->function->internal_function.function_name);
    } else if (zend_string_equals_literal(property_name, "flags")) {
        ZVAL_LONG(rv, intern->function->internal_function.fn_flags);
    } else if (zend_string_equals_literal(property_name, "docComment")) {
        ZVAL_STR_OR_NULL(rv, intern->function->op_array.doc_comment);
    } else if (zend_string_equals_literal(property_name, "class")) {
        rv = FUNC(class, intern);
    } else if (zend_string_equals_literal(property_name, "argInfos")) {
        rv = FUNC(arg_infos, intern);
    }
    if (Z_TYPE_P(rv) != IS_UNDEF) {
        return rv;
    }
    zend_error(E_ERROR,"Undefined property: %s::$%s", ZSTR_VAL(Z_OBJ_P(object)->ce->name), Z_STRVAL_P(member));

    return &EG(uninitialized_zval);
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