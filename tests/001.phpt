--TEST--
Type
--SKIPIF--
<?php include("skipif.inc") ?>
--FILE--
<?php
/**
 * Class AClass
 * @package \
 */
class AClass implements Typed {

    /** AClass::CONST1 */
    const CONST1 = 'const1';
    /** AClass::CONST2 */
    const CONST2 = 'const2';
    /**
     * $publicProperty
     */
    public $publicProperty;
    /**
     * $privateProperty
     */
    private $privateProperty;
    /**
     * $protectedProperty
     */
    protected $protectedProperty;
    /**
     * @param            $arg
     * @param array      $arg1
     * @param array|null $arg2
     */
    public function publicMethod($arg, array $arg1, ?array $arg2) {}
    /**
     * @param             $arg
     * @param string      $arg1
     * @param null|string $arg2
     */
    public function privateMethod($arg, string $arg1, ?string $arg2) {}
    /**
     * @return string
     */
    public function protectedMethod() : string {}
}
var_dump(AClass::type);
?>
--EXPECTF--
object(Type)#%d (7) {
  ["name"]=>
  string(6) "AClass"
  ["scalar"]=>
  bool(false)
  ["flags"]=>
  int(1572864)
  ["docComment"]=>
  string(40) "/**
 * Class AClass
 * @package \
 */"
  ["constants"]=>
  array(2) {
    ["CONST1"]=>
    object(Type\Constant)#%d (4) {
      ["name"]=>
      string(6) "CONST1"
      ["docComment"]=>
      string(21) "/** AClass::CONST1 */"
      ["value"]=>
      string(6) "const1"
      ["class"]=>
      *RECURSION*
    }
    ["CONST2"]=>
    object(Type\Constant)#%d (4) {
      ["name"]=>
      string(6) "CONST2"
      ["docComment"]=>
      string(21) "/** AClass::CONST2 */"
      ["value"]=>
      string(6) "const2"
      ["class"]=>
      *RECURSION*
    }
  }
  ["properties"]=>
  array(3) {
    ["publicProperty"]=>
    object(Type\Property)#%d (4) {
      ["name"]=>
      string(14) "publicProperty"
      ["flags"]=>
      int(256)
      ["docComment"]=>
      string(36) "/**
     * $publicProperty
     */"
      ["class"]=>
      *RECURSION*
    }
    ["privateProperty"]=>
    object(Type\Property)#%d (4) {
      ["name"]=>
      string(15) "privateProperty"
      ["flags"]=>
      int(1024)
      ["docComment"]=>
      string(37) "/**
     * $privateProperty
     */"
      ["class"]=>
      *RECURSION*
    }
    ["protectedProperty"]=>
    object(Type\Property)#%d (4) {
      ["name"]=>
      string(17) "protectedProperty"
      ["flags"]=>
      int(512)
      ["docComment"]=>
      string(39) "/**
     * $protectedProperty
     */"
      ["class"]=>
      *RECURSION*
    }
  }
  ["functions"]=>
  array(3) {
    ["publicMethod"]=>
    object(Type\Method)#%d (5) {
      ["name"]=>
      string(12) "publicMethod"
      ["flags"]=>
      int(402718976)
      ["docComment"]=>
      string(107) "/**
     * @param            $arg
     * @param array      $arg1
     * @param array|null $arg2
     */"
      ["class"]=>
      *RECURSION*
      ["argInfos"]=>
      array(3) {
        ["arg"]=>
        object(Type\ArgInfo)#%d (5) {
          ["name"]=>
          string(3) "arg"
          ["byReference"]=>
          bool(false)
          ["nullable"]=>
          bool(true)
          ["typeHint"]=>
          bool(false)
          ["variadic"]=>
          bool(false)
        }
        ["arg1"]=>
        object(Type\ArgInfo)#%d (5) {
          ["name"]=>
          string(4) "arg1"
          ["byReference"]=>
          bool(false)
          ["nullable"]=>
          bool(false)
          ["typeHint"]=>
          bool(true)
          ["variadic"]=>
          bool(false)
        }
        ["arg2"]=>
        object(Type\ArgInfo)#%d (5) {
          ["name"]=>
          string(4) "arg2"
          ["byReference"]=>
          bool(false)
          ["nullable"]=>
          bool(true)
          ["typeHint"]=>
          bool(true)
          ["variadic"]=>
          bool(false)
        }
      }
    }
    ["privateMethod"]=>
    object(Type\Method)#%d (5) {
      ["name"]=>
      string(13) "privateMethod"
      ["flags"]=>
      int(402718976)
      ["docComment"]=>
      string(110) "/**
     * @param             $arg
     * @param string      $arg1
     * @param null|string $arg2
     */"
      ["class"]=>
      *RECURSION*
      ["argInfos"]=>
      array(3) {
        ["arg"]=>
        object(Type\ArgInfo)#%d (5) {
          ["name"]=>
          string(3) "arg"
          ["byReference"]=>
          bool(false)
          ["nullable"]=>
          bool(true)
          ["typeHint"]=>
          bool(false)
          ["variadic"]=>
          bool(false)
        }
        ["arg1"]=>
        object(Type\ArgInfo)#%d (5) {
          ["name"]=>
          string(4) "arg1"
          ["byReference"]=>
          bool(false)
          ["nullable"]=>
          bool(false)
          ["typeHint"]=>
          bool(true)
          ["variadic"]=>
          bool(false)
        }
        ["arg2"]=>
        object(Type\ArgInfo)#%d (5) {
          ["name"]=>
          string(4) "arg2"
          ["byReference"]=>
          bool(false)
          ["nullable"]=>
          bool(true)
          ["typeHint"]=>
          bool(true)
          ["variadic"]=>
          bool(false)
        }
      }
    }
    ["protectedMethod"]=>
    object(Type\Method)#%d (5) {
      ["name"]=>
      string(15) "protectedMethod"
      ["flags"]=>
      int(1208025344)
      ["docComment"]=>
      string(35) "/**
     * @return string
     */"
      ["class"]=>
      *RECURSION*
      ["argInfos"]=>
      array(0) {
      }
    }
  }
}