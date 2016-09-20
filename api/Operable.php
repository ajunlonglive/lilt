<?php declare(strict_types = 1);
/**
 * Interface Operable
 * @package \
 */
interface Operable {

    /**
     * @param \Operator $operator
     * @param mixed     $value
     * @return mixed
     */
    public function __operate(\Operator $operator, $value);
}