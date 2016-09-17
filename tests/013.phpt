--TEST--
\Type::of ex
--SKIPIF--
<?php include("skipif.inc") ?>
--FILE--
<?php
$type = \Type::of();
?>
--EXPECTF--
Fatal error: Uncaught TypeError: Type::of() expects 1 parameter, 0 given in %s/tests/013.php:2
Stack trace:
#0 %s/tests/013.php(2): Type::of()
#1 {main}
  thrown in %s/tests/013.php on line 2