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
//    if (intern->is_mocking && intern->ce) {
//        intern->ce->parent->create_object = NULL;
//        intern->ce->parent->get_static_method = NULL;
//    }
//    if (intern->mock) {
//        intern->mock = NULL;
//        if (intern->ce) {
//            intern->ce->create_object = NULL;
//            intern->ce->get_static_method = NULL;
//        }
//    }
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

//PHP_API zend_object *FUNC(create_mock, zend_class_entry *ce) {
//    zval *mock = zend_hash_find(&LILTG(data.mocks), ce->name);
//    zend_object *object = zend_objects_new(Z_THIS_P(mock)->ce);
//    object_properties_init(object, Z_THIS_P(mock)->ce);
//    return object;
//}
//
//PHP_API zend_function *FUNC(get_static_method_mock, zend_class_entry *ce, zend_string *name) {
//    return zend_std_get_static_method(Z_THIS_P(zend_hash_find(&LILTG(data.mocks), ce->name))->ce, name, NULL);
//}

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
    Z_TRY_ADDREF_P(rv);
    return SUCCESS;
}

PHP_API int FUNC(zval_of_ce, zend_class_entry *ce, zval *rv) {
    zval zv, *ptr;
    ptr = zend_hash_find(&LILTG(data.types), ce->name);
    if (!ptr) {
        ZVAL_OBJ(&zv, FUNC(enclose, CTOR(ce->name, ce)));
        if (zend_hash_add(&LILTG(data.types), ce->name, &zv)) {
            zval_copy_ctor(&zv);
        }
        ptr = &zv;
    }
    ZVAL_OBJ(rv, Z_OBJ_P(ptr));
    Z_TRY_ADDREF_P(rv);
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
            if (zend_hash_add(&LILTG(data.types), ce->name, &zv)){
                zval_copy_ctor(&zv);
            }
            ptr = &zv;
        } else {
            ZVAL_NULL(rv);
            return FAILURE;
        }
    }
    ZVAL_OBJ(rv, Z_OBJ_P(ptr));
    Z_TRY_ADDREF_P(rv);
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