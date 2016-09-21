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

#include "classes/comparable.h"
#include "zend_interfaces.h"

#define CLASS Comparable
#include "gen/class.h"

CLASS_ENTRY;
NO_METHODS;

INIT_FUNCTION {
    INIT_INTERFACE;
    INIT_HANDLERS;
    CE->interface_gets_implemented = MEM(interface_gets_implemented);
    OH.compare = MEM(compare);
    OH.compare_objects = MEM(compare_objects);
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

int FUNC(compare, zval *result, zval *op1, zval *op2) {
    zval *value, *comparable, operator;
    zend_string *name = z_string("__compare");
    zend_function *fn;

    if (INSTANCE_OF_P(op1, CE)) {
        comparable = op1;
        value = op2;
        ZVAL_OBJ(&operator, OperatorMem(operators)[EG(current_execute_data)->opline->opcode]);
    } else {
        comparable = op2;
        value = op1;
        if (EG(current_execute_data)->opline->opcode == ZEND_IS_SMALLER) {
            ZVAL_OBJ(&operator, OperatorMem(operators)[LILT_IS_GREATER]);
        } else if(EG(current_execute_data)->opline->opcode == ZEND_IS_SMALLER_OR_EQUAL) {
            ZVAL_OBJ(&operator, OperatorMem(operators)[LILT_IS_GREATER_OR_EQUAL]);
        } else {
            ZVAL_OBJ(&operator, OperatorMem(operators)[EG(current_execute_data)->opline->opcode]);
        }
    }
    fn = zend_hash_find_ptr(&Z_OBJ_P(comparable)->ce->function_table, name);
    zend_string_release(name);
    Z_TRY_ADDREF(operator);
    if (fn && zend_call_method_with_2_params(comparable, Z_OBJ_P(comparable)->ce, &fn, "__compare", result, &operator, value)) {
        return Z_TYPE_P(result) != IS_LONG
            ? FAILURE
            : SUCCESS;
    }

    return FAILURE;
}

int FUNC(compare_objects, zval *object1, zval *object2) {
    zval result;

    return FUNC(compare, &result, object1, object2) == SUCCESS ? (int) Z_LVAL(result) : 1;
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