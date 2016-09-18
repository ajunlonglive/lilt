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

#include "classes/type.h"

#define CUSTOM_STRUCT
#define CLASS Type
#include "gen/class.h"

#define INIT_TYPE_SCALAR(scalar, constname) { \
      zval zv; \
      zend_constant c; \
      LILTG(type_##scalar) = MEM(enclose(CTOR(z_string(STRINGIZE(scalar)), NULL))); \
      ZVAL_OBJ(&zv, LILTG(type_##scalar)); \
      zend_declare_class_constant(CE, STRINGIZE(scalar), sizeof(STRINGIZE(scalar))-1, &zv); \
      ZVAL_OBJ(&c.value, LILTG(type_##scalar)); \
      Z_TRY_ADDREF(c.value); \
      c.flags = ZEND_ACC_PUBLIC; \
      c.name = zend_string_init(STR_AND_LEN(constname), ZEND_ACC_PUBLIC & CONST_PERSISTENT); \
      c.module_number = 0; \
      zend_register_constant(&c); \
  }

ZEND_BEGIN_ARG_INFO_EX(Type_of, 0, 0, 0)
ZEND_END_ARG_INFO()

//ZEND_BEGIN_ARG_INFO_EX(Type_mock, 0, 0, 0)
//ZEND_END_ARG_INFO()
//
//ZEND_BEGIN_ARG_INFO_EX(Type_unmock, 0, 0, 0)
//ZEND_END_ARG_INFO()

CLASS_ENTRY;
const METHODS_BEGIN
    ME(of, Type_of, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
//    ME(mock, Type_mock, ZEND_ACC_PUBLIC)
//    ME(unmock, Type_unmock, ZEND_ACC_PUBLIC)
METHODS_END;

CEINIT_FUNCTION {
    INIT_CLASS;
    CE->ce_flags |= ZEND_ACC_FINAL;
    CE->create_object = MEM(create_object);
    INIT_TYPE_SCALAR(array, "TYPE_ARRAY");
    INIT_TYPE_SCALAR(boolean, "TYPE_BOOLEAN");
    INIT_TYPE_SCALAR(double, "TYPE_DOUBLE");
    INIT_TYPE_SCALAR(integer, "TYPE_INTEGER");
    INIT_TYPE_SCALAR(null, "TYPE_NULL");
    INIT_TYPE_SCALAR(resource, "TYPE_RESOURCE");
    INIT_TYPE_SCALAR(string, "TYPE_STRING");
    INIT_TYPE_SCALAR(unknown, "TYPE_UNKNOWN");
//    TypeMem(fn_mock).common.scope = CE;
//    TypeMem(fn_mock).type = ZEND_OVERLOADED_FUNCTION;
//    TypeMem(fn_mock).common.function_name = z_string("mock");
//    TypeMem(fn_unmock).common.scope = CE;
//    TypeMem(fn_unmock).type = ZEND_OVERLOADED_FUNCTION;
//    TypeMem(fn_unmock).common.function_name = z_string("unmock");
}

PHP_API zend_object *FUNC(create_object, zend_class_entry *ce) {
    zend_error(E_ERROR,"Cannot instantiate %s::class in userland.", CLASS_STR);
    return NULL;
}

PHP_API METHOD(of) {
    int num_args = ZEND_CALL_NUM_ARGS(execute_data);
    if (num_args == 1) {
        FUNC(zval_of, ZEND_CALL_ARG(execute_data, 1), return_value);
    } else {
        zend_internal_type_error(1, "Type::of() expects 1 parameter, %d given", num_args);
    }
}

//PHP_API METHOD(mock) {
//    INIT_THIS;
//    zval parent_type;
//    int num_args = ZEND_CALL_NUM_ARGS(execute_data);
//    if (num_args == 0) {
//        if (this->ce) {
//            if (this->ce->parent) {
//                if (!this->ce->parent->create_object && !this->ce->parent->get_static_method) {
//                    FUNC(zval_of_ce, this->ce->parent, &parent_type);
//                    Z_THIS(parent_type)->mock = Z_OBJ(EX(This));
//                    if (zend_hash_update(&LILTG(data.mocks), this->ce->parent->name, &EX(This))) {
//                        zval_copy_ctor(&EX(This));
//                    }
//                    this->ce->parent->create_object = MEM(create_mock);
//                    this->ce->parent->get_static_method = MEM(get_static_method_mock);
//                    this->is_mocking = 1;
//                    RETURN_TRUE;
//                } else {
//                    RETURN_FALSE;
//                }
//            } else {
//                zend_internal_type_error(1, "Their is not extend to mock for type %s.", ZSTR_VAL(this->type_name));
//            }
//        } else {
//            zend_internal_type_error(1, "Cannot mock scalar type %s.", ZSTR_VAL(this->type_name));
//        }
//    } else {
//        zend_internal_type_error(1, "Type::mock() expects 0 parameter, %d given.", num_args);
//    }
//}
//
//PHP_API METHOD(unmock) {
//    INIT_THIS;
//    int num_args = ZEND_CALL_NUM_ARGS(execute_data);
//    if (num_args == 0) {
//        if (this->ce) {
//            int unmock = 0;
//            if (this->is_mocking) {
//                this->is_mocking = 0;
//                this->ce->parent->create_object = NULL;
//                this->ce->parent->get_static_method = NULL;
//                unmock = 1;
//            }
//            if (this->mock) {
//                this->mock = NULL;
//                this->ce->create_object = NULL;
//                this->ce->get_static_method = NULL;
//                unmock = 1;
//            }
//            ZVAL_BOOL(return_value, unmock);
//        } else {
//            zend_internal_type_error(1, "Cannot mock scalar type %s.", ZSTR_VAL(this->type_name));
//        }
//    } else {
//        zend_internal_type_error(1, "Type::mock() expects 0 parameter, %d given.", num_args);
//    }
//}

#undef CUSTOM_STRUCT
#undef CLASS

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */