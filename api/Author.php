<?php declare(strict_types = 1);

/**
 * Class Author
 * @package \
 */
class Author extends Object {

    /**
     * @var ?\Email
     */
    public $email;
    /**
     * @var ?string
     */
    public $firstname;
    /**
     * @var ?string
     */
    public $lastname;
    /**
     * @var ?string
     */
    public $nickname;
    /**
     * @var ?string
     */
    public $website;

    /**
     * @param \Author|array|null $args
     * @param bool       $nullable
     * @return static|null
     * @throws \InvalidArgumentException
     */
    public static function make($args = null, bool $nullable = true) {
        switch (\Type::of($args)) {
            case static::type:
                return $args;
            case \Type::NULL:
                return new static;
            case \Type::ARRAY:
                return new static(
                    $args['firstname'] ?? $args[0] ?? null,
                    $args['lastname'] ?? $args[1] ?? null,
                    $args['nickname'] ?? $args[2] ?? null,
                    \Email::make($args['email'] ?? $args[3] ?? null, true),
                    $args['website'] ?? $args[4] ?? null
                );
            default:
                if ($nullable) {
                    return null;
                }
                throw new \InvalidArgumentException(
                    'Unable to create author from given argument: "'.Type::of($args).'".'
                );
        }
    }

    /**
     * Author constructor.
     * @param string|null $firstname
     * @param string|null $lastname
     * @param string|null $nickname
     * @param \Email|null $email
     * @param string|null $website
     */
    public function __construct(?string $firstname = null, ?string $lastname = null, ?string $nickname = null, ?\Email $email = null,
        ?string $website = null) {
        $r = new ReflectionClass();
        $this->firstname = $firstname;
        $this->lastname = $lastname;
        $this->nickname = $nickname;
        $this->email = $email;
        $this->website = $website;
    }

    /**
     * @param \IObject|null $x
     * @return bool
     */
    public function __equals(?\IObject $x) : bool {
        return $x !== null && $x instanceof static && $x->firstname === $this->firstname && $x->lastname === $this->lastname &&
            $x->nickname === $this->nickname && $x->email === $this->email && $x->website === $this->website;
    }

    /**
     * @return int
     */
    public function __hash() : int {
        $result = 17;
        $result = 31 * $result + ($this->firstname ? crc32($this->firstname) : 0);
        $result = 31 * $result + ($this->lastname ? crc32($this->lastname) : 0);
        $result = 31 * $result + ($this->nickname ? crc32($this->nickname) : 0);
        $result = 31 * $result + ($this->email ? crc32((string)$this->email) : 0);
        $result = 31 * $result + ($this->nickname ? crc32($this->nickname) : 0);

        return $result;
    }

    /**
     * @return string
     */
    public function __toString() : string {
        $result = $this->firstname.($this->lastname ? ($this->firstname ? ' ' : '').$this->lastname : '');
        if ($this->nickname !== null) {
            $result = $this->nickname.($result ? ' ('.$result.')' : '');
        }
        if ($this->email !== null) {
            $result .= ' <'.$this->email.'>';
        }

        return $result;
    }

    /**
     * @param \Email|null $email
     * @return static
     */
    public function email(?\Email $email) {
        $this->email = $email;

        return $this;
    }

    /**
     * @param string|null $firstname
     * @return static
     */
    public function firstname(?string $firstname) {
        $this->firstname = $firstname;

        return $this;
    }

    /**
     * @param string|null $lastname
     * @return static
     */
    public function lastname(?string $lastname) {
        $this->lastname = $lastname;

        return $this;
    }

    /**
     * @param string|null $nickname
     * @return static
     */
    public function nickname(?string $nickname) {
        $this->nickname = $nickname;

        return $this;
    }

    /**
     * @param string|null $website
     * @return static
     */
    public function website(?string $website) {
        $this->website = $website;

        return $this;
    }
}