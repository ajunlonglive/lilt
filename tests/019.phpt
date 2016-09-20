--TEST--
Operators 2
--SKIPIF--
<?php include("skipif.inc") ?>
--FILE--
<?php
class Long implements \Operable {
    private $value = 5;

    public function __operate(\Operator $operator, $value) {
        switch ($operator) {
            case \Operator::Add:
                return $this->value + $value;
            case \Operator::Sub:
                return $this->value - $value;
            case \Operator::Mul:
                return $this->value * $value;
            case \Operator::Div:
                return $this->value / $value;
            case \Operator::Identical:
                return $this->value === $value;
            case \Operator::NotIdentical:
                return $this->value !== $value;
            case \Operator::Equal:
                return $this->value == $value;
            case \Operator::NotEqual:
                return $this->value != $value;
            case \Operator::Cast:
                return $this->value;
        }
    }
}
$long = new Long;
var_dump($long + 1);
var_dump($long - 2);
var_dump($long * 3);
var_dump($long / 4);
var_dump($long === 5);
var_dump($long !== 5);
var_dump($long == 5);
var_dump($long != 5);
var_dump((int)$long);
?>
--EXPECT--
int(6)
int(3)
int(15)
float(1.25)
bool(true)
bool(false)
bool(true)
bool(false)
int(5)