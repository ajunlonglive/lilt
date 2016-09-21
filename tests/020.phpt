--TEST--
Comparable
--SKIPIF--
<?php include("skipif.inc") ?>
--FILE--
<?php
class Foo implements \Comparable {
    public function __compare(\Operator $operator, $value) {
        var_dump($operator->name);
        var_dump($value);

        return 1;
    }
}
new Foo === 1;
new Foo !== 2;
new Foo == 3;
new Foo != 4;
new Foo < 5;
new Foo <= 6;
new Foo > 7;
new Foo >= 8;
?>
--EXPECT--
string(9) "IDENTICAL"
int(1)
string(13) "NOT_IDENTICAL"
int(2)
string(5) "EQUAL"
int(3)
string(9) "NOT_EQUAL"
int(4)
string(7) "SMALLER"
int(5)
string(16) "SMALLER_OR_EQUAL"
int(6)
string(7) "GREATER"
int(7)
string(16) "GREATER_OR_EQUAL"
int(8)