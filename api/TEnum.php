<?php declare(strict_types=1);
/**
 * Trait TEnum
 * @package \
 */
trait TEnum {
    use \TTyped {
        __static as private Enum__static;
    }

    /**
     * @var string
     */
    public $name;
    /**
     * @var mixed
     */
    public $value;

    /**
     * TEnum static constructor.
     * @throws \Error
     */
    final public static function __static() {
        static::Enum__static();
        if (static::class !== \TEnum::class) {
            if (!\function_exists('uopz_redefine')) {
                throw new \Error('Uopz extension must be installed.');
            }
            foreach (static::type()->getConstants() as $name => $value) {
                if ($name !== 'type' && $name !== 'VALUES') {
                    \uopz_redefine(static::class, $name, new static($name, $value));
                }
            }
            $values = static::type()->getConstants();
            unset($values['type'], $values['VALUES']);
            \uopz_redefine(static::class, 'VALUES', $values);
        }
    }

    /**
     * TEnum constructor.
     * @param string $name
     * @param mixed  $value
     */
    final private function __construct(string $name, $value) {
        $this->name = $name;
        $this->value = $value;
    }

    /**
     * @return string
     */
    public function __toString() : string {
        return \json_encode(static::VALUES);
    }
}