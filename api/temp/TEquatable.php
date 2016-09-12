<?php declare(strict_types = 1);
/**
 * Trait TEquatable
 * @package \
 */
trait TEquatable {
    use \TTyped;
    use \THashable;

    /**
     * @param \IObject|null $x
     * @return bool
     */
    public function __equals(?\IObject $x) : bool {
        if ($x === null || static::type !== $x::type) {
            return false;
        }

        return $this->__hash() === $x->__hash();
    }
}