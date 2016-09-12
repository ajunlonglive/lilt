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
    OH.cast_object = MEM(cast_object);
    OH.get_debug_info = MEM(get_debug_info);
    OH.read_property = MEM(read_property);
}

PHP_API int FUNC(cast_object, zval *readobj, zval *retval, int type) {
    if (type != IS_STRING) {
        return zend_std_cast_object_tostring(readobj, retval, type);
    }
    STRUCT *this = Z_THIS_P(readobj);
    if (this->function) {

        ZVAL_STR(retval, this->function->internal_function.function_name);
        return SUCCESS;
    }

    return FAILURE;
}

PHP_API void FUNC(free_object, zend_object *object) {
    PHP_STRUCT *intern = (PHP_STRUCT *) object;
    zend_object_std_dtor(&intern->std);
    FUNC(free, intern->intern);
    efree(intern);
}

PHP_API HashTable *FUNC(get_debug_info, zval *object, int *is_temp) {
    zval tmp;
    zval array;
    STRUCT *intern = Z_THIS_P(object);

    is_temp = 0;
    array_init_size(&array, 4);
    ZVAL_COPY(&tmp, FUNC(get_arg_infos, intern));
    add_assoc_zval(&array, "argInfos", &tmp);
    ZVAL_COPY(&tmp, FUNC(get_class, intern));
    add_assoc_zval(&array, "class", &tmp);
    ZVAL_COPY(&tmp, FUNC(get_name, intern));
    add_assoc_zval(&array, "name", &tmp);
    ZVAL_COPY(&tmp, FUNC(get_flags, intern));
    add_assoc_zval(&array, "flags", &tmp);

    return Z_ARRVAL(array);
}

PHP_API zval *FUNC(read_property, zval *object, zval *member, int type, void **cache_slot, zval *rv) {
    STRUCT *intern = Z_THIS_P(object);
    zend_string *property_name = Z_STR_P(member);
    if (zend_string_equals_literal(property_name, "name")) {
        return FUNC(get_name, intern);
    }
    if (zend_string_equals_literal(property_name, "argInfos")) {
        return FUNC(get_arg_infos, intern);
    }
    if (zend_string_equals_literal(property_name, "class")) {
        return FUNC(get_class, intern);
    }
    if (zend_string_equals_literal(property_name, "flags")) {
        return FUNC(get_flags, intern);
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