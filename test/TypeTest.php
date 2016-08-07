<?php
namespace Lilt\Test;
use Lilt\Type;

/**
 * Test TypeTest
 * @package Lilt\Test
 */
class TypeTest extends \PHPUnit_Framework_TestCase {

    public function testScalarTypes() {
        foreach (['\Lilt\Type::of', 'typeof'] as $fn) {
            self::assertEquals(Type::array(), $fn(['an array.']));
            self::assertEquals(Type::boolean(), $fn(false));
            self::assertEquals(Type::boolean(), $fn(true));
            self::assertEquals(Type::callable(), $fn(function () {}));
            self::assertEquals(Type::double(), $fn(0.1));
            self::assertEquals(Type::integer(), $fn(0));
            self::assertEquals(Type::null(), $fn(null));
            $resource = fopen(__FILE__, 'r');
            self::assertEquals(Type::resource(), $fn($resource));
            fclose($resource);
            self::assertEquals(Type::string(), $fn('an str value.'));
        }
    }
}
