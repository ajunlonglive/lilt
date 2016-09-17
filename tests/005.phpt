--TEST--
type array
--SKIPIF--
<?php include("skipif.inc") ?>
--FILE--
<?php
$type = \typeof([]);
var_dump($type instanceof \Type);
var_dump($type === \Type::of([]));
var_dump($type === \Type::array);
var_dump($type === TYPE_ARRAY);
var_dump($type->name);
var_dump($type->isScalar);
?>
--EXPECT--
bool(true)
bool(true)
bool(true)
bool(true)
string(5) "array"
bool(true)