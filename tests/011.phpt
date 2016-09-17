--TEST--
type string
--SKIPIF--
<?php include("skipif.inc") ?>
--FILE--
<?php
$type = \typeof('foo');
var_dump($type instanceof \Type);
var_dump($type === \Type::of('foo'));
var_dump($type === \Type::string);
var_dump($type === TYPE_STRING);
var_dump($type->name);
var_dump($type->isScalar);
?>
--EXPECT--
bool(true)
bool(true)
bool(true)
bool(true)
string(6) "string"
bool(true)