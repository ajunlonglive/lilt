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
  ["docComment"]=>
  string(40) "/**
 * Class AClass
 * @package \
 */"
  ["flags"]=>
  int(1572864)
  ["constants"]=>
  array(2) {
    ["CONST1"]=>
    object(Type\Constant)#%d (4) {
      ["docComment"]=>
      string(21) "/** AClass::CONST1 */"
      ["class"]=>
      *RECURSION*
      ["name"]=>
      string(6) "CONST1"
      ["value"]=>
      string(6) "const1"
    }
    ["CONST2"]=>
    object(Type\Constant)#%d (4) {
      ["docComment"]=>
      string(21) "/** AClass::CONST2 */"
      ["class"]=>
      *RECURSION*
      ["name"]=>
      string(6) "CONST2"
      ["value"]=>
      string(6) "const2"
    }
  }
  ["properties"]=>
  array(3) {
    ["publicProperty"]=>
    object(Type\Property)#%d (4) {
      ["docComment"]=>
      string(36) "/**
     * $publicProperty
     */"
      ["class"]=>
      *RECURSION*
      ["name"]=>
      string(14) "publicProperty"
      ["flags"]=>
      int(256)
    }
    ["privateProperty"]=>
    object(Type\Property)#%d (4) {
      ["docComment"]=>
      string(37) "/**
     * $privateProperty
     */"
      ["class"]=>
      *RECURSION*
      ["name"]=>
      string(15) "privateProperty"
      ["flags"]=>
      int(1024)
    }
    ["protectedProperty"]=>
    object(Type\Property)#%d (4) {
      ["docComment"]=>
      string(39) "/**
     * $protectedProperty
     */"
      ["class"]=>
      *RECURSION*
      ["name"]=>
      string(17) "protectedProperty"
      ["flags"]=>
      int(512)
    }
  }
  ["functions"]=>
  array(3) {
    ["publicMethod"]=>
    object(Type\Method)#%d (4) {
      ["argInfos"]=>
      array(3) {
        ["arg"]=>
        object(Type\ArgInfo)#%d (5) {
          ["byReference"]=>
          bool(false)
          ["name"]=>
          string(3) "arg"
          ["nullable"]=>
          bool(true)
          ["typeHint"]=>
          bool(false)
          ["variadic"]=>
          bool(false)
        }
        ["arg1"]=>
        object(Type\ArgInfo)#%d (5) {
          ["byReference"]=>
          bool(false)
          ["name"]=>
          string(4) "arg1"
          ["nullable"]=>
          bool(false)
          ["typeHint"]=>
          bool(true)
          ["variadic"]=>
          bool(false)
        }
        ["arg2"]=>
        object(Type\ArgInfo)#%d (5) {
          ["byReference"]=>
          bool(false)
          ["name"]=>
          string(4) "arg2"
          ["nullable"]=>
          bool(true)
          ["typeHint"]=>
          bool(true)
          ["variadic"]=>
          bool(false)
        }
      }
      ["class"]=>
      *RECURSION*
      ["name"]=>
      string(12) "publicMethod"
      ["flags"]=>
      int(402718976)
    }
    ["privateMethod"]=>
    object(Type\Method)#%d (4) {
      ["argInfos"]=>
      array(3) {
        ["arg"]=>
        object(Type\ArgInfo)#%d (5) {
          ["byReference"]=>
          bool(false)
          ["name"]=>
          string(3) "arg"
          ["nullable"]=>
          bool(true)
          ["typeHint"]=>
          bool(false)
          ["variadic"]=>
          bool(false)
        }
        ["arg1"]=>
        object(Type\ArgInfo)#%d (5) {
          ["byReference"]=>
          bool(false)
          ["name"]=>
          string(4) "arg1"
          ["nullable"]=>
          bool(false)
          ["typeHint"]=>
          bool(true)
          ["variadic"]=>
          bool(false)
        }
        ["arg2"]=>
        object(Type\ArgInfo)#%d (5) {
          ["byReference"]=>
          bool(false)
          ["name"]=>
          string(4) "arg2"
          ["nullable"]=>
          bool(true)
          ["typeHint"]=>
          bool(true)
          ["variadic"]=>
          bool(false)
        }
      }
      ["class"]=>
      *RECURSION*
      ["name"]=>
      string(13) "privateMethod"
      ["flags"]=>
      int(402718976)
    }
    ["protectedMethod"]=>
    object(Type\Method)#%d (4) {
      ["argInfos"]=>
      array(0) {
      }
      ["class"]=>
      *RECURSION*
      ["name"]=>
      string(15) "protectedMethod"
      ["flags"]=>
      int(1208025344)
    }
  }
}