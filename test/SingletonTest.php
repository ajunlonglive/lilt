<?php
/**
 * Class SingletonTest
 * @package \
 */
class SingletonTest extends \PHPUnit_Framework_TestCase {

    public function testMatter() {
        self::assertInstanceOf(ASingleton::class, ASingleton::instance);
        self::assertInstanceOf(AnInheritedSingleton::class, AnInheritedSingleton::instance);
    }
}