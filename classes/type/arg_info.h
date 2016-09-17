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

#ifndef LILT_TYPE_ARGINFO_H
#define LILT_TYPE_ARGINFO_H

#include "lilt.h"

#define Type_ArgInfo Type_ArgInfo
#define Type_ArgInfoName PHP_NSIZE(STRINGIZE(Type), "ArgInfo")
#define Type_ArgInfoStruct EXT_CLASS_STRUCT(Type_ArgInfo)
#define Type_ArgInfoCtor EXT_CLASS_CTOR(Type_ArgInfo)
#define Type_ArgInfoMem(name) EXT_CLASS_MEM(Type_ArgInfo, name)
#define Type_ArgInfoFunc(name, ...) EXT_CLASS_FUNC(Type_ArgInfo, name, __VA_ARGS__)

/**
 * API
 * * * * * * * * * */
EXT_CLASS_STRUCT_BEGIN(Type_ArgInfo)
    zend_arg_info *arg_info;
    HashTable properties;
EXT_CLASS_STRUCT_END(Type_ArgInfo);
EXT_CLASS_PHP_STRUCT_BEGIN(Type_ArgInfo)
EXT_CLASS_PHP_STRUCT_END(Type_ArgInfo);
EXT_CLASS_INIT_FUNCTION(Type_ArgInfo);
PHP_API Type_ArgInfoStruct *Type_ArgInfoCtor(zend_arg_info *arg_info);
PHP_API zend_object *Type_ArgInfoFunc(enclose, Type_ArgInfoStruct *type);
PHP_API void Type_ArgInfoFunc(free, Type_ArgInfoStruct *intern);
PHP_API HashTable *Type_ArgInfoFunc(properties, Type_ArgInfoStruct *intern);

/**
 * Class entry
 * * * * * * * * * */
extern EXT_CLASS_CLASS_ENTRY(Type_ArgInfo);
EXT_CLASS_CEINIT_FUNCTION(Type_ArgInfo);
PHP_API zend_object *Type_ArgInfoFunc(create_object, zend_class_entry *ce);

/**
 * Object handlers
 * * * * * * * * * */
EXT_CLASS_OBJECT_HANDLERS(Type_ArgInfo);
EXT_CLASS_OHINIT_FUNCTION(Type_ArgInfo);
PHP_API void Type_ArgInfoFunc(free_object, zend_object *object);
PHP_API HashTable *Type_ArgInfoFunc(get_debug_info, zval *object, int *is_temp);
PHP_API zval *Type_ArgInfoFunc(read_property, zval *object, zval *member, int type, void **cache_slot, zval *rv);

#endif /* LILT_TYPE_ARGINFO_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */