--TEST--
type null
--SKIPIF--
<?php include("skipif.inc") ?>
--FILE--
<?php
$type = \typeof(null);
var_dump($type instanceof \Type);
var_dump($type === \Type::of(null));
var_dump($type === \Type::null);
var_dump($type === TYPE_NULL);
var_dump($type->name);
var_dump($type->isScalar);
?>
--EXPECT--
bool(true)
bool(true)
bool(true)
bool(true)
string(4) "null"
bool(true)