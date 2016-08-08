<?php
namespace Lilt;
/**
 * Class Type
 * @package Lilt
 */
final class Type extends \ReflectionClass implements IObject, Stringable {
    use ObjectTrait;

    const ARRAY = 'array';
    const BOOLEAN = 'boolean';
    const CALLABLE = 'Closure';
    const DOUBLE = 'double';
    const INTEGER = 'integer';
    const NULL = 'NULL';
    const RESOURCE = 'resource';
    const STRING = 'string';

    /**
     * @var bool
     */
    private $_scalar = false;
    /**
     * @var string
     */
    private $_type;
    /**
     * @var Type[]
     */
    private static $_types = [];

    /**
     * @return Type
     */
    public static function array() : self {
        return self::$_types[self::ARRAY] ?? self::$_types[self::ARRAY] = new self(self::ARRAY, true);
    }

    /**
     * @return Type
     */
    public static function boolean() : self {
        return self::$_types[self::BOOLEAN] ?? self::$_types[self::BOOLEAN] = new self(self::BOOLEAN, true);
    }

    /**
     * @return Type
     */
    public static function callable() : self {
        return self::$_types[self::CALLABLE] ?? self::$_types[self::CALLABLE] = new self(self::CALLABLE, true);
    }

    /**
     * @return Type
     */
    public static function double() : self {
        return self::$_types[self::DOUBLE] ?? self::$_types[self::DOUBLE] = new self(self::DOUBLE, true);
    }

    /**
     * @return Type
     */
    public static function integer() : self {
        return self::$_types[self::INTEGER] ?? self::$_types[self::INTEGER] = new self(self::INTEGER, true);
    }

    /**
     * @return Type
     */
    public static function null() : self {
        return self::$_types[self::NULL] ?? self::$_types[self::NULL] = new self(self::NULL, true);
    }

    /**
     * @param mixed $var
     * @return Type
     */
    public static function of($var) : self {
        $type = ($isClass = is_object($var)) ? get_class($var) :
            (is_string($var) ? (($isClass = class_exists($var)) ? $var : gettype($var)) : gettype($var));

        return self::$_types[$type] ?? self::$_types[$type] = new self($type, !$isClass);
    }

    /**
     * @return Type
     */
    public static function resource() : self {
        return self::$_types[self::RESOURCE] ?? self::$_types[self::RESOURCE] = new self(self::RESOURCE, true);
    }

    /**
     * @return Type
     */
    public static function string() : self {
        return self::$_types[self::STRING] ?? self::$_types[self::STRING] = new self(self::STRING, true);
    }

    /**
     * Type constructor.
     * @param string $type
     * @param bool   $scalar
     */
    public function __construct(string $type, bool $scalar) {
        $this->_type = $type;
        $this->_scalar = $scalar;
        if (($this->_scalar = $scalar) === false) {
            parent::__construct($type);
        }
    }

    /**
     * @return array
     */
    public function __debugInfo() : array {
        return ['type' => $this->_type, 'scalar' => $this->_scalar];
    }

    /**
     * @return string
     */
    public function __toString() : string {
        return $this->_type;
    }

    /**
     * @param Type $other
     * @return bool
     */
    public function coincide(self $other) : bool {
        if ($this->_scalar) {
            return $this->_type === $other->_type;
        }
        if ($this->_type === $other->_type) {
            return true;
        }

        return $other->isSubclassOf($this->_type);
    }

    /**
     * @return bool
     */
    public function isArray() : bool {
        return $this->_type === self::ARRAY;
    }

    /**
     * @return bool
     */
    public function isBoolean() : bool {
        return $this->_type === self::BOOLEAN;
    }

    /**
     * @return bool
     */
    public function isCallable() : bool {
        return $this->_type === self::CALLABLE;
    }

    /**
     * @return bool
     */
    public function isDouble() : bool {
        return $this->_type === self::DOUBLE;
    }

    /**
     * @return bool
     */
    public function isInteger() : bool {
        return $this->_type === self::INTEGER;
    }

    /**
     * @return bool
     */
    public function isNull() : bool {
        return $this->_type === self::NULL;
    }

    /**
     * @return bool
     */
    public function isObject() : bool {
        return !$this->_scalar;
    }

    /**
     * @return bool
     */
    public function isResource() : bool {
        return $this->_type === self::RESOURCE;
    }

    /**
     * @return bool
     */
    public function isScalar() : bool {
        return $this->_scalar;
    }

    /**
     * @return bool
     */
    public function isString() : bool {
        return $this->_type === self::STRING;
    }
}