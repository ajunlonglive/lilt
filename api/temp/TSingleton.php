<?php declare(strict_types=1);
/**
 * Trait TSingleton
 * @package \
 */
trait TSingleton {
    use \TObject {
        __static as private TSingleton__static;
    }

    /**
     * TSingleton static constructor.
     * @throws \Error
     * @throws \RuntimeException
     */
    final public static function __static() {
        static::TSingleton__static();
        if (static::class !== \TSingleton::class) {
            if (!\function_exists('uopz_redefine')) {
                throw new \Error('Uopz extension must be installed.');
            }
            \uopz_redefine(static::class, 'instance', new static);
        }
    }

    /**
     * @return static
     */
    public static function instance() {
        return static::instance;
    }

    /**
     * TSingleton constructor.
     */
    protected function __construct() { }
}