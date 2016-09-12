<?php declare(strict_types = 1);
/**
 * Class Version
 * @package \
 */
final class Version extends \Object {

    /**
     * @var ?int
     */
    public $build;
    /**
     * @var ?int
     */
    public $major;
    /**
     * @var ?int
     */
    public $minor;
    /**
     * @var ?int
     */
    public $revision;
    /**
     * @var ?string
     */
    public $tag;

    /**
     * @param \Version|array|string|null $args
     * @param bool                       $nullable
     * @return \Version|null
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
                    $args['major'] ?? $args[0] ?? null,
                    $args['minor'] ?? $args[1] ?? null,
                    $args['build'] ?? $args[2] ?? null,
                    $args['revision'] ?? $args[3] ?? null,
                    $args['tag'] ?? $args[4] ?? null
                );
            default:
                return $nullable ? null : new self;
        }
    }

    /**
     * @param string $str
     * @return \Version
     * @throws \InvalidArgumentException
     */
    public static function parse(string $str) : self {
        if (preg_match('/^(\d+)?\.?(\d+)?\.?(\d+)?\.?(\d+)?([a-zA-Z-_]*)$/i', $str, $matches)) {
            return new self(
                $matches[1] !== '' ? $matches[1] : null,
                $matches[2] !== '' ? $matches[2] : null,
                $matches[3] !== '' ? $matches[3] : null,
                $matches[4] !== '' ? $matches[4] : null,
                $matches[5] !== '' ? $matches[5] : null
            );
        }
        throw new \InvalidArgumentException(
            'Unable to parse the following string into version: "'.$str.'".'
        );
    }

    /**
     * Version constructor.
     * @param int|null    $major
     * @param int|null    $minor
     * @param int|null    $build
     * @param int|null    $revision
     * @param string|null $tag
     */
    public function __construct(?int $major = null, ?int $minor = null, ?int $build = null, ?int $revision = null, ?string $tag = null) {
        $this->major = $major;
        $this->minor = $minor;
        $this->build = $build;
        $this->revision = $revision;
        $this->tag = $tag;
    }

    /**
     * @param \IObject|null $x
     * @return bool
     */
    public function __equals(?\IObject $x) : bool {
        return $x !== null && $x instanceof self && $x->major === $this->major && $x->minor === $this->minor &&
        $x->build === $this->build && $x->revision === $this->revision && $x->tag === $this->tag;
    }

    /**
     * @return int
     */
    public function __hash() : int {
        $result = 17;
        $result = 31 * $result + $this->major;
        $result = 31 * $result + $this->minor;
        $result = 31 * $result + $this->build;
        $result = 31 * $result + $this->revision;
        $result = 31 * $result + ($this->tag ? crc32($this->tag) : 0);

        return $result;
    }

    /**
     * @return string
     */
    public function __toString() : string {
        return $this->minor !== null ? ($this->build !== null ? ($this->major !== null ?
            ($this->revision !== null ? $this->major.'.'.$this->minor.'.'.$this->build.'.'.$this->revision.$this->tag :
                $this->major.'.'.$this->minor.'.'.$this->build.$this->tag) : ($this->tag ?: '')) :
            ($this->major !== null ? $this->major.'.'.$this->minor.$this->tag : ($this->tag ?: ''))) :
            ($this->major !== null ? $this->major.$this->tag : ($this->tag ?: ''));
    }

    /**
     * @param int|null $build
     * @return \Version
     */
    public function build(?int $build) : self {
        $this->build = $build;

        return $this;
    }

    /**
     * @param int|null $major
     * @return \Version
     */
    public function major(?int $major) : self {
        $this->major = $major;

        return $this;
    }

    /**
     * @param int|null $minor
     * @return \Version
     */
    public function minor(?int $minor) : self {
        $this->minor = $minor;

        return $this;
    }

    /**
     * @param int|null $revision
     * @return \Version
     */
    public function revision(?int $revision) : self {
        $this->revision = $revision;

        return $this;
    }

    /**
     * @param string|null $tag
     * @return \Version
     */
    public function tag(?string $tag) : self {
        $this->tag = $tag;

        return $this;
    }
}
