<?php declare(strict_types = 1);

/**
 * Class Type
 * @property  [] properties
 * @property  [] functions
 * @package \
 */
final class Type extends \ReflectionClass implements \Typed, \Stringable {

    /**
     * @var \Type
     */
    const ARRAY = 'array';
    /**
     * @var \Type
     */
    const BOOLEAN = 'boolean';
    /**
     * @var \Type
     */
    const CALLABLE = 'Closure';
    /**
     * @var \Type
     */
    const DOUBLE = 'double';
    /**
     * @var \Type
     */
    const INTEGER = 'integer';
    /**
     * @var \Type
     */
    const NULL = 'NULL';
    /**
     * @var \Type
     */
    const RESOURCE = 'resource';
    /**
     * @var \Type
     */
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
     * @throws \Error
     */
    final public static function __static() {
        if (!\function_exists('uopz_redefine')) {
            throw new \Error('Uopz extension must be installed.');
        }
        \uopz_redefine(static::class, 'type', self::fromClass(static::class));
        /** @noinspection PhpStrictTypeCheckingInspection */ {
            \uopz_redefine(self::class, 'ARRAY', new static(self::ARRAY, true));
            \uopz_redefine(self::class, 'BOOLEAN', new static(self::BOOLEAN, true));
            \uopz_redefine(self::class, 'CALLABLE', new static(self::CALLABLE, false));
            \uopz_redefine(self::class, 'DOUBLE', new static(self::DOUBLE, true));
            \uopz_redefine(self::class, 'INTEGER', new static(self::INTEGER, true));
            \uopz_redefine(self::class, 'NULL', new static(self::NULL, true));
            \uopz_redefine(self::class, 'RESOURCE', new static(self::RESOURCE, true));
            \uopz_redefine(self::class, 'STRING', new static(self::STRING, true));
        }
    }

    /**
     * @param string $class
     * @return \Type
     */
    public static function fromClass(string $class) : self {
        return $GLOBALS['__types'][$class] ?? $GLOBALS['__types'][$class] = new self($class, false);
    }

    /**
     * @param mixed $of
     * @return \Type
     */
    public static function of($of) : self {
        switch ($type = gettype($of)) {
            case 'array':
                return self::ARRAY;
            case 'boolean':
                return self::BOOLEAN;
            case 'double':
                return self::DOUBLE;
            case 'integer':
                return self::INTEGER;
            case 'NULL':
                return self::NULL;
            case 'resource':
                return self::RESOURCE;
            case 'string':
                if (\class_exists($of)) {
                    return $GLOBALS['__types'][$of] ?? $GLOBALS['__types'][$of] = new self($of, false);
                }
                return self::STRING;
            case 'object':
                $type = get_class($of);
                return $GLOBALS['__types'][$type] ?? $GLOBALS['__types'][$type] = new self($type, false);
            default:
                return new self($type, true);
        }
    }

    /**
     * @return \Type
     */
    public static function type() : self {
        return static::type;
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
     * @param \Type $other
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
        return $this->_type === 'array';
    }

    /**
     * @return bool
     */
    public function isBoolean() : bool {
        return $this->_type === 'boolean';
    }

    /**
     * @return bool
     */
    public function isCallable() : bool {
        return $this->_type === 'Closure';
    }

    /**
     * @return bool
     */
    public function isDouble() : bool {
        return $this->_type === 'double';
    }

    /**
     * @return bool
     */
    public function isInteger() : bool {
        return $this->_type === 'integer';
    }

    /**
     * @return bool
     */
    public function isNull() : bool {
        return $this->_type === 'NULL';
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
        return $this->_type === 'resource';
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
        return $this->_type === 'string';
    }
}