<?php
namespace Lilt\Test;
use Lilt\EnumTrait;
use Lilt\IEnum;

/**
 * Class AnEnum
 * @package Lilt\Test
 */
class AnEnum implements IEnum {
    use EnumTrait;

    const CONST1 = 0;
    const CONST2 = 1 << 0;
    const CONST3 = 1 << 1;
    const CONST4 = 1 << 2;
    const CONST5 = 1 << 3;
}