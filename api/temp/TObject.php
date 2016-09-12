<?php declare(strict_types=1);
/**
 * Trait TObject
 * @package \
 */
trait TObject {
    use \TEquatable;

    /**
     * @param null $args
     * @param bool $nullable
     * @return static
     */
    public static function make($args = null, bool $nullable = true) {
        return new static($args);
    }

    /**
     * @return string
     */
    public function __toString() : string {
        return \json_encode((array)$this);
    }
}