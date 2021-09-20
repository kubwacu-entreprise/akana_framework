<?php
    namespace users\Models;

    use Akana\ORM\Model;

    class User extends Model{
        public $pk;
        public $first_name;
        public $last_name;
        public $email;
        public $phone;
        public $password; 
        public $created_at;

        public static $params = [
            "pk" => ["type" => "int"],
            "first_name" => ["type" => "str", "max_length" => 50],
            "last_name" => ["type" => "str", "max_length" => 50],
            "email" => ["type" => "str", "max_length" => 50],
            "phone" => ["type" => "str", "max_length" => 20, 'nullable' => true],
            "password" => ["type" => "str", "max_length" => 100],
            "created_at" => ["type" => "datetime"]
        ];
    }