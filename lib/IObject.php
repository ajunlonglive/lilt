<?php
namespace Lilt;
/**
 * Interface IObject
 * @package Lilt
 */
interface IObject {

    /**
     * @return Type
     */
    public static function class() : Type;
}