--TEST--
Type
--SKIPIF--
<?php include("skipif.inc") ?>
--FILE--
<?php
/**
 * Class Foo
 * @package \
 */
class Foo implements Typed {
    const CONST1 = 'const1';
    const CONST2 = 'const2';
    public $publicProperty;
    private $privateProperty;
    protected $protectedProperty;
    public function publicMethod($arg, array $arg1, ?array $arg2) {}
    public function privateMethod($arg, string $arg1, ?string $arg2) {}
    public function protectedMethod() : string {}
}
$type = Foo::type;
var_dump($type instanceof \Type);
var_dump(count($type->constants));
var_dump(count($type->properties));
var_dump(count($type->functions));
?>
--EXPECT--
bool(true)
int(2)
int(3)
int(3)