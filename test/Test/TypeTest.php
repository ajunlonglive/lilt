<?php declare(strict_types = 1);
namespace Test;
/**
 * Test TypeTest
 * @package \Test
 */
class TypeTest extends \PHPUnit_Framework_TestCase {

    public function testAClass() {
        $type = \AClass::type;
        $this->assertInstanceOf(\Type::class, $type);
    }
}