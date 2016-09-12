<?php declare(strict_types = 1);
/**
 * Class AClass
 * @package \
 */
class AClass implements Typed {

    /** AClass::CONST1 */
    const CONST1 = 'const1';
    /** AClass::CONST2 */
    const CONST2 = 'const2';

    /**
     * $publicProperty
     */
    public $publicProperty;
    /**
     * $privateProperty
     */
    private $privateProperty;
    /**
     * $protectedProperty
     */
    protected $protectedProperty;

    /**
     * @param            $arg
     * @param array      $arg1
     * @param array|null $arg2
     */
    public function publicMethod($arg, array $arg1, ?array $arg2) {}

    /**
     * @param             $arg
     * @param string      $arg1
     * @param null|string $arg2
     */
    public function privateMethod($arg, string $arg1, ?string $arg2) {}

    /**
     * @return string
     */
    public function protectedMethod() : string {}
}