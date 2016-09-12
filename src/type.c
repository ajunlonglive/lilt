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

INIT_FUNCTION {
    CEINIT;
    OHINIT;
}

PHP_API STRUCT *CTOR(zend_string *type_name, zend_class_entry* ce) {
    STRUCT *intern = ecalloc(1, sizeof(STRUCT));
    intern->type_name = type_name;
    intern->ce = ce;
    if (intern->type_name) {
        ZVAL_STR(&intern->name, intern->type_name);
    }
    else {
        ZVAL_NULL(&intern->name);
    }
    if (intern->ce) {
        ZVAL_LONG(&intern->flags, intern->ce->ce_flags);
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
    efree(intern);
}

PHP_API zval *FUNC(get_name, STRUCT *intern) {
    return &intern->name;
}

PHP_API zval *FUNC(get_flags, STRUCT *intern) {
    return &intern->flags;
}

PHP_API zval *FUNC(get_constants, STRUCT *intern) {
    if (intern->ce && Z_TYPE(intern->constants) == IS_UNDEF) {
        zend_string *key;
        zend_class_constant *constant;
        array_init_size(&intern->constants, 3);
        ZEND_HASH_FOREACH_STR_KEY_PTR(&intern->ce->constants_table, key, constant)
            if (Z_TYPE(constant->value) != IS_OBJECT || Z_OBJ(constant->value)->ce != TypeCe) {
                zval zv;
                ZVAL_OBJ(&zv, Type_ConstantMem(enclose)(Type_ConstantCtor(key, constant)));
                zend_hash_add(Z_ARRVAL(intern->constants), key, &zv);
            }
        ZEND_HASH_FOREACH_END();
    }

    return &intern->constants;
}

PHP_API zval *FUNC(get_functions, STRUCT *intern) {
    if (intern->ce && Z_TYPE(intern->functions) == IS_UNDEF) {
        zend_function *function;
        array_init_size(&intern->functions, 3);
        ZEND_HASH_FOREACH_PTR(&intern->ce->function_table, function)
            zval zv;
            ZVAL_OBJ(&zv, Type_FunctionMem(enclose)(Type_FunctionCtor(function)));
            zend_hash_add(Z_ARRVAL(intern->functions), function->internal_function.function_name, &zv);
        ZEND_HASH_FOREACH_END();
    }

    return &intern->functions;
}

PHP_API zval *FUNC(get_properties, STRUCT *intern) {
    if (intern->ce && Z_TYPE(intern->properties) == IS_UNDEF) {
        zend_property_info *property_info;
        array_init_size(&intern->properties, 3);
        ZEND_HASH_FOREACH_PTR(&intern->ce->properties_info, property_info)
            zval zv;
            ZVAL_OBJ(&zv, Type_PropertyMem(enclose)(Type_PropertyCtor(property_info)));
            zend_hash_add(Z_ARRVAL(intern->properties), property_info->name, &zv);
        ZEND_HASH_FOREACH_END();
    }

    return &intern->properties;
}

PHP_API int FUNC(zval_of, zval *value, zval *rv) {
    switch (Z_TYPE_P(value)) {
        case IS_LONG:
            ZVAL_OBJ(rv, LILTG(type_integer));;
            break;
        case IS_DOUBLE:
            ZVAL_OBJ(rv, LILTG(type_double));;
            break;
        case IS_STRING:
            ZVAL_OBJ(rv, LILTG(type_string));;
            break;
        case _IS_BOOL:
        case IS_TRUE:
        case IS_FALSE:
            ZVAL_OBJ(rv, LILTG(type_boolean));;
            break;
        case IS_NULL:
            ZVAL_OBJ(rv, LILTG(type_null));;
            break;
        case IS_OBJECT:
            return FUNC(zval_of_ce, Z_OBJ_P(value)->ce, rv);
        case IS_ARRAY:
            ZVAL_OBJ(rv, LILTG(type_array));;
            break;
        case IS_RESOURCE:
            ZVAL_OBJ(rv, LILTG(type_resource));;
            break;
        case IS_REFERENCE:
            return FUNC(zval_of, Z_REFVAL_P(value), rv);
        default:
            ZVAL_OBJ(rv, LILTG(type_unknown));
    }

    return SUCCESS;
}

PHP_API int FUNC(zval_of_ce, zend_class_entry *ce, zval *rv) {
    zval zv, *ptr;

    ptr = zend_hash_find(&LILTG(data.types), ce->name);
    if (!ptr) {
        ZVAL_OBJ(&zv, FUNC(enclose, CTOR(ce->name, ce)));
        zend_hash_add(&LILTG(data.types), ce->name, &zv);
        ptr = &zv;
    }
    ZVAL_COPY(rv, ptr);

    return SUCCESS;
}

PHP_API int FUNC(zval_of_classname, zval *value, zval *rv) {
    zval zv, *ptr;
    zend_class_entry *ce;

    if (Z_TYPE_P(value) != IS_STRING) {
        return FUNC(zval_of, value, rv);
    }
    ptr = zend_hash_find(&LILTG(data.types), Z_STR_P(value));
    if (!ptr) {
        ce = zend_lookup_class(Z_STR_P(value));
        if (ce) {
            ZVAL_OBJ(&zv, FUNC(enclose, CTOR(ce->name, ce)));
            zend_hash_add(&LILTG(data.types), ce->name, &zv);
            ptr = &zv;
        }
        else {
            ZVAL_NULL(rv);
            return FAILURE;
        }
    }
    ZVAL_COPY(rv, ptr);

    return SUCCESS;
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