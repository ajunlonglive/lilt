<?php declare(strict_types = 1);
namespace Test;
/**
 * Test TypeTest
 * @package \Test
 */
class TypeTest extends \PHPUnit_Framework_TestCase {

    public function testTypeof() {
        $type = \typeof(true);
        $this->assertInstanceOf(\Type::class, $type);
        $type = \classtype(\AClass::class);
        $this->assertInstanceOf(\Type::class, $type);
        $this->assertEquals(2, count($type->constants));
        $this->assertEquals(3, count($type->properties));
        $this->assertEquals(3, count($type->functions));
    }

    public function testAClass() {
        $this->assertInstanceOf(\Typed::class, new \AClass);
        $type = \AClass::type;
        $this->assertInstanceOf(\Type::class, $type);
        $this->assertEquals(2, count($type->constants));
        $this->assertEquals(3, count($type->properties));
        $this->assertEquals(3, count($type->functions));
    }
}