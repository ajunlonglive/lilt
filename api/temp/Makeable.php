<?php declare(strict_types=1);
/**
 * Interface Makeable
 * @package \
 */
interface Makeable {

    /**
     * @param mixed $args
     * @param bool  $nullable
     * @return static
     */
    public static function make($args = null, bool $nullable = false);
}