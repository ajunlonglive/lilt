<?php declare(strict_types = 1);

/**
 * Trait THashable
 * @package \
 */
trait THashable {

    /**
     * @return int
     */
    public function __hash() : int {
        return \crc32(\serialize((array)$this));
    }
}