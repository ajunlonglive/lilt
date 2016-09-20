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

/**
 * API
 * todo add assignement:
 * ZEND_QM_ASSIGN,
 * ZEND_ASSIGN_ADD,
 * ZEND_ASSIGN_SUB,
 * ZEND_ASSIGN_MUL,
 * ZEND_ASSIGN_DIV,
 * ZEND_ASSIGN_MOD,
 * ZEND_ASSIGN_SL,
 * ZEND_ASSIGN_SR,
 * ZEND_ASSIGN_BW_OR,
 * ZEND_ASSIGN_BW_AND,
 * ZEND_ASSIGN_BW_XOR,
 * ZEND_ASSIGN,
 * ZEND_ASSIGN_REF,
 * * * * * * * * * */
EXT_CLASS_INIT_FUNCTION(Operable);
static int OperableMem(opcodes)[] = {
    ZEND_ADD,
    ZEND_SUB,
    ZEND_MUL,
    ZEND_DIV,
    ZEND_MOD,
    ZEND_SL,
    ZEND_SR,
    ZEND_BW_OR,
    ZEND_BW_AND,
    ZEND_BW_XOR,
    ZEND_IS_IDENTICAL,
    ZEND_IS_NOT_IDENTICAL,
    ZEND_IS_EQUAL,
    ZEND_IS_NOT_EQUAL,
    ZEND_IS_SMALLER,
    ZEND_IS_SMALLER_OR_EQUAL,
    ZEND_CAST,
    0
};
static const char* OperableMem(opconsts)[] = {
    "Add",
    "Sub",
    "Mul",
    "Div",
    "Mod",
    "Sl",
    "Sr",
    "BwOr",
    "BwAnd",
    "BwXor",
    "Identical",
    "NotIdentical",
    "Equal",
    "NotEqual",
    "Smaller",
    "SmallerOrEqual",
    "Cast",
    NULL
};

/**
 * Class entry
 * * * * * * * * * */
extern EXT_CLASS_CLASS_ENTRY(Operable);

#endif /* LILT_OPERABLE_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */