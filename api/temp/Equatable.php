<?php declare(strict_types=1);
/**
 * Interface Equatable
 * @package \
 */
interface Equatable extends \Typed, \Hashable {

    /**
     * @param \IObject|null $x
     * @return bool
     */
    public function __equals(?\IObject $x) : bool;
}