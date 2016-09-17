--TEST--
typeof && classtype
--SKIPIF--
<?php include("skipif.inc") ?>
--FILE--
<?php
class Foo { }
var_dump(\typeof(new Foo) === \classtype(Foo::class));
var_dump(Foo::type);
?>
--EXPECTF--
bool(true)

Fatal error: Uncaught Error: Undefined class constant 'type' in %s/tests/002.php:4
Stack trace:
#0 {main}
  thrown in %s/tests/002.php on line 4