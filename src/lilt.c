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

EXT_DECLARE_MODULE_GLOBALS;

EXT_MGINIT_FUNCTION { /* {{{ EXT_MGINIT_FUNCTION */
    EXT_MEMSET_GLOBALS;
} /* }}} */

EXT_MINIT_FUNCTION { /* {{{ EXT_MINIT_FUNCTION */
    ZEND_INIT_MODULE_GLOBALS(lilt, EXT_MGINIT, NULL);

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
    zend_string_release(LILTG(zstr.type));

    LILTG(type_array)->handlers->free_obj(LILTG(type_array));
    efree(LILTG(type_array));
    LILTG(type_boolean)->handlers->free_obj(LILTG(type_boolean));
    efree(LILTG(type_boolean));
    LILTG(type_double)->handlers->free_obj(LILTG(type_double));
    efree(LILTG(type_double));
    LILTG(type_integer)->handlers->free_obj(LILTG(type_integer));
    efree(LILTG(type_integer));
    LILTG(type_null)->handlers->free_obj(LILTG(type_null));
    efree(LILTG(type_null));
    LILTG(type_resource)->handlers->free_obj(LILTG(type_resource));
    efree(LILTG(type_resource));
    LILTG(type_string)->handlers->free_obj(LILTG(type_string));
    efree(LILTG(type_string));
    LILTG(type_unknown)->handlers->free_obj(LILTG(type_unknown));
    efree(LILTG(type_unknown));

    EXT_HFREE();

    return SUCCESS;
} /* }}} */

EXT_GINIT_FUNCTION { /* {{{ EXT_RSHUTDOWN_FUNCTION */
}; /* }}} */

EXT_MINFO_FUNCTION { /* {{{ EXT_MINFO_FUNCTION */
    EXT_MINFO_BODY;
} /* }}} */

EXT_DEPS_TABLE = { /* {{{ EXT_DEPS_TABLE */
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