<?php
/**
 * Test TypeTest
 * @package \
 */
class TypeTest extends \PHPUnit_Framework_TestCase {

    public function testTypes() {
        self::assertEquals(\Type::ARRAY, \Type::of(['an array.']));
        self::assertTrue(\Type::of(['an array.'])->isArray());
        self::assertTrue(\Type::of(['an array.'])->isScalar());
        self::assertEquals(\Type::BOOLEAN, \Type::of(false));
        self::assertTrue(\Type::of(false)->isBoolean());
        self::assertTrue(\Type::of(false)->isScalar());
        self::assertEquals(\Type::BOOLEAN, \Type::of(true));
        self::assertTrue(\Type::of(true)->isBoolean());
        self::assertTrue(\Type::of(true)->isScalar());
        self::assertEquals(\Type::CALLABLE, \Type::of(function () {}));
        self::assertTrue(\Type::of(function () {})->isCallable());
        self::assertFalse(\Type::of(function () {})->isScalar());
        self::assertEquals(\Type::DOUBLE, \Type::of(0.1));
        self::assertTrue(\Type::of(0.1)->isDouble());
        self::assertTrue(\Type::of(0.1)->isScalar());
        self::assertEquals(\Type::INTEGER, \Type::of(0));
        self::assertTrue(\Type::of(0)->isInteger());
        self::assertTrue(\Type::of(0)->isScalar());
        self::assertEquals(\Type::NULL, \Type::of(null));
        self::assertTrue(\Type::of(null)->isNull());
        self::assertTrue(\Type::of(null)->isScalar());
        $resource = fopen(__FILE__, 'r');
        self::assertEquals(\Type::RESOURCE, \Type::of($resource));
        self::assertTrue(\Type::of($resource)->isResource());
        self::assertTrue(\Type::of($resource)->isScalar());
        fclose($resource);
        self::assertEquals(\Type::STRING, \Type::of('an str value.'));
        self::assertTrue(\Type::of('an str value.')->isString());
        self::assertTrue(\Type::of('an str value.')->isScalar());
        self::assertEquals(\Type::class, (string)\Type::of(\Type::class));
        self::assertEquals(\Type::class, \Type::of(\Type::class)->name);
        self::assertTrue(\Type::of(\Type::class)->isObject());
        self::assertTrue(\Type::of(\ReflectionClass::class)->coincide(\Type::of(\Type::class)));
        self::assertTrue(\Type::of(\Type::class)->coincide(\Type::of(\Type::class)));
        self::assertTrue(\Type::of(['an array.'])->coincide(\Type::of(['an array.'])));
        /** @noinspection ImplicitMagicMethodCallInspection */
        self::assertEquals([
            'type' => \Type::ARRAY,
            'scalar' => true
        ], \Type::of(['an array.'])->__debugInfo());
    }
}
