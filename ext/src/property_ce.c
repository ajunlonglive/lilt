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

#include "classes/type/property.h"

#define CUSTOM_STRUCT
#define CLASS_NAME Type_PropertyName
#define CLASS Type_Property
#include "gen/class.h"

CLASS_ENTRY;

CEINIT_FUNCTION {
    METHODS_BEGIN
    METHODS_END
    INIT_CLASS;
    CE->ce_flags |= ZEND_ACC_FINAL;
    CE->create_object = MEM(create_object);
}

PHP_API zend_object *FUNC(create_object, zend_class_entry *ce) {
    return FUNC(enclose, CTOR(NULL));
}

#undef CUSTOM_STRUCT
#undef CLASS_NAME
#undef CLASS

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */