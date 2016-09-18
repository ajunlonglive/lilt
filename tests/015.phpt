--TEST--
IStaticInit
--SKIPIF--
<?php include("skipif.inc") ?>
--FILE--
<?php
class Foo implements \IStaticInit {
    public static function __static() : void {
        var_dump('Hello');
    }
}
class Bar extends Foo {
    public static function __static() : void {
        var_dump('World');
    }
}
class Baz extends Bar { }
?>
--EXPECT--
string(5) "Hello"
string(5) "World"