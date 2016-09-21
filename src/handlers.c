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
    int *ptr = OperableMem(opcodes);
    while (*ptr) {
        zend_set_user_opcode_handler((zend_uchar) *ptr, EXT_HANDLER(Operable));
        ptr++;
    }
}

EXT_HFREE_FUNCTION {
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

EXT_HANDLER_FUNCTION(Operable) {
    zval *op1, *op2, operator, result;

    if ((op1 = get_ptr(execute_data, EX(opline)->op1, EX(opline)->op1_type)) && Z_TYPE_P(op1) == IS_OBJECT &&
        (op2 = get_ptr(execute_data, EX(opline)->op2, EX(opline)->op2_type))) {
        if (instanceof_function(Z_OBJ_P(op1)->ce, OperableCe)) {
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