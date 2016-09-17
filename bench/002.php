<?php declare(strict_types=1);
use Lilt\Bench;

Bench\run(
    Bench\process()->description('is_array')->function(function () {
        $ret = is_array([]);
    }),
    Bench\process()->description('Type')->function(function () {
        $ret = \typeof([]) === \Type::array;
    })
);