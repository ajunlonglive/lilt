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

EXT_HINIT_FUNCTION {
    EXT_SET_HANDLER(ZEND_DECLARE_INHERITED_CLASS);
    EXT_SET_HANDLER(ZEND_ADD_INTERFACE);
}

EXT_HFREE_FUNCTION {
    EXT_UNSET_HANDLER(ZEND_DECLARE_INHERITED_CLASS);
    EXT_UNSET_HANDLER(ZEND_ADD_INTERFACE);
}

EXT_HANDLER_FUNCTION(ZEND_DECLARE_INHERITED_CLASS) {
    zend_class_entry *ce, *parent;
    zval *lcname, *rtd_key;
    lcname = RT_CONSTANT(&EX(func)->op_array, EX(opline)->op1);
    rtd_key = lcname + 1;
    ce = zend_hash_find_ptr(EG(class_table), Z_STR_P(rtd_key));
    parent = Z_CE_P(EX_VAR(EX(opline)->op2.var));
    if (UNEXPECTED(ce != NULL && parent != NULL)) {
        if (parent == TypedCe || instanceof_function(parent, TypedCe)) {
            zval type;
            zend_hash_del(&ce->constants_table, LILTG(zstr.type));
            TypeFunc(zval_of_ce, ce, &type);
            zend_declare_class_constant(ce, ZSTR_VAL(LILTG(zstr.type)), ZSTR_LEN(LILTG(zstr.type)), &type);
            Z_TRY_ADDREF(type);
        }
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
    if (UNEXPECTED(parent != NULL)) {
        if (parent == TypedCe || instanceof_function(parent, TypedCe)) {
            zval type;
            zend_hash_del(&ce->constants_table, LILTG(zstr.type));
            TypeFunc(zval_of_ce, ce, &type);
            zend_declare_class_constant(ce, ZSTR_VAL(LILTG(zstr.type)), ZSTR_LEN(LILTG(zstr.type)), &type);
            Z_TRY_ADDREF(type);
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