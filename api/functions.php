<?php
if (!function_exists('typeof')) {

    /**
     * @param $of
     * @return \Type
     */
    function typeof($of) : \Type {
        switch ($type = gettype($of)) {
            case 'array':
                return \Type::ARRAY;
            case 'boolean':
                return \Type::BOOLEAN;
            case 'double':
                return \Type::DOUBLE;
            case 'integer':
                return \Type::INTEGER;
            case 'NULL':
                return \Type::NULL;
            case 'resource':
                return \Type::RESOURCE;
            case 'string':
                if (\class_exists($of)) {
                    return $GLOBALS['__types'][$of] ?? $GLOBALS['__types'][$of] = new \Type($of, false);
                }
                return \Type::STRING;
            case 'object':
                $type = get_class($of);
                return $GLOBALS['__types'][$type] ?? $GLOBALS['__types'][$type] = new \Type($type, false);
            default:
                return new \Type($type, true);
        }
    }
}