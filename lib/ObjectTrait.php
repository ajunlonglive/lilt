<?php
namespace Lilt;
/**
 * Class ObjectTrait
 * @package Lilt
 */
trait ObjectTrait {

    /**
     * @return Type
     */
    public static function class() : Type {
        return Type::of(static::class);
    }
}