<?php
namespace Lilt;
/**
 * @param int $build
 * @param int $major
 * @param int $minor
 * @param ?int $revision
 * @return Version
 */
function version(int $build = 0, int $major = 0, int $minor = 1, ?int $revision = null) : Version {
    return new Version($build, $major, $minor, $revision);
}