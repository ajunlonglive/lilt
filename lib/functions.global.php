<?php
/**
 * @param mixed $var
 * @return \Lilt\Type
 */
function typeof($var) : \Lilt\Type {
    return \Lilt\Type::of($var);
}