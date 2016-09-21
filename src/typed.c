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

#include "classes/typed.h"

#define CLASS Typed
#include "gen/class.h"

CLASS_ENTRY;
const NO_METHODS;

INIT_FUNCTION {
    INIT_INTERFACE;
    CE->interface_gets_implemented = MEM(interface_gets_implemented);
}

SHUTDOWN_FUNCTION { }

int FUNC(interface_gets_implemented, zend_class_entry *iface, zend_class_entry *ce) {
    zval type;

    zend_hash_del(&ce->constants_table, LILTG(zstr.type));
    ZVAL_TYPEOF_CE(&type, ce);
    zend_declare_class_constant(ce, ZSTR_VAL(LILTG(zstr.type)), ZSTR_LEN(LILTG(zstr.type)), &type);

    return SUCCESS;
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