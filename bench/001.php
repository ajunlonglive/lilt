<?php declare(strict_types=1);
use Lilt\Bench;

Bench\run(
    Bench\process()->description('ReflectionClass')->function(function () {
        $type = new ReflectionClass(Foo::class);
        $type->isInternal();
        $type->isInterface();
        $type->isTrait();
        $type->isFinal();
        $type->isAbstract();
        foreach ($type->getConstants() as $k => $v) { }
        foreach ($type->getProperties() as $k => $v) {
            $v->getDeclaringClass();
            $v->getDocComment();
            $v->getName();
        }
        foreach ($type->getMethods() as $k => $v) {
            $v->getDeclaringClass();
            $v->getDocComment();
            $v->getName();
        }
    }),
    Bench\process()->description('Type')->function(function () {
        $type = Foo::type;
        $type->isInternal;
        $type->isInterface;
        $type->isTrait;
        $type->isFinal;
        $type->isAbstract;
        foreach ($type->constants as $k => $v) { }
        foreach ($type->properties as $k => $v) {
            $v->class;
            $v->docComment;
            $v->name;
        }
        foreach ($type->functions as $k => $v) {
            $v->class;
            $v->docComment;
            $v->name;
        }
    })
);