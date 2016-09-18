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

#ifndef LILT_H
#define LILT_H

#include "liblilt.h"

#ifdef PHP_WIN32
#    define PHP_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#    define PHP_API __attribute__ ((visibility("default")))
#else
#    define PHP_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#ifdef ZTS
#define LILTG(v) TSRMG(lilt_globals_id, zend_lilt_globals *, v)
#else
#define LILTG(v) (lilt_globals.v)
#endif

#define LILT_EXT_NAME lilt
#define LILT_EXT_NAME_UC LILT
#define LILT_EXT_VERSION "0.0.1"

#define EXT_NAME LILT_EXT_NAME
#define EXT_NAME_UC LILT_EXT_NAME_UC
#define EXT_VERSION LILT_EXT_VERSION
#include "gen/ext.h"

EXT_EXTERN_MODULE_ENTRY_NX(LILT_EXT_NAME);

EXT_BEGIN_MODULE_GLOBALS_NX(LILT_EXT_NAME)
    zend_object *type_array;
    zend_object *type_boolean;
    zend_object *type_double;
    zend_object *type_integer;
    zend_object *type_null;
    zend_object *type_resource;
    zend_object *type_string;
    zend_object *type_unknown;
    struct {
        zend_string *type;
    } zstr;
    struct {
        HashTable types;
//        HashTable mocks;
    } data;
EXT_END_MODULE_GLOBALS_NX(LILT_EXT_NAME)

EXT_EXTERN_MODULE_GLOBALS_NX(LILT_EXT_NAME);

#include "classes.h"
#include "functions.h"
#include "handlers.h"
#include "utils.h"

#if defined(ZTS) && defined(COMPILE_DL_LILT)
ZEND_TSRMLS_CACHE_EXTERN();
#endif

#endif /* LILT_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */