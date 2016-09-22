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

EXT_HANDLER_FUNCTION(0) {
    php_printf("opcode: %d\n", EX(opline)->opcode);
    return ZEND_USER_OPCODE_DISPATCH;
}

EXT_RINIT_FUNCTION { /* {{{ EXT_RINIT_FUNCTION */
#if defined(COMPILE_DL_EXT) && defined(ZTS)
    ZEND_TSRMLS_CACHE_UPDATE();
#endif
    zend_hash_init(&LILTG(data.types), 8, NULL, zval_p_dtor, 0);
    zend_hash_init(&LILTG(data.mocks), 3, NULL, zval_p_dtor, 0);
    LILTG(zstr.type) = z_string("type");
    EXT_CLASS_INIT(Type_ArgInfo);
    EXT_CLASS_INIT(Type_Constant);
    EXT_CLASS_INIT(Type_Function);
    EXT_CLASS_INIT(Type_Property);
    EXT_CLASS_INIT(Type);
    EXT_CLASS_INIT(Typed);
    EXT_CLASS_INIT(IStaticInit);
    EXT_CLASS_INIT(Enum);
    EXT_HINIT();
    return SUCCESS;
} /* }}} */

EXT_RSHUTDOWN_FUNCTION { /* {{{ EXT_RSHUTDOWN_FUNCTION */
    zend_hash_destroy(&LILTG(data.types));
    zend_hash_destroy(&LILTG(data.mocks));
    zend_string_release(LILTG(zstr.type));
    if (zend_hash_num_elements(&TypeCe->constants_table)) {
        zend_class_constant *c;
        zend_string *k;
        ZEND_HASH_FOREACH_STR_KEY_PTR(&TypeCe->constants_table, k, c)
            zval_ptr_dtor(&c->value);
            if (c->doc_comment && c->ce == TypeCe) {
                zend_string_release(c->doc_comment);
            }
            zend_hash_del(&TypeCe->constants_table, k);
        ZEND_HASH_FOREACH_END();
        zend_hash_destroy(&TypeCe->constants_table);
    }
    zend_hash_del(EG(zend_constants), z_string("TYPE_ARRAY"));
    zend_hash_del(EG(zend_constants), z_string("TYPE_BOOLEAN"));
    zend_hash_del(EG(zend_constants), z_string("TYPE_DOUBLE"));
    zend_hash_del(EG(zend_constants), z_string("TYPE_INTEGER"));
    zend_hash_del(EG(zend_constants), z_string("TYPE_NULL"));
    zend_hash_del(EG(zend_constants), z_string("TYPE_RESOURCE"));
    zend_hash_del(EG(zend_constants), z_string("TYPE_STRING"));
    zend_hash_del(EG(zend_constants), z_string("TYPE_UNKNOWN"));
    zend_string_release(TypeMem(fn_mock).common.function_name);
    zend_string_release(TypeMem(fn_unmock).common.function_name);
    EXT_HSHUTDOWN();
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