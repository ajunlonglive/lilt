<?php
namespace Lilt\Test;
use Lilt\ISingleton;
use Lilt\SingletonTrait;

/**
 * Class ASingleton
 * @package Lilt\Test
 */
class ASingleton implements ISingleton {
    use SingletonTrait;
}