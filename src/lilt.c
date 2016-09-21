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

EXT_RINIT_FUNCTION { /* {{{ EXT_RINIT_FUNCTION */
#if defined(COMPILE_DL_EXT) && defined(ZTS)
    ZEND_TSRMLS_CACHE_UPDATE();
#endif
    LILTG(zstr.type) = z_string("type");
    zend_hash_init(&LILTG(data.types), 8, NULL, zval_p_dtor, 0);
    zend_hash_init(&LILTG(data.mocks), 3, NULL, zval_p_dtor, 0);

    EXT_CLASS_INIT(Type_ArgInfo);
    EXT_CLASS_INIT(Type_Constant);
    EXT_CLASS_INIT(Type_Function);
    EXT_CLASS_INIT(Type_Property);
    EXT_CLASS_INIT(Type);
    EXT_CLASS_INIT(Typed);
    EXT_CLASS_INIT(IStaticInit);
    EXT_CLASS_INIT(Enum);
    EXT_CLASS_INIT(Operator);
    EXT_CLASS_INIT(Operable);
    EXT_CLASS_INIT(Castable);
    EXT_CLASS_INIT(Comparable);

    EXT_HINIT();

    return SUCCESS;
} /* }}} */

EXT_RSHUTDOWN_FUNCTION { /* {{{ EXT_RSHUTDOWN_FUNCTION */
    EXT_CLASS_SHUTDOWN(Comparable);
    EXT_CLASS_SHUTDOWN(Castable);
    EXT_CLASS_SHUTDOWN(Operable);
    EXT_CLASS_SHUTDOWN(Operator);
    EXT_CLASS_SHUTDOWN(Enum);
    EXT_CLASS_SHUTDOWN(Typed);
    EXT_CLASS_SHUTDOWN(Type);
    EXT_CLASS_SHUTDOWN(IStaticInit);
    EXT_CLASS_SHUTDOWN(Type_Property);
    EXT_CLASS_SHUTDOWN(Type_Function);
    EXT_CLASS_SHUTDOWN(Type_Constant);
    EXT_CLASS_SHUTDOWN(Type_ArgInfo);

    zend_hash_destroy(&LILTG(data.types));
    zend_hash_destroy(&LILTG(data.mocks));
    zend_string_release(LILTG(zstr.type));

    EXT_HSHUTDOWN();

    return SUCCESS;
} /* }}} */

EXT_GINIT_FUNCTION { /* {{{ EXT_GINIT_FUNCTION */ }; /* }}} */

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