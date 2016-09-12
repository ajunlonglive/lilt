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

#ifndef LILT_ARGINFO_H
#define LILT_ARGINFO_H

#define ARGINFO(name) arginfo_##name

#define ARGINFO_NONE(name) \
ZEND_BEGIN_ARG_INFO_EX(ARGINFO(name), 0, 0, 0) \
ZEND_END_ARG_INFO()

#define ARGINFO_ZVAL_RETURN_BOOL(name, z) \
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(ARGINFO(name), 0, 1, _IS_BOOL, 0, 0) \
    ZEND_ARG_INFO(0, z) \
ZEND_END_ARG_INFO()

#define ARGINFO_OPTIONAL_ZVAL(name, z) \
ZEND_BEGIN_ARG_INFO_EX(ARGINFO(name), 0, 0, 0) \
ZEND_ARG_TYPE_INFO(0, z, 0, 1) \
ZEND_END_ARG_INFO()

#define ARGINFO_OPTIONAL_ZVAL_OPTIONAL_ZVAL(name, z1, z2) \
ZEND_BEGIN_ARG_INFO_EX(ARGINFO(name), 0, 0, 0) \
ZEND_ARG_TYPE_INFO(0, z1, 0, 1) \
ZEND_ARG_TYPE_INFO(0, z2, 0, 1) \
ZEND_END_ARG_INFO()

#define ARGINFO_CALLABLE_OPTIONAL_ZVAL(name, c, z) \
ZEND_BEGIN_ARG_INFO_EX(ARGINFO(name), 0, 0, 1) \
ZEND_ARG_TYPE_INFO(0, c, IS_CALLABLE, 0) \
ZEND_ARG_TYPE_INFO(0, z, 0, 1) \
ZEND_END_ARG_INFO()

#define ARGINFO_OPTIONAL_STRING(name, s) \
ZEND_BEGIN_ARG_INFO_EX(ARGINFO(name), 0, 0, 0) \
ZEND_ARG_TYPE_INFO(0, s, IS_STRING, 0) \
ZEND_END_ARG_INFO()

#define ARGINFO_OPTIONAL_STRING_RETURN_STRING(name, s) \
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(ARGINFO(name), 0, 0, IS_STRING, 0, 0) \
ZEND_ARG_TYPE_INFO(0, s, IS_STRING, 0) \
ZEND_END_ARG_INFO()

#define ARGINFO_OPTIONAL_CALLABLE(name, c) \
ZEND_BEGIN_ARG_INFO_EX(ARGINFO(name), 0, 0, 0) \
ZEND_ARG_TYPE_INFO(0, c, IS_CALLABLE, 1) \
ZEND_END_ARG_INFO()

#define ARGINFO_CALLABLE(name, c) \
ZEND_BEGIN_ARG_INFO_EX(ARGINFO(name), 0, 0, 1) \
ZEND_ARG_TYPE_INFO(0, c, IS_CALLABLE, 0) \
ZEND_END_ARG_INFO()

#define ARGINFO_VARIADIC_ZVAL(name, v) \
ZEND_BEGIN_ARG_INFO_EX(ARGINFO(name), 0, 0, 0) \
ZEND_ARG_VARIADIC_INFO(0, v) \
ZEND_END_ARG_INFO()

#define ARGINFO_NONE_RETURN_LONG(name) \
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(ARGINFO(name), 0, 0, IS_LONG, 0, 0) \
ZEND_END_ARG_INFO()

#define ARGINFO_NONE_RETURN_STRING(name) \
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(ARGINFO(name), 0, 0, IS_STRING, 0, 0) \
ZEND_END_ARG_INFO()

#define ARGINFO_NONE_RETURN_OBJ(name, class_name) \
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(ARGINFO(name), 0, 0, IS_OBJECT, class_name, 1) \
ZEND_END_ARG_INFO()

#define ARGINFO_NONE_RETURN_BOOL(name) \
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(ARGINFO(name), 0, 0, _IS_BOOL, 0, 0) \
ZEND_END_ARG_INFO()

#define ARGINFO_VARIADIC_ZVAL_RETURN_BOOL(name, v) \
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(ARGINFO(name), 0, 0, _IS_BOOL, 0, 0) \
ZEND_ARG_VARIADIC_INFO(0, v) \
ZEND_END_ARG_INFO()

#define ARGINFO_NONE_RETURN_ARRAY(name) \
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(ARGINFO(name), 0, 0, IS_ARRAY, 0, 0) \
ZEND_END_ARG_INFO()

#define ARGINFO_LONG(name, i) \
ZEND_BEGIN_ARG_INFO_EX(ARGINFO(name), 0, 0, 1) \
ZEND_ARG_TYPE_INFO(0, i, IS_LONG, 0) \
ZEND_END_ARG_INFO()

#define ARGINFO_LONG_ZVAL(name, i, z) \
ZEND_BEGIN_ARG_INFO_EX(ARGINFO(name), 0, 0, 2) \
ZEND_ARG_TYPE_INFO(0, i, IS_LONG, 0) \
ZEND_ARG_INFO(0, z) \
ZEND_END_ARG_INFO()

#define ARGINFO_ZVAL_LONG(name, z, i) \
ZEND_BEGIN_ARG_INFO_EX(ARGINFO(name), 0, 0, 2) \
ZEND_ARG_INFO(0, z) \
ZEND_ARG_TYPE_INFO(0, i, IS_LONG, 0) \
ZEND_END_ARG_INFO()

#define ARGINFO_ZVAL(name, z) \
ZEND_BEGIN_ARG_INFO_EX(ARGINFO(name), 0, 0, 1) \
ZEND_ARG_INFO(0, z) \
ZEND_END_ARG_INFO()

#define ARGINFO_ZVAL_ZVAL(name, z1, z2) \
ZEND_BEGIN_ARG_INFO_EX(ARGINFO(name), 0, 0, 2) \
ZEND_ARG_INFO(0, z1) \
ZEND_ARG_INFO(0, z2) \
ZEND_END_ARG_INFO()

#define ARGINFO_ZVAL_OPTIONAL_ZVAL(name, z1, z2) \
ZEND_BEGIN_ARG_INFO_EX(ARGINFO(name), 0, 0, 1) \
ZEND_ARG_INFO(0, z1) \
ZEND_ARG_TYPE_INFO(0, z2, 0, 1) \
ZEND_END_ARG_INFO()

#define ARGINFO_LONG_VARIADIC_ZVAL(name, i, v) \
ZEND_BEGIN_ARG_INFO_EX(ARGINFO(name), 0, 0, 1) \
ZEND_ARG_TYPE_INFO(0, i, IS_LONG, 0) \
ZEND_ARG_VARIADIC_INFO(0, v) \
ZEND_END_ARG_INFO()

#endif /* LILT_ARGINFO_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */