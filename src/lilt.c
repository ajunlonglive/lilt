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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "lilt.h"
#include "utils.h"

zend_lilt_globals EXT_MG;

EXT_MGINIT_FUNCTION { /* {{{ EXT_MGINIT_FUNCTION */
    EXT_MEMSET_GLOBALS;
} /* }}} */

EXT_MINIT_FUNCTION { /* {{{ EXT_MINIT_FUNCTION */
    EXT_MGINIT(&EXT_MG);

    return SUCCESS;
} /* }}} */

EXT_MSHUTDOWN_FUNCTION { /* {{{ EXT_MSHUTDOWN_FUNCTION */
    return SUCCESS;
} /* }}} */

EXT_HANDLER_FUNCTION(0) {
    php_printf("opcode: %d\n", EX(opline)->opcode);

    return ZEND_USER_OPCODE_DISPATCH;
}

EXT_RINIT_FUNCTION { /* {{{ EXT_RINIT_FUNCTION */
#if defined(COMPILE_DL_EXT) && defined(ZTS)
    ZEND_TSRMLS_CACHE_UPDATE();
#endif
    zend_hash_init(&LILTG(data.types), 8, NULL, zval_p_dtor, 0);
    LILTG(zstr.type) = z_string("type");

    for (int i = 0; i < 256; i++) {
        if (i != ZEND_FETCH_CLASS_CONSTANT) {
            //zend_set_user_opcode_handler((zend_uchar) i, EXT_HANDLER(0));
        }
    }

    EXT_CLASS_INIT(Type_ArgInfo);
    EXT_CLASS_INIT(Type_Constant);
    EXT_CLASS_INIT(Type_Function);
    EXT_CLASS_INIT(Type_Property);
    EXT_CLASS_INIT(Type);
    EXT_CLASS_INIT(Typed);

    EXT_HINIT();

    return SUCCESS;
} /* }}} */

EXT_RSHUTDOWN_FUNCTION { /* {{{ EXT_RSHUTDOWN_FUNCTION */
    zend_hash_destroy(&LILTG(data.types));

    for (int i = 0; i < 256; i++) {
        if (i != ZEND_FETCH_CLASS_CONSTANT) {
            //zend_set_user_opcode_handler((zend_uchar) i, NULL);
        }
    }

    zend_objects_destroy_object(LILTG(type_array));
    zend_objects_destroy_object(LILTG(type_boolean));
    zend_objects_destroy_object(LILTG(type_double));
    zend_objects_destroy_object(LILTG(type_integer));
    zend_objects_destroy_object(LILTG(type_null));
    zend_objects_destroy_object(LILTG(type_resource));
    zend_objects_destroy_object(LILTG(type_string));
    zend_objects_destroy_object(LILTG(type_unknown));

    EXT_HFREE();

    return SUCCESS;
} /* }}} */

EXT_GINIT_FUNCTION { /* {{{ EXT_RSHUTDOWN_FUNCTION */
}; /* }}} */

EXT_MINFO_FUNCTION { /* {{{ EXT_MINFO_FUNCTION */
    EXT_MINFO_BODY;
} /* }}} */

EXT_DEPS_TABLE = { /* {{{ EXT_DEPS_TABLE */
    ZEND_MOD_REQUIRED("reflection")
    ZEND_MOD_REQUIRED("spl")
    ZEND_MOD_END
} /* }}} */;

EXT_FUNCTIONS_TABLE = { /* {{{ EXT_FUNCTIONS_TABLE */
    PHP_FE(typeof, NULL)
    PHP_FE(classtype, NULL)
    PHP_FE_END
} /* }}} */;

EXT_MODULE_ENTRY = { /* {{{ EXT_MODULE_ENTRY */
    EXT_MODULE_PROPERTIES
} /* }}} */;


#if COMPILE_DL_LILT
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE();
#endif
ZEND_GET_MODULE(lilt)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */