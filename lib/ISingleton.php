<?php
namespace Lilt;
/**
 * Interface ISingleton
 * @package Lilt
 */
interface ISingleton extends IObject {

    /**
     * @return static
     */
    public static function matter();
}