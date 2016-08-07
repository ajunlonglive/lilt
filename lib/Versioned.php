<?php
namespace Lilt;
/**
 * Interface Versionable
 * @package Lilt
 */
interface Versioned {
    /**
     * @return Version
     */
    public function getVersion() : Version;
}