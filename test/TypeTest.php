<?php
namespace Lilt\Test;
use Lilt\Type;

/**
 * Test TypeTest
 * @package Lilt\Test
 */
class TypeTest extends \PHPUnit_Framework_TestCase {

    public function testTypes() {
        self::assertEquals(Type::array(), typeof(['an array.']));
        self::assertTrue(typeof(['an array.'])->isArray());
        self::assertTrue(typeof(['an array.'])->isScalar());
        self::assertEquals(Type::boolean(), typeof(false));
        self::assertTrue(typeof(false)->isBoolean());
        self::assertTrue(typeof(false)->isScalar());
        self::assertEquals(Type::boolean(), typeof(true));
        self::assertTrue(typeof(true)->isBoolean());
        self::assertTrue(typeof(true)->isScalar());
        self::assertEquals(Type::callable(), typeof(function () {}));
        self::assertTrue(typeof(function () {})->isCallable());
        self::assertTrue(typeof(function () {})->isScalar());
        self::assertEquals(Type::double(), typeof(0.1));
        self::assertTrue(typeof(0.1)->isDouble());
        self::assertTrue(typeof(0.1)->isScalar());
        self::assertEquals(Type::integer(), typeof(0));
        self::assertTrue(typeof(0)->isInteger());
        self::assertTrue(typeof(0)->isScalar());
        self::assertEquals(Type::null(), typeof(null));
        self::assertTrue(typeof(null)->isNull());
        self::assertTrue(typeof(null)->isScalar());
        $resource = fopen(__FILE__, 'r');
        self::assertEquals(Type::resource(), typeof($resource));
        self::assertTrue(typeof($resource)->isResource());
        self::assertTrue(typeof($resource)->isScalar());
        fclose($resource);
        self::assertEquals(Type::string(), typeof('an str value.'));
        self::assertTrue(typeof('an str value.')->isString());
        self::assertTrue(typeof('an str value.')->isScalar());
        self::assertEquals(Type::class, (string)typeof(Type::class));
        self::assertEquals(Type::class(), typeof(Type::class));
        self::assertEquals(Type::class, typeof(Type::class)->name);
        self::assertTrue(typeof(Type::class)->isObject());
        self::assertTrue(typeof(\ReflectionClass::class)->coincide(typeof(Type::class)));
        self::assertTrue(typeof(Type::class)->coincide(typeof(Type::class)));
        self::assertTrue(typeof(['an array.'])->coincide(typeof(['an array.'])));
        /** @noinspection ImplicitMagicMethodCallInspection */
        self::assertEquals([
            'type' => Type::ARRAY,
            'scalar' => true
        ], typeof(['an array.'])->__debugInfo());
    }
}
