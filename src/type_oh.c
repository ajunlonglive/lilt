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

#include "classes/type.h"

#define CUSTOM_STRUCT
#define CLASS Type
#include "gen/class.h"

OHINIT_FUNCTION {
    INIT_HANDLERS;
    OH.dtor_obj = zend_objects_destroy_object;
    OH.free_obj = MEM(free_object);
    OH.do_operation = MEM(do_operation);
    OH.get_debug_info = MEM(get_debug_info);
    OH.read_property = MEM(read_property);
}

PHP_API int FUNC(do_operation, zend_uchar opcode, zval *result, zval *op1, zval *op2) {
    ZVAL_BOOL(result, 0);
    if (opcode == ZEND_IS_IDENTICAL || opcode == ZEND_IS_EQUAL ||
        opcode == ZEND_IS_NOT_IDENTICAL || opcode == ZEND_IS_NOT_EQUAL) {
        ZVAL_DEREF(op1);
        ZVAL_DEREF(op2);
        STRUCT *this = Z_THIS_P(op1);
        if (!this) {
            return FAILURE;
        }
        if (Z_TYPE_P(op2) != IS_STRING) {
            return SUCCESS;
        }
        if (opcode == ZEND_IS_IDENTICAL || opcode == ZEND_IS_EQUAL) {
            ZVAL_BOOL(result, zend_string_equals(this->type_name, Z_STR_P(op2)));
        } else {
            ZVAL_BOOL(result, !zend_string_equals(this->type_name, Z_STR_P(op2)));
        }
        return SUCCESS;
    }
    return FAILURE;
}

PHP_API void FUNC(free_object, zend_object *object) {
    PHP_STRUCT *intern = (PHP_STRUCT *) object;
    FUNC(free, intern->intern);
    zend_object_std_dtor(&intern->std);
}

PHP_API HashTable *FUNC(get_debug_info, zval *object, int *is_temp) {
    *is_temp = 0;
    return FUNC(properties, Z_THIS_P(object));
}

PHP_API zval *FUNC(read_property, zval *object, zval *member, int type, void **cache_slot, zval *rv) {
    STRUCT *intern = Z_THIS_P(object);
    zend_string *property_name = Z_STR_P(member);
    if (zend_string_equals_literal(property_name, "name")) {
        ZVAL_STR(rv, intern->type_name);
    } else if (intern->ce) {
        if (zend_string_equals_literal(property_name, "isScalar")) {
            ZVAL_BOOL(rv, 0);
        } else if (zend_string_equals_literal(property_name, "flags")) {
            ZVAL_LONG(rv, intern->ce->ce_flags);
        } else if (zend_string_equals_literal(property_name, "docComment")) {
            ZVAL_STR(rv, intern->ce->info.user.doc_comment);
        } else if (zend_string_equals_literal(property_name, "constants")) {
            rv = FUNC(constants, intern);
        } else if (zend_string_equals_literal(property_name, "functions")) {
            rv = FUNC(functions, intern);
        } else if (zend_string_equals_literal(property_name, "properties")) {
            rv = FUNC(class_properties, intern);
        } else if (zend_string_equals_literal(property_name, "isInternal")) {
            ZVAL_BOOL(rv, intern->ce->type == ZEND_INTERNAL_CLASS);
        } else if (zend_string_equals_literal(property_name, "isAbstract")) {
            ZVAL_BOOL(rv,
                (intern->ce->ce_flags & ZEND_ACC_ABSTRACT) ||
                (intern->ce->ce_flags & ZEND_ACC_EXPLICIT_ABSTRACT_CLASS) ||
                (intern->ce->ce_flags & ZEND_ACC_IMPLICIT_ABSTRACT_CLASS)
            );
        } else if (zend_string_equals_literal(property_name, "isInterface")) {
            ZVAL_BOOL(rv, intern->ce->ce_flags & ZEND_ACC_INTERFACE);
        } else if (zend_string_equals_literal(property_name, "isDeprecated")) {
            ZVAL_BOOL(rv, intern->ce->ce_flags & ZEND_ACC_DEPRECATED);
        } else if (zend_string_equals_literal(property_name, "isFinal")) {
            ZVAL_BOOL(rv, intern->ce->ce_flags & ZEND_ACC_FINAL);
        } else if (zend_string_equals_literal(property_name, "isTrait")) {
            ZVAL_BOOL(rv, intern->ce->ce_flags & ZEND_ACC_TRAIT);
        }
    } else if (zend_string_equals_literal(property_name, "isScalar")) {
        ZVAL_BOOL(rv, 1);
    }
    if (Z_TYPE_P(rv) != IS_UNDEF) {
        return rv;
    }
    zend_error(E_ERROR,"Undefined property: %s::$%s", ZSTR_VAL(Z_OBJ_P(object)->ce->name), Z_STRVAL_P(member));
    return &EG(uninitialized_zval);
}

#undef CUSTOM_STRUCT
#undef CLASS

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */