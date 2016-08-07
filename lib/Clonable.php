<?php
namespace Lilt;
/**
 * Interface Clonable
 * @package Lilt
 */
interface Clonable {

    /**
     * @return static
     */
    public function __clone();
}