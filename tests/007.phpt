--TEST--
type double
--SKIPIF--
<?php include("skipif.inc") ?>
--FILE--
<?php
$type = \typeof(0.1);
var_dump($type instanceof \Type);
var_dump($type === \Type::of(0.1));
var_dump($type === \Type::double);
var_dump($type === TYPE_DOUBLE);
var_dump($type->name);
var_dump($type->isScalar);
?>
--EXPECT--
bool(true)
bool(true)
bool(true)
bool(true)
string(6) "double"
bool(true)