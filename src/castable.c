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

#include "classes/castable.h"
#include "zend_interfaces.h"

#define CLASS Castable
#include "gen/class.h"

CLASS_ENTRY;
NO_METHODS;

INIT_FUNCTION {
    INIT_INTERFACE;
    INIT_HANDLERS;
    CE->interface_gets_implemented = MEM(interface_gets_implemented);
    OH.cast_object = MEM(cast_object);
}

SHUTDOWN_FUNCTION { }

zend_object *FUNC(create_object, zend_class_entry *ce) {
    zend_object *object;

    object = zend_objects_new(ce);
    object_properties_init(object, ce);
    object->handlers = &OH;

    return object;
}

int FUNC(interface_gets_implemented, zend_class_entry *iface, zend_class_entry *ce) {
    if (ce->create_object != NULL) {
        zend_error(E_ERROR, "%s interface can only be used on userland classes.", CLASS_STR);
    }
    ce->create_object = MEM(create_object);

    return SUCCESS;
}

int FUNC(cast_object, zval *readobj, zval *retval, int zend_type) {
    zval type;
    zend_string *name = z_string("__cast");
    zend_function *fn = zend_hash_find_ptr(&Z_OBJ_P(readobj)->ce->function_table, name);

    zend_string_release(name);
    ZVAL_TYPEOF_TYPE(&type, zend_type);
    if (fn && zend_call_method_with_1_params(readobj, Z_OBJ_P(readobj)->ce, &fn, "__cast", retval, &type)) {
        return Z_TYPE_P(retval) == IS_UNDEF || Z_TYPE_P(retval) == IS_NULL
            ? FAILURE
            : SUCCESS;
    }

    return FAILURE;
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