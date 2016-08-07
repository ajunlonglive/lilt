<?php
namespace Lilt;
/**
 * Interface IEnum
 * @package Lilt
 */
interface IEnum extends IObject {

    /**
     * @return array
     */
    public static function values() : array;

    /**
     * @param mixed $value
     * @return bool
     */
    public static function has($value) : bool;
}