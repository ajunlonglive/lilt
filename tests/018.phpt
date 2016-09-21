--TEST--
Operable
--SKIPIF--
<?php include("skipif.inc") ?>
--FILE--
<?php
class Foo implements \Operable {
    public function __operate(\Operator $operator, $value) {
        var_dump($operator->name);

        return $value;
    }
}
var_dump(new Foo + 1);
var_dump(new Foo - 2);
var_dump(new Foo * 3);
var_dump(new Foo / 4);
var_dump(new Foo % 5);
var_dump(new Foo << 6);
var_dump(new Foo >> 7);
var_dump(new Foo . 8);
var_dump(new Foo | 9);
var_dump(new Foo & 10);
var_dump(new Foo ^ 11);
?>
--EXPECT--
string(3) "ADD"
int(1)
string(3) "SUB"
int(2)
string(3) "MUL"
int(3)
string(3) "DIV"
int(4)
string(3) "MOD"
int(5)
string(2) "SL"
int(6)
string(2) "SR"
int(7)
string(6) "CONCAT"
string(1) "8"
string(5) "BW_OR"
int(9)
string(6) "BW_AND"
int(10)
string(6) "BW_XOR"
int(11)