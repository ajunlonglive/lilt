<?php declare(strict_types = 1);
namespace Type;
/**
 * Class Constant
 * @package \Type
 */
final class Constant {

    /**
     * @var string
     */
    public $name;
    /**
     * @var \Type
     */
    public $class;
    /**
     * @var string
     */
    public $docComment;
    /**
     * @var mixed
     */
    public $value;

    /**
     * Constant constructor.
     */
    private function __construct() { }
}