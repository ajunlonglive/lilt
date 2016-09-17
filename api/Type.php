<?php declare(strict_types=1);
/**
 * Class Type
 * @package \
 */
final class Type implements \Typed {

    /**
     * @var \Type
     */
    const array = null;
    /**
     * @var \Type
     */
    const boolean = null;
    /**
     * @var \Type
     */
    const double = null;
    /**
     * @var \Type
     */
    const integer = null;
    /**
     * @var \Type
     */
    const null = null;
    /**
     * @var \Type
     */
    const resource = null;
    /**
     * @var \Type
     */
    const string = null;

    /**
     * @var string
     */
    public $name;
    /**
     * @var bool
     */
    public $isScalar;
    /**
     * @var bool
     */
    public $isInternal;
    /**
     * @var bool
     */
    public $isInterface;
    /**
     * @var bool
     */
    public $isTrait;
    /**
     * @var bool
     */
    public $isAbstract;
    /**
     * @var bool
     */
    public $isFinal;
    /**
     * @var bool
     */
    public $isDeprecated;
    /**
     * @var int
     */
    public $flags;
    /**
     * @var \Type\Constant[]
     */
    public $constants;
    /**
     * @var \Type\Property[]
     */
    public $properties;
    /**
     * @var \Type\Method[]
     */
    public $functions;
    
    /**
     * @param mixed $value
     * @return \Type
     */
    public static function of($value) : \Type { }

    /**
     * Type constructor.
     */
    private function __construct() { }
}