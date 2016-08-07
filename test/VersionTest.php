<?php
namespace Lilt\Test;
use Lilt\Version;

/**
 * Test VersionTest
 * @package Lilt\Test
 */
class VersionTest extends \PHPUnit_Framework_TestCase {

    public function testConstruct() {
        $version = new Version;
        self::assertEquals(0, $version->build);
        self::assertEquals(0, $version->major);
        self::assertEquals(1, $version->minor);
        self::assertEquals(null, $version->revision);
        $version = new Version(3, 2, 1, 0);
        self::assertEquals(3, $version->build);
        self::assertEquals(2, $version->major);
        self::assertEquals(1, $version->minor);
        self::assertEquals(null, $version->revision);
    }

    public function testToString() {
        $version = new Version;
        self::assertEquals('0.0.1', (string)$version);
        $version = new Version(3, 2, 1, 0);
        self::assertEquals('3.2.1', (string)$version);
    }
}
