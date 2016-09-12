<?php declare(strict_types = 1);
/**
 * Class Email
 * @package \
 */
final class Email extends \Object {

    const AT = '@';

    /**
     * @var string
     */
    public $prefix;
    /**
     * @var string
     */
    public $domain;

    /**
     * @param \Email|array|string $args
     * @param bool                $nullable
     * @return \Email|null
     * @throws \InvalidArgumentException
     */
    public static function make($args = null, bool $nullable = false) : ?self {
        switch (\Type::of($args)) {
            case self::type:
                return $args;
            case \Type::STRING:
                return self::parse($args);
            case \Type::ARRAY:
                return new self(
                    $args['prefix'] ?? $args[0] ?? '',
                    $args['domain'] ?? $args[1] ?? ''
                );
            default:
                if ($nullable) {
                    return null;
                }
                throw new \InvalidArgumentException(
                    'Unable to create email from given argument: "'.Type::of($args).'".'
                );
        }
    }

    /**
     * @param string $str
     * @return \Email
     * @throws \InvalidArgumentException
     */
    public static function parse(string $str) : self {
        if (preg_match('/\b([A-Z0-9._%+-]+)@((?:[A-Z0-9-]+\.)+[A-Z]{2,6})\b/i', $str, $matches)) {
            return new self($matches[1], $matches[2]);
        }
        throw new \InvalidArgumentException(
            'Unable to parse the following string into email: "'.$str.'".'
        );
    }

    /**
     * Email constructor.
     * @param string $prefix
     * @param string $domain
     */
    public function __construct(string $prefix = '', string $domain = '') {
        $this->prefix = $prefix;
        $this->domain = $domain;
    }

    /**
     * @param \IObject|null $x
     * @return bool
     */
    public function __equals(?\IObject $x) : bool {
        return $x !== null && $x instanceof self && $x->prefix === $this->prefix && $x->domain === $this->domain;
    }

    /**
     * @return int
     */
    public function __hash() : int {
        $result = 17;
        $result = 31 * $result + crc32($this->prefix);
        $result = 31 * $result + crc32($this->domain);

        return $result;
    }

    /**
     * @return string
     */
    public function __toString() : string {
        return $this->prefix.self::AT.$this->domain;
    }

    /**
     * @param string $prefix
     * @return \Email
     */
    public function prefix(string $prefix) : self {
        $this->prefix = $prefix;

        return $this;
    }

    /**
     * @param string $domain
     * @return \Email
     */
    public function domain(string $domain) : self {
        $this->domain = $domain;

        return $this;
    }
}