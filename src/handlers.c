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

#include "handlers.h"
#include "zend_interfaces.h"

EXT_HINIT_FUNCTION {
    EXT_SET_HANDLER(ZEND_DECLARE_INHERITED_CLASS);
    EXT_SET_HANDLER(ZEND_ADD_INTERFACE);
}

EXT_HFREE_FUNCTION {
    EXT_UNSET_HANDLER(ZEND_DECLARE_INHERITED_CLASS);
    EXT_UNSET_HANDLER(ZEND_ADD_INTERFACE);
}

static void on_class_inheritance(zend_class_entry *ce, zend_class_entry *parent) {
    if (parent == TypedCe || instanceof_function(parent, TypedCe)) {
        zval type;

        zend_hash_del(&ce->constants_table, LILTG(zstr.type));
        TypeFunc(zval_of_ce, ce, &type);
        zend_declare_class_constant(ce, ZSTR_VAL(LILTG(zstr.type)), ZSTR_LEN(LILTG(zstr.type)), &type);
    }
    if (parent == IStaticInitCe || instanceof_function(parent, IStaticInitCe)) {
        zval retval;
        zend_string *name = z_string("__static");
        zend_function *__static = ce->get_static_method
            ? ce->get_static_method(ce, name)
            : zend_std_get_static_method(ce, name, NULL);

        if (UNEXPECTED(__static != NULL) && __static->common.scope == ce &&
            zend_call_method_with_0_params(NULL, ce, &__static, "__static", &retval)) {
            zval_ptr_dtor(&retval);
        }
    }
    if (parent == EnumCe || instanceof_function(parent, EnumCe)) {
        zend_object *object;
        zend_class_constant *constant;
        zend_string *key;
        zend_class_entry *ce_enum = parent;

        ce->create_object = EnumMem(create_object);
        ZEND_HASH_FOREACH_STR_KEY_PTR(&ce->constants_table, key, constant)
            if (Z_TYPE(constant->value) != IS_OBJECT) {
                zval tmp;

                ZVAL_COPY(&tmp, &constant->value);
                object = zend_objects_new(ce);
                object_properties_init(object, ce);

                ZVAL_OBJ(&constant->value, object);
                zend_update_property_str(ce, &constant->value, STR_AND_LEN("name"), zend_string_copy(key));
                zend_update_property(ce, &constant->value, STR_AND_LEN("value"), &tmp);
                object->handlers = &(EnumOh);
            } else if (instanceof_function(Z_OBJ(constant->value)->ce, EnumCe)) {
                zval *value, tmp;

                value = zend_read_property(Z_OBJ(constant->value)->ce, &constant->value, STR_AND_LEN("value"), 0, &tmp);
                object = zend_objects_new(ce);
                object_properties_init(object, ce);

                ZVAL_OBJ(&constant->value, object);
                zend_update_property_str(ce, &constant->value, STR_AND_LEN("name"), zend_string_copy(key));
                zend_update_property(ce, &constant->value, STR_AND_LEN("value"), value);
                object->handlers = &(EnumOh);
            }
        ZEND_HASH_FOREACH_END();
        while(ce_enum) {
            ZEND_HASH_FOREACH_STR_KEY_PTR(&ce_enum->constants_table, key, constant)
                if (Z_TYPE(constant->value) != IS_OBJECT) {
                    zval value, cst;

                    ZVAL_COPY(&value, &constant->value);
                    object = zend_objects_new(ce);
                    object_properties_init(object, ce);

                    ZVAL_OBJ(&cst, object);
                    zend_update_property_str(ce, &cst, STR_AND_LEN("name"), zend_string_copy(key));
                    zend_update_property(ce, &cst, STR_AND_LEN("value"), &value);
                    object->handlers = &(EnumOh);

                    zend_hash_del(&ce->constants_table, key);
                    zend_declare_class_constant(ce, ZSTR_VAL(key), ZSTR_LEN(key), &cst);
                } else if (instanceof_function(Z_OBJ(constant->value)->ce, EnumCe)) {
                    zval *value, tmp, cst;

                    value = zend_read_property(Z_OBJ(constant->value)->ce, &constant->value, STR_AND_LEN("value"), 0, &tmp);
                    object = zend_objects_new(ce);
                    object_properties_init(object, ce);

                    ZVAL_OBJ(&cst, object);
                    zend_update_property_str(ce, &cst, STR_AND_LEN("name"), zend_string_copy(key));
                    zend_update_property(ce, &cst, STR_AND_LEN("value"), value);
                    object->handlers = &(EnumOh);

                    zend_hash_del(&ce->constants_table, key);
                    zend_declare_class_constant(ce, ZSTR_VAL(key), ZSTR_LEN(key), &cst);
                }
            ZEND_HASH_FOREACH_END();
            ce_enum = ce_enum->parent;
        }
    }
}

EXT_HANDLER_FUNCTION(ZEND_DECLARE_INHERITED_CLASS) {
    zend_class_entry *ce, *parent;
    zval *lcname, *rtd_key;

    lcname = RT_CONSTANT(&EX(func)->op_array, EX(opline)->op1);
    rtd_key = lcname + 1;
    ce = zend_hash_find_ptr(EG(class_table), Z_STR_P(rtd_key));
    parent = Z_CE_P(EX_VAR(EX(opline)->op2.var));
    if (UNEXPECTED(ce != NULL && parent != NULL)) {
        on_class_inheritance(ce, parent);
    }

    return ZEND_USER_OPCODE_DISPATCH;
}

EXT_HANDLER_FUNCTION(ZEND_ADD_INTERFACE) {
    zend_class_entry *parent;
    zend_class_entry *ce = Z_CE_P(EX_VAR(EX(opline)->op1.var));

    parent = CACHED_PTR(Z_CACHE_SLOT_P(EX_CONSTANT(EX(opline)->op2)));
    if (UNEXPECTED(parent == NULL)) {
        parent = zend_fetch_class_by_name(Z_STR_P(EX_CONSTANT(EX(opline)->op2)), EX_CONSTANT(EX(opline)->op2) + 1, ZEND_FETCH_CLASS_INTERFACE);
        if (UNEXPECTED(parent == NULL)) {
            return ZEND_USER_OPCODE_DISPATCH;
        }
        CACHE_PTR(Z_CACHE_SLOT_P(EX_CONSTANT(EX(opline)->op2)), parent);
    }
    if (UNEXPECTED(ce != NULL && parent != NULL)) {
        on_class_inheritance(ce, parent);
    }

    return ZEND_USER_OPCODE_DISPATCH;
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */