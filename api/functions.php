<?php
if (!function_exists('typeof')) {

    /**
     * @param $value
     * @return \Type
     */
    function typeof($value) : \Type { }
}
if (!function_exists('classtype')) {

    /**
     * @param string $classname
     * @return \Type
     */
    function classtype(string $classname) : \Type { }
}