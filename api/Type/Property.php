<?php declare(strict_types = 1);
namespace Type;
/**
 * Class Property
 * @package \Type
 */
final class Property {

    /**
     * @var string
     */
    public $name;
    /**
     * @var int
     */
    public $flags;
    /**
     * @var \Type
     */
    public $class;
    /**
     * @var string
     */
    public $docComment;

    /**
     * Property constructor.
     */
    private function __construct() { }
}