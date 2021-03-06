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
    int *ptr = OperableMem(opcodes);
    while (*ptr) {
        zend_set_user_opcode_handler((zend_uchar) *ptr, EXT_HANDLER(Operable));
        ptr++;
    }
}

EXT_HFREE_FUNCTION {
    EXT_UNSET_HANDLER(ZEND_DECLARE_INHERITED_CLASS);
    EXT_UNSET_HANDLER(ZEND_ADD_INTERFACE);
    int *ptr = OperableMem(opcodes);
    while (*ptr) {
        zend_set_user_opcode_handler((zend_uchar) *ptr, NULL);
        ptr++;
    }
}


static zend_never_inline ZEND_COLD void zval_undefined_cv(uint32_t var, const zend_execute_data *execute_data) {
    zend_string *cv = EX(func)->op_array.vars[var];
    zend_error(E_NOTICE, "Undefined variable: %s", ZSTR_VAL(cv));
}

static zend_never_inline zval *get_zval_cv_lookup(zval *ptr, uint32_t var, int type, const zend_execute_data *execute_data) {
    switch (type) {
        case BP_VAR_R:
        case BP_VAR_UNSET:
            zval_undefined_cv(var, execute_data);
        case BP_VAR_IS:
            ptr = &EG(uninitialized_zval);
            break;
        case BP_VAR_RW:
            zval_undefined_cv(var, execute_data);
        case BP_VAR_W:
            ZVAL_NULL(ptr);
            break;
        default:
            break;
    }
    return ptr;
}

static zend_always_inline zval *get_ptr(const zend_execute_data *execute_data, znode_op op, int type) {
    if (type == IS_CONST) {
        return EX_CONSTANT(op);
    }
    zval *ret = EX_VAR(op.var);

    if (UNEXPECTED(Z_TYPE_P(ret) == IS_UNDEF)) {
        return get_zval_cv_lookup(ret, op.var, type, execute_data);
    }

    return ret;
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
        zend_string_release(name);
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
                object->handlers = &EnumOh;
            }
        ZEND_HASH_FOREACH_END();
        while(ce_enum) {
            ZEND_HASH_FOREACH_STR_KEY_PTR(&ce_enum->constants_table, key, constant)
                if (Z_TYPE(constant->value) == IS_OBJECT && instanceof_function(Z_OBJ(constant->value)->ce, EnumCe)) {
                    zval *value, tmp, cst;

                    value = zend_read_property(Z_OBJ(constant->value)->ce, &constant->value, STR_AND_LEN("value"), 0, &tmp);
                    object = zend_objects_new(ce);
                    object_properties_init(object, ce);

                    ZVAL_OBJ(&cst, object);
                    zend_update_property_str(ce, &cst, STR_AND_LEN("name"), zend_string_copy(key));
                    zend_update_property(ce, &cst, STR_AND_LEN("value"), value);
                    object->handlers = &EnumOh;

                    zend_hash_del(&ce->constants_table, key);
                    zend_declare_class_constant(ce, ZSTR_VAL(key), ZSTR_LEN(key), &cst);
                }
            ZEND_HASH_FOREACH_END();
            ce_enum = ce_enum->parent;
        }
    }
}

EXT_HANDLER_FUNCTION(Operable) {
    zval *op1, *op2, operator, result;

    if ((op1 = get_ptr(execute_data, EX(opline)->op1, EX(opline)->op1_type)) &&
        Z_TYPE_P(op1) == IS_OBJECT && instanceof_function(Z_OBJ_P(op1)->ce, OperableCe) &&
        (op2 = get_ptr(execute_data, EX(opline)->op2, EX(opline)->op2_type))) {
        zend_string *name = z_string("__operate");
        zend_function *__operate = zend_hash_find_ptr(&Z_OBJ_P(op1)->ce->function_table, name);

        zend_string_release(name);
        ZVAL_OBJ(&operator, OperatorMem(operators)[EX(opline)->opcode]);
        Z_TRY_ADDREF(operator);
        if (UNEXPECTED(__operate != NULL) &&
            zend_call_method_with_2_params(op1, Z_OBJ_P(op1)->ce, &__operate, "__operate", &result, &operator, op2)) {
            if (Z_TYPE(result) != IS_UNDEF) {
                ZVAL_COPY(EX_VAR(EX(opline)->result.var), &result);
                EX(opline)++;

                return ZEND_USER_OPCODE_CONTINUE;
            }
        }
    }

    return ZEND_USER_OPCODE_DISPATCH;
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