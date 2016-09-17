--TEST--
\typeof ex
--SKIPIF--
<?php include("skipif.inc") ?>
--FILE--
<?php
$type = \typeof();
?>
--EXPECTF--
Fatal error: Uncaught TypeError: typeof() expects 1 parameter, 0 given in %s/lilt/tests/012.php:2
Stack trace:
#0 %s/tests/012.php(2): typeof()
#1 {main}
  thrown in %s/tests/012.php on line 2