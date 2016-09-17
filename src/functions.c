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

#include "functions.h"

PHP_API PHP_FUNCTION(typeof) { /* {{{ */
    int num_args = ZEND_CALL_NUM_ARGS(execute_data);
    if (num_args == 1) {
        TypeMem(zval_of)(ZEND_CALL_ARG(execute_data, 1), return_value);
    } else {
        zend_internal_type_error(1, "typeof() expects 1 parameter, %d given", num_args);
    }
} /* }}} */

PHP_API PHP_FUNCTION(classtype) { /* {{{ */
    zval *value;
    int num_args = ZEND_CALL_NUM_ARGS(execute_data);
    if (num_args == 1) {
        value = ZEND_CALL_ARG(execute_data, 1);
        ZVAL_DEREF(value);
        if (Z_TYPE_P(value) == IS_STRING) {
            TypeFunc(zval_of_classname, value, return_value);
        } else {
            zend_internal_type_error(
                1, "classtype() expects parameter 1 to be string, %s given", zend_zval_type_name(value)
            );
        }
    } else {
        zend_internal_type_error(1, "classtype() expects 1 parameter, %d given", num_args);
    }
} /* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */