--TEST--
mocking
--SKIPIF--
<?php include("skipif.inc") ?>
--FILE--
<?php
class Foo implements Typed {
    public $foo = 'foo';
    public static function quz() {
        return 'Foo::baz';
    }
}
class Bar extends Foo {
    public $foo = 'bar';
    public static function quz() {
        return 'Bar::baz';
    }
}
class Baz extends Bar {
    public $foo = 'baz';
    public static function quz() {
        return 'Baz::baz';
    }
}
(Bar::type)->mock();
var_dump(new Foo);
var_dump(Foo::quz());
var_dump(new Bar);
var_dump(Bar::quz());
(Baz::type)->mock();
var_dump(new Foo);
var_dump(Foo::quz());
var_dump(new Bar);
var_dump(Bar::quz());
(Bar::type)->unmock();
var_dump(new Foo);
var_dump(Foo::quz());
var_dump(new Bar);
var_dump(Bar::quz());
(Foo::type)->unmock();
var_dump(new Foo);
var_dump(Foo::quz());
var_dump(new Bar);
var_dump(Bar::quz());
?>
--EXPECTF--
object(Bar)#%d (1) {
  ["foo"]=>
  string(3) "bar"
}
string(8) "Bar::baz"
object(Bar)#%d (1) {
  ["foo"]=>
  string(3) "bar"
}
string(8) "Bar::baz"
object(Baz)#%d (1) {
  ["foo"]=>
  string(3) "bar"
}
string(8) "Baz::baz"
object(Baz)#%d (1) {
  ["foo"]=>
  string(3) "baz"
}
string(8) "Baz::baz"
object(Bar)#%d (1) {
  ["foo"]=>
  string(3) "bar"
}
string(8) "Bar::baz"
object(Bar)#%d (1) {
  ["foo"]=>
  string(3) "bar"
}
string(8) "Bar::baz"
object(Foo)#%d (1) {
  ["foo"]=>
  string(3) "foo"
}
string(8) "Foo::baz"
object(Bar)#%d (1) {
  ["foo"]=>
  string(3) "bar"
}
string(8) "Bar::baz"