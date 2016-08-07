<?php
namespace Lilt;
/**
 * Trait SingletonTrait
 * @package Lilt
 */
trait SingletonTrait {
    use ObjectTrait;

    /**
     * @var static[]
     */
    protected static $_instances;

    /**
     * @return static
     */
    public static function matter() : self {
        return static::$_instances[static::class] ?? (static::$_instances[static::class] = new static());
    }
}