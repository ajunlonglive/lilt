<?php
namespace Lilt;
/**
 * Class Version
 * @package Lilt
 */
final class Version implements Stringable {

    /**
     * @var int
     */
    public $build;
    /**
     * @var int
     */
    public $major;
    /**
     * @var int
     */
    public $minor;
    /**
     * @var ?int
     */
    public $revision;

    /**
     * Version constructor.
     * @param int  $build
     * @param int  $major
     * @param int  $minor
     * @param ?int $revision
     */
    public function __construct(int $build = 0, int $major = 0, int $minor = 1, ?int $revision = null) {
        $this->build = $build;
        $this->major = $major;
        $this->minor = $minor;
        $this->revision = $revision > 0 ? $revision : null;
    }

    /**
     * @return string
     */
    public function __toString() : string {
        return $this->build.'.'.$this->major.'.'.$this->minor.($this->revision !== null ? '.'.$this->revision : '');
    }
}
