# lilt/lilt

[![Build Status](https://img.shields.io/travis/lilt-php/lilt/master.svg?style=flat-square)](https://travis-ci.org/liltphp/lilt)
[![Minimum PHP Version](https://img.shields.io/badge/php-%3E%3D%207.1-8892BF.svg?style=flat-square)](https://php.net/)
[![Latest Stable Version](https://poser.pugx.org/lilt/lilt/v/stable?format=flat-square)](https://packagist.org/packages/lilt/lilt)
[![Total Downloads](https://poser.pugx.org/lilt/lilt/downloads?format=flat-square)](https://packagist.org/packages/lilt/lilt)
[![License](https://poser.pugx.org/lilt/lilt/license?format=flat-square)](https://packagist.org/packages/lilt/lilt)

**Required PHP Version**

- PHP 7.1+ (NTS)

**Installation**

```bash
$ composer require lilt/lilt
$ echo "extension=lilt.so" >> /path/to/php.ini

or clone then

$ composer install
$ echo "extension=lilt.so" >> /path/to/php.ini
```

**Usage**

```php
// to type
class Foo implements Typed { }
class Bar implements Typed {
    /**
     * @var Foo
     */
    public $foo;
    
    public function __construct($var) {
        switch (\typeof($var)) {
            case \Type::string:
                // do something
                break;
            case \Type::resource:
                // do something
                break;
            case \Type::null: 
                // do something
                break;
            case \Type::integer: 
                // do something
                break;
            case \Type::double: 
                // do something
                break;
            case \Type::boolean: 
                // do something
                break;
            case \Type::array: 
                // do something
                break;
            case Foo::type: 
                $this->foo = $var;
                break;
        }
    }
}

// or as reflection
if (!(Bar::type)->isInternal) {
    foreach ((Bar::type)->properties as $k => $v) {
        if ($v->class === Bar::type) {
            if (preg_match('/@(\w+) (.+) ?(.+)/i', $v->docComment, $matches)) {
                echo $matches[1]; // var
                echo $matches[2]; // Foo
            }
        }
    }
}
```

**Benchmark**

```bash
$ composer bench
```

**Tests**

```bash
$ composer test
$ composer memtest
```
