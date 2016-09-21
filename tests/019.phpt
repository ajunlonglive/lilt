--TEST--
Castable
--SKIPIF--
<?php include("skipif.inc") ?>
--FILE--
<?php
class Foo implements \Castable {
    public function __cast(\Type $type) {
        switch($type) {
            case \Type::array:
                return [9.9];
            case \Type::boolean:
                return true;
            case \Type::double:
                return 9.9;
            case \Type::integer:
                return 9;
            case \Type::string:
                return "9";
        }
    }
}
var_dump((array)new Foo);
var_dump((bool)new Foo);
var_dump((double)new Foo);
var_dump((int)new Foo);
var_dump((string)new Foo);
?>
--EXPECT--
array(1) {
  [0]=>
  float(9.9)
}
bool(true)
float(9.9)
int(9)
string(1) "9"