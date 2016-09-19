<?php declare(strict_types = 1);
/**
 * Interface IStaticInit
 * @package \
 */
interface IStaticInit {

    /**
     * This method call on class initialization
     * @return void
     */
    public static function __static() : void;
}