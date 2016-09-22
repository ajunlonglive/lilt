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

#include "classes/enum.h"

#define CLASS Enum
#include "gen/class.h"

CLASS_ENTRY;
NO_METHODS;

INIT_FUNCTION {
    INIT_INTERFACE;
    INIT_HANDLERS;
    OH.write_property = MEM(write_property);
    CE->interface_gets_implemented = MEM(interface_gets_implemented);
}

SHUTDOWN_FUNCTION { }

zend_object *FUNC(create_object, zend_class_entry *ce) {
    zend_error(E_ERROR, "Cannot instantiate enum %s::class.", ZSTR_VAL(ce->name));

    return NULL;
}

int FUNC(interface_gets_implemented, zend_class_entry *iface, zend_class_entry *ce) {
    zend_object *object;
    zend_class_constant *constant;
    zend_string *key;
    zend_class_entry *parent = ce->parent;

    if (ce->create_object != NULL) {
        zend_error(E_ERROR, "%s interface can only be used on userland classes.", CLASS_STR);
    }

    ce->create_object = MEM(create_object);
    ZEND_HASH_FOREACH_STR_KEY_PTR(&ce->constants_table, key, constant)
        if (Z_TYPE(constant->value) != IS_OBJECT) {
            zval tmp;

            ZVAL_COPY(&tmp, &constant->value);
            object = zend_objects_new(ce);

            ZVAL_OBJ(&constant->value, object);
            zend_update_property_str(ce, &constant->value, STR_AND_LEN("name"), zend_string_copy(key));
            zend_update_property(ce, &constant->value, STR_AND_LEN("value"), &tmp);
            object->handlers = &OH;
        }
    ZEND_HASH_FOREACH_END();
    while(parent) {
        ZEND_HASH_FOREACH_STR_KEY_PTR(&parent->constants_table, key, constant)
            if (Z_TYPE(constant->value) == IS_OBJECT && instanceof_function(Z_OBJ(constant->value)->ce, EnumCe)) {
                zval *value, tmp, cst;

                value = zend_read_property(Z_OBJ(constant->value)->ce, &constant->value, STR_AND_LEN("value"), 0, &tmp);
                object = zend_objects_new(ce);

                ZVAL_OBJ(&cst, object);
                zend_update_property_str(ce, &cst, STR_AND_LEN("name"), zend_string_copy(key));
                zend_update_property(ce, &cst, STR_AND_LEN("value"), value);
                object->handlers = &OH;

                zend_hash_del(&ce->constants_table, key);
                zend_declare_class_constant(ce, ZSTR_VAL(key), ZSTR_LEN(key), &cst);
            }
        ZEND_HASH_FOREACH_END();
        parent = parent->parent;
    }

    return SUCCESS;
}

void FUNC(write_property, zval *object, zval *member, zval *value, void **cache_slot) {
    zend_error(E_ERROR, "Cannot set property of enum object %s::$%s.",
        ZSTR_VAL(Z_OBJ_P(object)->ce->name),
        Z_STRVAL_P(member)
    );
}

#undef CLASS

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */