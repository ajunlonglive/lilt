<?php
/**
 * Test VersionTest
 * @package \
 */
class VersionTest extends \PHPUnit_Framework_TestCase {

    public function testConstruct() {
        $version = new \Version;
        self::assertEquals(null, $version->major);
        self::assertEquals(null, $version->minor);
        self::assertEquals(null, $version->build);
        self::assertEquals(null, $version->revision);
        $version = new \Version(3, 2, 1, 0);
        self::assertEquals(3, $version->major);
        self::assertEquals(2, $version->minor);
        self::assertEquals(1, $version->build);
        self::assertEquals(0, $version->revision);
    }

    public function testToString() {
        $version = new \Version();
        self::assertEquals('', (string)$version);
        $version = new \Version(3, 2, 1, 0);
        self::assertEquals('3.2.1.0', (string)$version);
        $version = new \Version(3, 2, 1, 100);
        self::assertEquals('3.2.1.100', (string)$version);
    }
}
