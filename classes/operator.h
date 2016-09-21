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

#ifndef LILT_OPERATOR_H
#define LILT_OPERATOR_H

#include "lilt.h"

#define Operator Operator
#define OperatorCe EXT_CLASS_CE(Operator)
#define OperatorMem(name) EXT_CLASS_MEM(Operator, name)

#define LILT_IS_GREATER ZEND_CAST+1
#define LILT_IS_GREATER_OR_EQUAL ZEND_CAST+2

/**
 * API
 * * * * * * * * * */
EXT_CLASS_INIT_FUNCTION(Operator);
EXT_CLASS_SHUTDOWN_FUNCTION(Operator);
zend_object *OperatorMem(operators)[LILT_IS_GREATER_OR_EQUAL+1];
static int OperatorMem(opcodes)[] = {
    ZEND_ADD, ZEND_SUB, ZEND_MUL, ZEND_DIV, ZEND_MOD, ZEND_SL, ZEND_SR, ZEND_CONCAT, ZEND_BW_OR, ZEND_BW_AND,
    ZEND_BW_XOR, ZEND_IS_IDENTICAL, ZEND_IS_NOT_IDENTICAL, ZEND_IS_EQUAL, ZEND_IS_NOT_EQUAL, ZEND_IS_SMALLER,
    ZEND_IS_SMALLER_OR_EQUAL, ZEND_CAST, LILT_IS_GREATER, LILT_IS_GREATER_OR_EQUAL, 0
};
static const char* OperatorMem(opnames)[] = {
    "ADD", "SUB", "MUL", "DIV", "MOD", "SL", "SR", "CONCAT", "BW_OR", "BW_AND", "BW_XOR", "IDENTICAL", "NOT_IDENTICAL",
    "EQUAL", "NOT_EQUAL", "SMALLER", "SMALLER_OR_EQUAL", "CAST", "GREATER", "GREATER_OR_EQUAL", NULL
};

/**
 * Class entry
 * * * * * * * * * */
extern EXT_CLASS_CLASS_ENTRY(Operator);

#endif /* LILT_OPERATOR_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */