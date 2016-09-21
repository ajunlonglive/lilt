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

#include "classes/operator.h"

#define CLASS Operator
#include "gen/class.h"

CLASS_ENTRY;
NO_METHODS;

INIT_FUNCTION {
    const int *opcode = MEM(opcodes);
    const char *const *opnames = MEM(opnames);

    INIT_CLASS;
    CE->ce_flags |= ZEND_ACC_FINAL;
    zend_class_implements(CE, 1, EnumCe);

//    while (*opcode) {
//        zval operator;
//        zend_object *object;
//
//        object = zend_objects_new(CE);
//        ZVAL_OBJ(&operator, object);
//        Z_TRY_ADDREF(operator);
//        zend_update_property_string(CE, &operator, STR_AND_LEN("name"), *opnames);
//        zend_update_property_long(CE, &operator, STR_AND_LEN("value"), *opcode);
//        object->handlers = &EnumOh;
//        MEM(operators)[*opcode] = object;
//
//        zend_declare_class_constant(CE, *opnames, strlen(*opnames), &operator);
//
//        opnames++;
//        opcode++;
//    }
}

SHUTDOWN_FUNCTION {
//    if (zend_hash_num_elements(&OperatorCe->constants_table)) {
//        zend_class_constant *c;
//        zend_string *k;
//        ZEND_HASH_FOREACH_STR_KEY_PTR(&OperatorCe->constants_table, k, c)
//            zval_ptr_dtor(&c->value);
//            if (c->doc_comment && c->ce == OperatorCe) {
//                zend_string_release(c->doc_comment);
//            }
//            zend_hash_del(&OperatorCe->constants_table, k);
//        ZEND_HASH_FOREACH_END();
//        zend_hash_destroy(&OperatorCe->constants_table);
//    }
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