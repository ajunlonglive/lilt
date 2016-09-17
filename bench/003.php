<?php declare(strict_types=1);
use Lilt\Bench;

$array = [];
$object = new Foo;

Bench\run(
    Bench\process()->description('switch []')->function(function () use($array) {
        switch (gettype($array)) {
            case 'string': break;
            case 'resource': break;
            case 'NULL': break;
            case 'integer': break;
            case 'double': break;
            case 'boolean': break;
            case 'array': break;
        }
    }),
    Bench\process()->description('switch [] Type')->function(function () use($array) {
        switch (\typeof($array)) {
            case \Type::string: break;
            case \Type::resource: break;
            case \Type::null: break;
            case \Type::integer: break;
            case \Type::double: break;
            case \Type::boolean: break;
            case \Type::array: break;
        }
    }),
    Bench\process()->description('switch object')->function(function () use($object) {
        switch (is_object($object) ? get_class($object) : gettype($object)) {
            case 'string': break;
            case 'resource': break;
            case 'NULL': break;
            case 'integer': break;
            case 'double': break;
            case 'boolean': break;
            case 'array': break;
            case Foo::class: break;
        }
    }),
    Bench\process()->description('switch object Type')->function(function () use($object) {
        switch (\typeof($object)) {
            case \Type::string: break;
            case \Type::resource: break;
            case \Type::null: break;
            case \Type::integer: break;
            case \Type::double: break;
            case \Type::boolean: break;
            case \Type::array: break;
            case Foo::type: break;
        }
    })
);