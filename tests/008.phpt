--TEST--
type integer
--SKIPIF--
<?php include("skipif.inc") ?>
--FILE--
<?php
$type = \typeof(1);
var_dump($type instanceof \Type);
var_dump($type === \Type::of(1));
var_dump($type === \Type::integer);
var_dump($type === TYPE_INTEGER);
var_dump($type->name);
var_dump($type->isScalar);
?>
--EXPECT--
bool(true)
bool(true)
bool(true)
bool(true)
string(7) "integer"
bool(true)