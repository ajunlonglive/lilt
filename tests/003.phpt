--TEST--
typeof && classtype 2
--SKIPIF--
<?php include("skipif.inc") ?>
--FILE--
<?php
class Foo implements \Typed { }
var_dump(\typeof(new Foo) instanceof \Type);
var_dump(\typeof(new Foo) === \classtype(Foo::class));
var_dump(\typeof(new Foo) === Foo::type);
var_dump(\classtype(Foo::class) === Foo::type);
?>
--EXPECT--
bool(true)
bool(true)
bool(true)
bool(true)