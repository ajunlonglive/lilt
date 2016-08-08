<?php
namespace Lilt\Test;
/**
 * Test EnumTraitTest
 * @package Lilt\Test
 */
class EnumTraitTest extends \PHPUnit_Framework_TestCase {

    public function testHas() {
        self::assertTrue(AnEnum::has(0));
        self::assertTrue(AnEnum::has(1));
        self::assertTrue(AnEnum::has(2));
        self::assertTrue(AnEnum::has(4));
        self::assertTrue(AnEnum::has(8));
        self::assertFalse(AnEnum::has(16));
    }

    public function testValues() {
        self::assertEquals([
            'CONST1' => 0,
            'CONST2' => 1,
            'CONST3' => 2,
            'CONST4' => 4,
            'CONST5' => 8
        ], AnEnum::values());
    }
}
