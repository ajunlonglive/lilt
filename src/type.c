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

#include <Zend/zend.h>
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
    zend_hash_init(&intern->properties, 6, NULL, zval_p_dtor, 0);

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
    if (intern->mock) {
        intern->mock = NULL;
        if (intern->ce) {
            intern->ce->create_object = NULL;
            intern->ce->get_static_method = NULL;
        }
    }
    zval_ptr_dtor(&intern->constants);
    zval_ptr_dtor(&intern->functions);
    zval_ptr_dtor(&intern->class_properties);
    zend_string_release(intern->type_name);
    efree(intern);
}

PHP_API HashTable *FUNC(properties, STRUCT *intern) {
    if (zend_hash_num_elements(&intern->properties) <= 0) {
        zend_hash_add_string(&intern->properties, "name", intern->type_name);
        if (!intern->ce) {
            zend_hash_add_bool(&intern->properties, "isScalar", 1);
        } else {
            zend_hash_add_bool(&intern->properties, "isScalar", 0);
            zend_hash_add_long(&intern->properties, "flags", intern->ce->ce_flags);
            zend_hash_add_string(&intern->properties, "docComment", intern->ce->info.user.doc_comment);
            zend_hash_add_zval(&intern->properties, "constants", FUNC(constants, intern));
            zend_hash_add_zval(&intern->properties, "properties", FUNC(class_properties, intern));
            zend_hash_add_zval(&intern->properties, "functions", FUNC(functions, intern));
        }
    }

    return &intern->properties;
}

PHP_API zval *FUNC(constants, STRUCT *intern) {
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

PHP_API zval *FUNC(class_properties, STRUCT *intern) {
    if (intern->ce && Z_TYPE(intern->class_properties) == IS_UNDEF) {
        zend_string *key;
        zend_property_info *property_info;

        array_init_size(&intern->class_properties, 3);
        ZEND_HASH_FOREACH_STR_KEY_PTR(&intern->ce->properties_info, key, property_info)
            zval zv;
            ZVAL_OBJ(&zv, Type_PropertyMem(enclose)(Type_PropertyCtor(property_info, key)));
            zend_hash_add(Z_ARRVAL(intern->class_properties), key, &zv);
        ZEND_HASH_FOREACH_END();
    }

    return &intern->class_properties;
}

PHP_API zval *FUNC(functions, STRUCT *intern) {
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

PHP_API zend_object *FUNC(create_mock, zend_class_entry *ce) {
    STRUCT *intern = Z_THIS_P(zend_hash_find(&LILTG(data.mocks), ce->name));

    zend_object *object = intern->ce->create_object
        ? intern->ce->create_object(intern->ce)
        : zend_objects_new(intern->ce);
    object_properties_init(object, intern->ce);

    return object;
}

PHP_API zend_function *FUNC(get_static_method_mock, zend_class_entry *ce, zend_string *name) {
    STRUCT *intern = Z_THIS_P(zend_hash_find(&LILTG(data.mocks), ce->name));

    return intern->ce->get_static_method
        ? intern->ce->get_static_method(intern->ce, name)
        : zend_std_get_static_method(intern->ce, name, NULL);
}

PHP_API zend_object *FUNC(of, zval *value) {
    switch (Z_TYPE_P(value)) {
        case IS_LONG:
            return LILTG(type_integer);
        case IS_DOUBLE:
            return LILTG(type_double);
        case IS_STRING:
            return LILTG(type_string);
        case _IS_BOOL:
        case IS_TRUE:
        case IS_FALSE:
            return LILTG(type_boolean);
        case IS_NULL:
            return LILTG(type_null);
        case IS_OBJECT:
            return FUNC(of_ce, Z_OBJ_P(value)->ce);
        case IS_ARRAY:
            return LILTG(type_array);
        case IS_RESOURCE:
            return LILTG(type_resource);
        case IS_REFERENCE:
            return FUNC(of, Z_REFVAL_P(value));
        default:
            return LILTG(type_unknown);
    }
}

PHP_API zend_object *FUNC(of_type, int type, zend_object *object) {
    switch (type) {
        case IS_LONG:
            return LILTG(type_integer);
        case IS_DOUBLE:
            return LILTG(type_double);
        case IS_STRING:
            return LILTG(type_string);
        case _IS_BOOL:
        case IS_TRUE:
        case IS_FALSE:
            return LILTG(type_boolean);
        case IS_NULL:
            return LILTG(type_null);
        case IS_OBJECT:
            return FUNC(of_ce, object->ce);
        case IS_ARRAY:
            return LILTG(type_array);
        case IS_RESOURCE:
            return LILTG(type_integer);
        case IS_REFERENCE:
            zend_error(E_ERROR, "Their is no % for zend type %d.", CLASS_STR, type);
        default:
            return LILTG(type_unknown);
    }
}

PHP_API zend_object *FUNC(of_ce, zend_class_entry *ce) {
    zval zv, *ptr;

    if (!(ptr = zend_hash_find(&LILTG(data.types), ce->name))) {
        ZVAL_OBJ(&zv, FUNC(enclose, CTOR(ce->name, ce)));
        if (zend_hash_add(&LILTG(data.types), ce->name, &zv)) {
            zval_copy_ctor(&zv);
        }
        ptr = &zv;
    }

    return Z_OBJ_P(ptr);
}

PHP_API zend_object *FUNC(of_class_name, zend_string *class_name) {
    zval zv, *ptr;
    zend_class_entry *ce;

    if (!(ptr = zend_hash_find(&LILTG(data.types), class_name))) {
        if (!(ce = zend_lookup_class(class_name))) {
            zend_error(E_ERROR, "Invalid class name provided, %s::class does not exists.", ZSTR_VAL(class_name));
        }
        ZVAL_OBJ(&zv, FUNC(enclose, CTOR(ce->name, ce)));
        if (zend_hash_add(&LILTG(data.types), ce->name, &zv)){
            zval_copy_ctor(&zv);
        }
        ptr = &zv;
    }

    return Z_OBJ_P(ptr);
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