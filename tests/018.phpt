--TEST--
Enum ex
--SKIPIF--
<?php include("skipif.inc") ?>
--FILE--
<?php
class Long implements \Operable {
    public function __operate(\Operator $operator, $value) {
        var_dump($operator);
        var_dump($value);

        return $this;
    }
}
$long = new Long;
$long + 1;
$long - 2;
$long * 3;
$long / 4;
$long % 5;
$long << 6;
$long >> 7;
$long | 8;
$long & 9;
$long ^ 10;
$long === 11;
$long !== 12;
$long == 14;
$long != 15;
$long < 16;
$long <= 17;
?>
--EXPECTF--
object(Operator)#%d (2) {
  ["name"]=>
  string(3) "Add"
  ["value"]=>
  int(1)
}
int(1)
object(Operator)#%d (2) {
  ["name"]=>
  string(3) "Sub"
  ["value"]=>
  int(2)
}
int(2)
object(Operator)#%d (2) {
  ["name"]=>
  string(3) "Mul"
  ["value"]=>
  int(3)
}
int(3)
object(Operator)#%d (2) {
  ["name"]=>
  string(3) "Div"
  ["value"]=>
  int(4)
}
int(4)
object(Operator)#%d (2) {
  ["name"]=>
  string(3) "Mod"
  ["value"]=>
  int(5)
}
int(5)
object(Operator)#%d (2) {
  ["name"]=>
  string(2) "Sl"
  ["value"]=>
  int(6)
}
int(6)
object(Operator)#%d (2) {
  ["name"]=>
  string(2) "Sr"
  ["value"]=>
  int(7)
}
int(7)
object(Operator)#%d (2) {
  ["name"]=>
  string(4) "BwOr"
  ["value"]=>
  int(9)
}
int(8)
object(Operator)#%d (2) {
  ["name"]=>
  string(5) "BwAnd"
  ["value"]=>
  int(10)
}
int(9)
object(Operator)#%d (2) {
  ["name"]=>
  string(5) "BwXor"
  ["value"]=>
  int(11)
}
int(10)
object(Operator)#%d (2) {
  ["name"]=>
  string(9) "Identical"
  ["value"]=>
  int(15)
}
int(11)
object(Operator)#%d (2) {
  ["name"]=>
  string(12) "NotIdentical"
  ["value"]=>
  int(16)
}
int(12)
object(Operator)#%d (2) {
  ["name"]=>
  string(5) "Equal"
  ["value"]=>
  int(17)
}
int(14)
object(Operator)#%d (2) {
  ["name"]=>
  string(8) "NotEqual"
  ["value"]=>
  int(18)
}
int(15)
object(Operator)#%d (2) {
  ["name"]=>
  string(7) "Smaller"
  ["value"]=>
  int(19)
}
int(16)
object(Operator)#%d (2) {
  ["name"]=>
  string(14) "SmallerOrEqual"
  ["value"]=>
  int(20)
}
int(17)