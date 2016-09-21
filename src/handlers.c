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

#define OP1_ZPTR (op1 = znode_op_zval_ptr(execute_data, EX(opline)->op1, EX(opline)->op1_type))
#define OP2_ZPTR (op2 = znode_op_zval_ptr(execute_data, EX(opline)->op2, EX(opline)->op2_type))

EXT_HINIT_FUNCTION {
    EXT_SET_HANDLER(ZEND_CASE);
    EXT_SET_HANDLER(ZEND_CAST);
    EXT_SET_HANDLER(ZEND_IS_EQUAL);
    EXT_SET_HANDLER(ZEND_IS_NOT_EQUAL);
    EXT_SET_HANDLER(ZEND_IS_IDENTICAL);
    EXT_SET_HANDLER(ZEND_IS_NOT_IDENTICAL);
}

EXT_HFREE_FUNCTION {
    EXT_UNSET_HANDLER(ZEND_CASE);
    EXT_UNSET_HANDLER(ZEND_CAST);
    EXT_UNSET_HANDLER(ZEND_IS_EQUAL);
    EXT_UNSET_HANDLER(ZEND_IS_NOT_EQUAL);
    EXT_UNSET_HANDLER(ZEND_IS_IDENTICAL);
    EXT_UNSET_HANDLER(ZEND_IS_NOT_IDENTICAL);
}

EXT_HANDLER_FUNCTION(ZEND_CAST) {
    zval result, *op1;

    if (EX(opline)->extended_value == IS_ARRAY) {
        if (OP1_ZPTR && INSTANCE_OF_P(op1, CastableCe)) {
            Z_OBJ_HT_P(op1)->cast_object(op1, &result, IS_ARRAY);
            if (Z_TYPE(result) == IS_ARRAY) {
                ZVAL_ARR(EX_VAR(EX(opline)->result.var), Z_ARR(result));
                EX(opline)++;

                return ZEND_USER_OPCODE_CONTINUE;
            }
        }
    }
    else if (EX(opline)->extended_value == IS_STRING) {
        if (OP1_ZPTR && INSTANCE_OF_P(op1, TypeCe)) {
            ZVAL_STR(EX_VAR(EX(opline)->result.var), ((TypePhpStruct *)Z_OBJ_P(op1))->intern->type_name);
            Z_TRY_ADDREF_P(EX_VAR(EX(opline)->result.var));
            EX(opline)++;

            return ZEND_USER_OPCODE_CONTINUE;
        }
    }

    return ZEND_USER_OPCODE_DISPATCH;
}

EXT_HANDLER_FUNCTION(ZEND_CASE) {
    zval result, *op1, *op2;

    if (OP1_ZPTR && Z_TYPE_P(op1) == IS_OBJECT && OP2_ZPTR && Z_TYPE_P(op2) == IS_OBJECT) {
        ZVAL_BOOL(&result, zend_is_identical(op1, op2));
        ZVAL_COPY(EX_VAR(EX(opline)->result.var), &result);
        EX(opline)++;

        return ZEND_USER_OPCODE_CONTINUE;
    }

    return ZEND_USER_OPCODE_DISPATCH;
}

EXT_HANDLER_FUNCTION(ZEND_IS_EQUAL) {
    zval result, *op1, *op2;

    if (OP1_ZPTR && INSTANCE_OF_P(op1, TypeCe) &&
        OP2_ZPTR && INSTANCE_OF_P(op2, TypeCe)) {
        ZVAL_BOOL(&result, Z_OBJ_P(op1) == Z_OBJ_P(op2));
        ZVAL_COPY(EX_VAR(EX(opline)->result.var), &result);
        EX(opline)++;

        return ZEND_USER_OPCODE_CONTINUE;
    }

    return ZEND_USER_OPCODE_DISPATCH;
}

EXT_HANDLER_FUNCTION(ZEND_IS_NOT_EQUAL) {
    zval result, *op1, *op2;

    if (OP1_ZPTR && INSTANCE_OF_P(op1, TypeCe) &&
        OP2_ZPTR && INSTANCE_OF_P(op2, TypeCe)) {
        ZVAL_BOOL(&result, Z_OBJ_P(op1) != Z_OBJ_P(op2));
        ZVAL_COPY(EX_VAR(EX(opline)->result.var), &result);
        EX(opline)++;

        return ZEND_USER_OPCODE_CONTINUE;
    }

    return ZEND_USER_OPCODE_DISPATCH;
}

EXT_HANDLER_FUNCTION(ZEND_IS_IDENTICAL) {
    zval result, *op1, *op2;

    if (OP1_ZPTR && OP2_ZPTR) {
        if (IS_A_P(op1, TypeCe) && IS_A_P(op2, TypeCe)) {
            ZVAL_BOOL(EX_VAR(EX(opline)->result.var), Z_OBJ_P(op1) == Z_OBJ_P(op2));
            EX(opline)++;

            return ZEND_USER_OPCODE_CONTINUE;
        }
        if (INSTANCE_OF_P(op1, ComparableCe) && Z_OBJ_HT_P(op1)->compare(&result, op1, op2) == SUCCESS) {
            ZVAL_COPY(EX_VAR(EX(opline)->result.var), &result);
            EX(opline)++;

            return ZEND_USER_OPCODE_CONTINUE;
        }
        if (INSTANCE_OF_P(op2, ComparableCe) && Z_OBJ_HT_P(op2)->compare(&result, op1, op2) == SUCCESS) {
            ZVAL_COPY(EX_VAR(EX(opline)->result.var), &result);
            EX(opline)++;

            return ZEND_USER_OPCODE_CONTINUE;
        }
    }

    return ZEND_USER_OPCODE_DISPATCH;
}

EXT_HANDLER_FUNCTION(ZEND_IS_NOT_IDENTICAL) {
    zval result, *op1, *op2;

    if (OP1_ZPTR && OP2_ZPTR) {
        if (IS_A_P(op1, TypeCe) && IS_A_P(op2, TypeCe)) {
            ZVAL_BOOL(EX_VAR(EX(opline)->result.var), Z_OBJ_P(op1) != Z_OBJ_P(op2));
            EX(opline)++;

            return ZEND_USER_OPCODE_CONTINUE;
        }
        if (INSTANCE_OF_P(op1, ComparableCe) && Z_OBJ_HT_P(op1)->compare(&result, op1, op2) == SUCCESS) {
            ZVAL_COPY(EX_VAR(EX(opline)->result.var), &result);
            EX(opline)++;

            return ZEND_USER_OPCODE_CONTINUE;
        }
        if (INSTANCE_OF_P(op2, ComparableCe) && Z_OBJ_HT_P(op2)->compare(&result, op1, op2) == SUCCESS) {
            ZVAL_COPY(EX_VAR(EX(opline)->result.var), &result);
            EX(opline)++;

            return ZEND_USER_OPCODE_CONTINUE;
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