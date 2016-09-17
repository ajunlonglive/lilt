--TEST--
type boolean
--SKIPIF--
<?php include("skipif.inc") ?>
--FILE--
<?php
foreach([true, false] as $bool) {
    $type = \typeof($bool);
    var_dump($type instanceof \Type);
    var_dump($type === \Type::of($bool));
    var_dump($type === \Type::boolean);
    var_dump($type === TYPE_BOOLEAN);
    var_dump($type->name);
    var_dump($type->scalar);
}
?>
--EXPECT--
bool(true)
bool(true)
bool(true)
bool(true)
string(7) "boolean"
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
string(7) "boolean"
bool(true)