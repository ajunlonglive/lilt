<?php declare(strict_types=1);
/** @var \Composer\Autoload\ClassLoader $loader */
$loader = require __DIR__.'/vendor/autoload.php';
$loader->unregister();
spl_autoload_register(function($class) use($loader) {
    if (($result = $loader->loadClass($class)) === true) {
        $r = new ReflectionClass($class);
        if ($r->hasMethod('__static')) {
            /** @noinspection PhpUndefinedMethodInspection */
            $class::__static();
        }
    }

    return $result;
});

return $loader;