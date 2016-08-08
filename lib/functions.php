<?php
/**
 * @param mixed $var
 * @return \Lilt\Type
 */
function typeof($var) : \Lilt\Type {
    return \Lilt\Type::of($var);
}

/**
 * @param int  $build
 * @param int  $major
 * @param int  $minor
 * @param ?int $revision
 * @return Lilt\Version
 */
function version(int $build = 0, int $major = 0, int $minor = 1, ?int $revision = null) : Lilt\Version {
    return new Lilt\Version($build, $major, $minor, $revision);
}