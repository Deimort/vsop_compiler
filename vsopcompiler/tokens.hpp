#pragma once

#include <string>
#include <map>

enum class Token : int
{
    // operators
    LBRACE = '{',
    RBRACE = '}',
    LPAR = '(',
    RPAR = ')',
    COLON = ':',
    SEMICOLON = ';',
    COMMA = ',',
    PLUS = '+',
    MINUS = '-',
    TIMES = '*',
    DIV = '/',
    POW = '^',
    DOT = '.',
    EQUAL = '=',
    LOWER = '<',
    LOWER_EQUAL = 257,
    ASSIGN,
    // keywords
    AND,
    BOOL,
    CLASS,
    DO,
    ELSE,
    EXTENDS,
    FALSE,
    IF,
    IN,
    INT,
    ISNULL,
    LET,
    NEW,
    NOT,
    SELF,
    STRING,
    THEN,
    TRUE,
    UNIT,
    WHILE,
    // literals
    INTEGER_LITERAL,
    STRING_LITERAL,
    // identifiers
    TYPE_IDENTIFIER,
    OBJECT_IDENTIFIER,
};

// create map from ascii token to string
static const std::map<Token, std::string> tokensMap{
    // operators
    {Token::LBRACE, "lbrace"},
    {Token::RBRACE, "rbrace"},
    {Token::LPAR, "lpar"},
    {Token::RPAR, "rpar"},
    {Token::COLON, "colon"},
    {Token::SEMICOLON, "semicolon"},
    {Token::COMMA, "comma"},
    {Token::PLUS, "plus"},
    {Token::MINUS, "minus"},
    {Token::TIMES, "times"},
    {Token::DIV, "div"},
    {Token::POW, "pow"},
    {Token::DOT, "dot"},
    {Token::EQUAL, "equal"},
    {Token::LOWER, "lower"},
    {Token::LOWER_EQUAL, "lower-equal"},
    {Token::ASSIGN, "assign"},
    // keywords
    {Token::AND, "and"},
    {Token::BOOL, "bool"},
    {Token::CLASS, "class"},
    {Token::DO, "do"},
    {Token::ELSE, "else"},
    {Token::EXTENDS, "extends"},
    {Token::FALSE, "false"},
    {Token::IF, "if"},
    {Token::IN, "in"},
    {Token::INT, "int32"},
    {Token::ISNULL, "isnull"},
    {Token::LET, "let"},
    {Token::NEW, "new"},
    {Token::NOT, "not"},
    {Token::SELF, "self"},
    {Token::STRING, "string"},
    {Token::THEN, "then"},
    {Token::TRUE, "true"},
    {Token::UNIT, "unit"},
    {Token::WHILE, "while"},
    // literals
    {Token::INTEGER_LITERAL, "integer-literal"},
    {Token::STRING_LITERAL, "string-literal"},
    // identifiers
    {Token::TYPE_IDENTIFIER, "type-identifier"},
    {Token::OBJECT_IDENTIFIER, "object-identifier"},
};

class TokenInfo {
public:
    TokenInfo(Token token, std::string value, int line, int column) : 
        token(token), value(value), line(line), column(column) {}
    Token getToken() const { return token; }
    std::string getTokenStr() const { return tokensMap.at(token); }
    std::string getValue() const { return value; }
    int getValueInt() const;
    int getLine() const { return line; }
    int getColumn() const { return column; }
    std::string to_string();
private:
    Token token;
    std::string value;
    int line;
    int column;
};