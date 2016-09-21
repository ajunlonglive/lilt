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

#ifndef LILT_ENUM_H
#define LILT_ENUM_H

#include "lilt.h"

#define Enum Enum
#define EnumCe EXT_CLASS_CE(Enum)
#define EnumOh EXT_CLASS_OH(Enum)
#define EnumFunc(name, ...) EXT_CLASS_FUNC(Enum, name, __VA_ARGS__)

/**
 * API
 * * * * * * * * * */
EXT_CLASS_INIT_FUNCTION(Enum);
EXT_CLASS_SHUTDOWN_FUNCTION(Enum);
zend_object *EnumFunc(create_object, zend_class_entry *ce);

/**
 * Class entry
 * * * * * * * * * */
extern EXT_CLASS_CLASS_ENTRY(Enum);
int EnumFunc(interface_gets_implemented, zend_class_entry *parent, zend_class_entry *ce);

/**
 * Object handlers
 * * * * * * * * * */
EXT_CLASS_OBJECT_HANDLERS(Enum);
void EnumFunc(write_property, zval *object, zval *member, zval *value, void **cache_slot);

#endif /* LILT_ENUM_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */