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

#ifndef LILT_UTILS_H
#define LILT_UTILS_H

#include "lilt.h"

static inline void zval_p_dtor(zval *zv) { /* {{{ */
    zval_ptr_dtor(zv);
} /* }}} */

static inline int zend_hash_add_zval_ex(HashTable *ht, const char *str, size_t len, zval *data) { /* {{{ */
    zval *ret;

    ret = zend_symtable_str_update(ht, str, len, data);

    return ret ? SUCCESS : FAILURE;
} /* }}} */

static inline int zend_hash_add_string_ex(HashTable *ht, const char *str, size_t len, zend_string *data) { /* {{{ */
    zval *ret, tmp;

    ZVAL_STR_OR_NULL(&tmp, data);
    ret = zend_symtable_str_update(ht, str, len, &tmp);

    return ret ? SUCCESS : FAILURE;
} /* }}} */

static inline int zend_hash_add_long_ex(HashTable *ht, const char *str, size_t len, int data) { /* {{{ */
    zval *ret, tmp;

    ZVAL_LONG(&tmp, data);
    ret = zend_symtable_str_update(ht, str, len, &tmp);

    return ret ? SUCCESS : FAILURE;
} /* }}} */

static inline int zend_hash_add_bool_ex(HashTable *ht, const char *str, size_t len, zend_bool data) { /* {{{ */
    zval *ret, tmp;

    ZVAL_BOOL(&tmp, data);
    ret = zend_symtable_str_update(ht, str, len, &tmp);

    return ret ? SUCCESS : FAILURE;
} /* }}} */

#define zend_hash_add_zval(_ht, _key, _data) zend_hash_add_zval_ex(_ht, STR_AND_LEN(_key), _data)
#define zend_hash_add_string(_ht, _key, _data) zend_hash_add_string_ex(_ht, STR_AND_LEN(_key), _data)
#define zend_hash_add_long(_ht, _key, _data) zend_hash_add_long_ex(_ht, STR_AND_LEN(_key), _data)
#define zend_hash_add_bool(_ht, _key, _data) zend_hash_add_bool_ex(_ht, STR_AND_LEN(_key), _data)

static inline zval *znode_op_zval_ptr(const zend_execute_data *execute_data, znode_op op, int type) { /* {{{ */
    if (type == IS_CONST) {
        return EX_CONSTANT(op);
    }
    zend_string *cv;
    zval *ptr = EX_VAR(op.var);

    if (UNEXPECTED(Z_TYPE_P(ptr) == IS_UNDEF)) {
        switch (type) {
            case BP_VAR_R:
            case BP_VAR_UNSET:
                cv = EX(func)->op_array.vars[op.var];
                zend_error(E_NOTICE, "Undefined variable: %s", ZSTR_VAL(cv));
            case BP_VAR_IS:
                ptr = &EG(uninitialized_zval);
                break;
            case BP_VAR_RW:
                cv = EX(func)->op_array.vars[op.var];
                zend_error(E_NOTICE, "Undefined variable: %s", ZSTR_VAL(cv));
            case BP_VAR_W:
                ZVAL_NULL(ptr);
                break;
            default:
                break;
        }
    }

    return ptr;
} /* }}} */

#endif /* LILT_UTILS_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */