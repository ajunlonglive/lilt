<?php declare(strict_types=1);
use Lilt\Bench;

$foo = new Foo;

Bench\run(
    Bench\process()->description('typeof')->function(function () use($foo) {
        $ret = \typeof($foo);
    }),
    Bench\process()->description('Type::of')->function(function () use($foo) {
        $ret = \Type::of($foo);
    }),
    Bench\process()->description('classtype')->function(function () {
        $ret = \classtype(Foo::class);
    }),
    Bench\process()->description('::type')->function(function () {
        $ret = Foo::type;
    })
);