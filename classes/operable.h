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

#ifndef LILT_OPERABLE_H
#define LILT_OPERABLE_H

#include "lilt.h"

#define Operable Operable
#define OperableCe EXT_CLASS_CE(Operable)
#define OperableMem(name) EXT_CLASS_MEM(Operable, name)
#define OperableFunc(name, ...) EXT_CLASS_FUNC(Operable, name, __VA_ARGS__)

#define IS_OPERABLE_P(zv) (Z_TYPE_P(zv) == IS_OBJECT && instanceof_function(Z_OBJ_P(zv)->ce, OperableCe))
#define IS_OPERABLE(zv) IS_OPERABLE_P(&(zv))


/**
 * API
 * * * * * * * * * */
EXT_CLASS_INIT_FUNCTION(Operable);
EXT_CLASS_SHUTDOWN_FUNCTION(Operable);
zend_object *OperableFunc(create_object, zend_class_entry *ce);

/**
 * Class entry
 * * * * * * * * * */
extern EXT_CLASS_CLASS_ENTRY(Operable);
int OperableFunc(interface_gets_implemented, zend_class_entry *iface, zend_class_entry *ce);

/**
 * Object handlers
 * * * * * * * * * */
EXT_CLASS_OBJECT_HANDLERS(Operable);
int OperableFunc(do_operation, zend_uchar opcode, zval *result, zval *op1, zval *op2);

#endif /* LILT_OPERABLE_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */