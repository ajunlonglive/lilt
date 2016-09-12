<?php declare(strict_types=1);
/**
 * Interface ISingleton
 * @package \
 */
interface ISingleton extends IObject {

    /**
     * @var static
     */
    const instance = null;

    /**
     * @return static
     */
    public static function instance();
}