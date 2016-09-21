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

#ifndef LILT_COMPARABLE_H
#define LILT_COMPARABLE_H

#include "lilt.h"

#define Comparable Comparable
#define ComparableCe EXT_CLASS_CE(Comparable)
#define ComparableMem(name) EXT_CLASS_MEM(Comparable, name)
#define ComparableFunc(name, ...) EXT_CLASS_FUNC(Comparable, name, __VA_ARGS__)

#define IS_COMPARABLE_P(zv) (Z_TYPE_P(zv) == IS_OBJECT && instanceof_function(Z_OBJ_P(zv)->ce, ComparableCe))
#define IS_COMPARABLE(zv) IS_COMPARABLE_P(&(zv))

/**
 * API
 * * * * * * * * * */
EXT_CLASS_INIT_FUNCTION(Comparable);
EXT_CLASS_SHUTDOWN_FUNCTION(Comparable);
zend_object *ComparableFunc(create_object, zend_class_entry *ce);

/**
 * Class entry
 * * * * * * * * * */
extern EXT_CLASS_CLASS_ENTRY(Comparable);
int ComparableFunc(interface_gets_implemented, zend_class_entry *iface, zend_class_entry *ce);

/**
 * Object handlers
 * * * * * * * * * */
EXT_CLASS_OBJECT_HANDLERS(Comparable);
int ComparableFunc(compare, zval *resul, zval *op1, zval *op2);
int ComparableFunc(compare_objects, zval *object1, zval *object2);

#endif /* LILT_COMPARABLE_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */