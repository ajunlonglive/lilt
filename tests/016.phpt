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
class BuildStatus extends Status {
    /**
     * @var BuildStatus
     */
    const Error = -2;
}
class TravisBuildStatus extends BuildStatus {
    /**
     * @var TravisBuildStatus
     */
    const Passing = 2;
}
var_dump(Status::Pending);
var_dump(Status::Running);
var_dump(Status::Failed);
var_dump(BuildStatus::Pending);
var_dump(BuildStatus::Running);
var_dump(BuildStatus::Failed);
var_dump(BuildStatus::Error);
var_dump(TravisBuildStatus::Pending);
var_dump(TravisBuildStatus::Running);
var_dump(TravisBuildStatus::Failed);
var_dump(TravisBuildStatus::Error);
var_dump(TravisBuildStatus::Passing);
$status = Status::Pending;
$status->value = "oops";
?>
--EXPECTF--
object(Status)#%d (2) {
  ["name"]=>
  string(7) "Pending"
  ["value"]=>
  int(-1)
}
object(Status)#%d (2) {
  ["name"]=>
  string(7) "Running"
  ["value"]=>
  int(1)
}
object(Status)#%d (2) {
  ["name"]=>
  string(6) "Failed"
  ["value"]=>
  int(0)
}
object(BuildStatus)#%d (2) {
  ["name"]=>
  string(7) "Pending"
  ["value"]=>
  int(-1)
}
object(BuildStatus)#%d (2) {
  ["name"]=>
  string(7) "Running"
  ["value"]=>
  int(1)
}
object(BuildStatus)#%d (2) {
  ["name"]=>
  string(6) "Failed"
  ["value"]=>
  int(0)
}
object(BuildStatus)#%d (2) {
  ["name"]=>
  string(5) "Error"
  ["value"]=>
  int(-2)
}
object(TravisBuildStatus)#%d (2) {
  ["name"]=>
  string(7) "Pending"
  ["value"]=>
  int(-1)
}
object(TravisBuildStatus)#%d (2) {
  ["name"]=>
  string(7) "Running"
  ["value"]=>
  int(1)
}
object(TravisBuildStatus)#%d (2) {
  ["name"]=>
  string(6) "Failed"
  ["value"]=>
  int(0)
}
object(TravisBuildStatus)#%d (2) {
  ["name"]=>
  string(5) "Error"
  ["value"]=>
  int(-2)
}
object(TravisBuildStatus)#%d (2) {
  ["name"]=>
  string(7) "Passing"
  ["value"]=>
  int(2)
}

Fatal error: Cannot set property of enum object Status::$value. in %s/tests/016.php on line %d