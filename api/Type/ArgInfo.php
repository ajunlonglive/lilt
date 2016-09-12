<?php declare(strict_types = 1);
namespace Type;
/**
 * Class ArgInfo
 * @package \Type
 */
final class ArgInfo {

    /**
     * @var boolean
     */
    public $byReference;
    /**
     * @var string
     */
    public $name;
    /**
     * @var boolean
     */
    public $nullable;
    /**
     * @var boolean
     */
    public $typeHint;
    /**
     * @var boolean
     */
    public $variadic;

    /**
     * ArgInfo constructor.
     */
    private function __construct() { }
}