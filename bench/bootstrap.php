<?php declare(strict_types=1);
require __DIR__.'/../vendor/autoload.php';

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

include __DIR__.'/001.php';
include __DIR__.'/002.php';
include __DIR__.'/003.php';