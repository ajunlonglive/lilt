--TEST--
Enum ex
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
$status = new Status();
?>
--EXPECTF--
Fatal error: Cannot instantiate enum Status::class. in %s/tests/017.php on line %d