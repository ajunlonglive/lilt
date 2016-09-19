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

#include "classes/enum.h"

#define CLASS Enum
#include "gen/class.h"

CLASS_ENTRY;
NO_METHODS;

INIT_FUNCTION {
    INIT_INTERFACE;
    INIT_HANDLERS;
    OH.write_property = MEM(write_property);
}

void FUNC(write_property, zval *object, zval *member, zval *value, void **cache_slot) {
    if (zend_string_equals_literal(Z_STR_P(member), "name") ||
        zend_string_equals_literal(Z_STR_P(member), "value")) {
        zend_error(E_ERROR, "Cannot set immutable property %s::$%s.", ZSTR_VAL(Z_OBJ_P(object)->ce->name), Z_STRVAL_P(member));
    }

    return zend_std_write_property(object, member, value, cache_slot);
}

#undef CLASS

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */