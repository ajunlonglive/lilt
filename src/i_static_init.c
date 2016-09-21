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

#include "classes/i_static_init.h"
#include "zend_interfaces.h"

#define CLASS IStaticInit
#include "gen/class.h"

CLASS_ENTRY;
const METHODS_BEGIN
    ABSTRACT_ME(__static, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
METHODS_END;

INIT_FUNCTION {
    INIT_INTERFACE;
    CE->interface_gets_implemented = MEM(interface_gets_implemented);
}

SHUTDOWN_FUNCTION { }

int FUNC(interface_gets_implemented, zend_class_entry *iface, zend_class_entry *ce) {
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