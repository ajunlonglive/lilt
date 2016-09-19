--TEST--
Enum
--SKIPIF--
<?php include("skipif.inc") ?>
--FILE--
<?php
class Status implements \Enum {

    /**
     * @var Status
     */
    const Pending = -1;
    /**
     * @var Status
     */
    const Running = 1;
    /**
     * @var Status
     */
    const Failed = 0;
}
var_dump(Status::Pending);
var_dump(Status::Running);
var_dump(Status::Failed);
$status = Status::Pending;
$status->value = "oops";
?>
--EXPECTF--
object(Status)#%d (1) {
  ["value"]=>
  int(-1)
}
object(Status)#%d (1) {
  ["value"]=>
  int(1)
}
object(Status)#%d (1) {
  ["value"]=>
  int(0)
}

Fatal error: Cannot set immutable const Status::$value. in %s/tests/016.php on line %d