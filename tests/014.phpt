--TEST--
\Type::of ex
--SKIPIF--
<?php include("skipif.inc") ?>
--FILE--
<?php
class Foo implements Typed {
    public $foo = 'foo';
    public static function baz() {
        return 'Foo::baz';
    }
}
class Bar extends Foo {
    public $foo = 'bar';
    public static function baz() {
        return 'Bar::baz';
    }
}
var_dump((Bar::type)->mock());
var_dump(new Foo);
var_dump(Foo::baz());
var_dump((Bar::type)->unmock());
var_dump(new Foo);
var_dump(Foo::baz());
var_dump((Bar::type)->mock());
var_dump(new Foo);
var_dump(Foo::baz());
var_dump((Foo::type)->unmock());
var_dump(new Foo);
var_dump(Foo::baz());
?>
--EXPECTF--
bool(true)
object(Bar)#%d (1) {
  ["foo"]=>
  string(3) "bar"
}
string(8) "Bar::baz"
bool(true)
object(Foo)#%d (1) {
  ["foo"]=>
  string(3) "foo"
}
string(8) "Foo::baz"
bool(true)
object(Bar)#%d (1) {
  ["foo"]=>
  string(3) "bar"
}
string(8) "Bar::baz"
bool(true)
object(Foo)#%d (1) {
  ["foo"]=>
  string(3) "foo"
}
string(8) "Foo::baz"