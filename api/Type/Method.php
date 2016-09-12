<?php declare(strict_types = 1);
namespace Type;
/**
 * Class Method
 * @package \Type
 */
final class Method {

    /**
     * @var \Type\ArgInfo[]
     */
    public $argInfos;
    /**
     * @var \Type|null
     */
    public $class;
    /**
     * @var int
     */
    public $flags;
    /**
     * @var string
     */
    public $name;

    /**
     * Method constructor.
     */
    private function __construct() { }
}