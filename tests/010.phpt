--TEST--
type resource
--SKIPIF--
<?php include("skipif.inc") ?>
--FILE--
<?php
$resource = fopen(__FILE__, 'r');
$type = \typeof($resource);
var_dump($type instanceof \Type);
var_dump($type === \Type::of($resource));
var_dump($type === \Type::resource);
var_dump($type === TYPE_RESOURCE);
var_dump($type->name);
var_dump($type->scalar);
fclose($resource);
?>
--EXPECT--
bool(true)
bool(true)
bool(true)
bool(true)
string(8) "resource"
bool(true)