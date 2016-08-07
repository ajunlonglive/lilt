<?php
namespace Lilt;
/**
 * Trait EnumTrait
 * @package Lilt
 */
trait EnumTrait {
    use ObjectTrait;

    /**
     * @return array
     */
    public static function values() : array {
        return static::class()->getConstants();
    }

    /**
     * @param mixed $value
     * @return bool
     */
    public static function has($value) : bool {
        return in_array($value, static::class()->getConstants(), true);
    }
}