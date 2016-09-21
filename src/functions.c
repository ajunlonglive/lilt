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
    int num_args = EX_NUM_ARGS();

    if (num_args != 1) {
        zend_internal_type_error(1, "typeof() expects 1 parameter, %d given", num_args);
    }

    RETURN_TYPEOF(EX_ARG(1));
} /* }}} */

PHP_API PHP_FUNCTION(classtype) { /* {{{ */
    zval *value;
    int num_args = EX_NUM_ARGS();

    if (num_args == 1) {
        value = EX_ARG(1);
        if (Z_TYPE_P(value) == IS_STRING) {
            RETURN_TYPEOF_CLASS_NAME(Z_STR_P(value));
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