<?php
namespace Lilt\Test;
/**
 * Class SingletonTest
 * @package Lilt\Test
 */
class SingletonTest extends \PHPUnit_Framework_TestCase {

    public function testMatter() {
        self::assertInstanceOf(ASingleton::class, ASingleton::matter());
        self::assertInstanceOf(AnInheritedSingleton::class, AnInheritedSingleton::matter());
    }
}