--TEST--
\Type props
--SKIPIF--
<?php include("skipif.inc") ?>
--FILE--
<?php
class Foo implements \Typed { }
$type = Foo::type;
var_dump($type->name);
var_dump($type->isScalar);
var_dump($type->flags);
var_dump($type->constants);
var_dump($type->properties);
var_dump($type->functions);
?>
--EXPECT--
string(3) "Foo"
bool(false)
int(1572864)
array(0) {
}
array(0) {
}
array(0) {
}