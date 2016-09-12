<?php declare(strict_types = 1);
/**
 * Trait TTyped
 * @package \
 */
trait TTyped {

    /**
     * TTyped static constructor.
     * @throws \Error
     */
    final public static function __static() {
        if (!\function_exists('uopz_redefine')) {
            throw new \Error('Uopz extension must be installed.');
        }
        \uopz_redefine(static::class, 'type', \Type::fromClass(static::class));
    }

    /**
     * @return \Type
     */
    public static function type() : \Type {
        return static::type;
    }
}