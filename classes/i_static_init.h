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

#ifndef LILT_I_STATIC_INIT_H
#define LILT_I_STATIC_INIT_H

#include "lilt.h"

#define IStaticInit IStaticInit
#define IStaticInitFunc(name, ...) EXT_CLASS_FUNC(IStaticInit, name, __VA_ARGS__)

/**
 * API
 * * * * * * * * * */
EXT_CLASS_INIT_FUNCTION(IStaticInit);

/**
 * Class entry
 * * * * * * * * * */
extern EXT_CLASS_CLASS_ENTRY(IStaticInit);
int IStaticInitFunc(interface_gets_implemented, zend_class_entry *iface, zend_class_entry *ce);

#endif /* LILT_I_STATIC_INIT_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */