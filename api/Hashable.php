<?php declare(strict_types=1);
/**
 * Interface Hashable
 * @package \
 */
interface Hashable {

    /**
     * @return int
     */
    public function __hash() : int;
}