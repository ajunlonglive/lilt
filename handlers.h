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

#ifndef LILT_HANDLERS_H
#define LILT_HANDLERS_H

#include "lilt.h"

EXT_HINIT_FUNCTION;
EXT_HFREE_FUNCTION;
EXT_HANDLER_FUNCTION(ZEND_CASE);
EXT_HANDLER_FUNCTION(ZEND_CAST);
EXT_HANDLER_FUNCTION(ZEND_IS_EQUAL);
EXT_HANDLER_FUNCTION(ZEND_IS_NOT_EQUAL);
EXT_HANDLER_FUNCTION(ZEND_IS_IDENTICAL);
EXT_HANDLER_FUNCTION(ZEND_IS_NOT_IDENTICAL);

#endif /* LILT_HANDLERS_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
