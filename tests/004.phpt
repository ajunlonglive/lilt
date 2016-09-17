--TEST--
\Type props
--SKIPIF--
<?php include("skipif.inc") ?>
--FILE--
<?php
final class Foo implements \Typed { }
abstract class Bar implements \Typed { }
trait Baz { }
$type = Foo::type;
$type2 = Bar::type;
var_dump($type->name);
var_dump($type2->name);
var_dump($type->isScalar);
var_dump($type2->isScalar);
var_dump(classtype(\Type::class)->isInternal);
var_dump($type->flags);
var_dump($type->constants);
var_dump($type->properties);
var_dump($type->functions);
var_dump($type->isInternal);
var_dump($type2->isInternal);
var_dump($type->isFinal);
var_dump($type2->isFinal);
var_dump($type->isAbstract);
var_dump($type2->isAbstract);
var_dump(\classtype(Baz::class)->isTrait);
var_dump(\classtype(Baz::class)->isInterface);
var_dump(\classtype(\Typed::class)->isInterface);
var_dump(\classtype(\Typed::class)->isTrait);
?>
--EXPECT--
string(3) "Foo"
string(3) "Bar"
bool(false)
bool(false)
bool(true)
int(1572868)
array(0) {
}
array(0) {
}
array(0) {
}
bool(false)
bool(false)
bool(true)
bool(false)
bool(false)
bool(true)
bool(true)
bool(false)
bool(true)
bool(false)