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

#ifndef LILT_CASTABLE_H
#define LILT_CASTABLE_H

#include "lilt.h"

#define Castable Castable
#define CastableCe EXT_CLASS_CE(Castable)
#define CastableMem(name) EXT_CLASS_MEM(Castable, name)
#define CastableFunc(name, ...) EXT_CLASS_FUNC(Castable, name, __VA_ARGS__)

/**
 * API
 * * * * * * * * * */
EXT_CLASS_INIT_FUNCTION(Castable);
EXT_CLASS_SHUTDOWN_FUNCTION(Castable);
zend_object *CastableFunc(create_object, zend_class_entry *ce);

/**
 * Class entry
 * * * * * * * * * */
extern EXT_CLASS_CLASS_ENTRY(Castable);
int CastableFunc(interface_gets_implemented, zend_class_entry *iface, zend_class_entry *ce);

/**
 * Object handlers
 * * * * * * * * * */
EXT_CLASS_OBJECT_HANDLERS(Castable);
int CastableFunc(cast_object, zval *readobj, zval *retval, int type);

#endif /* LILT_CASTABLE_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */