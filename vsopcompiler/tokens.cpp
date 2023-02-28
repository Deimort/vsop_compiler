#include <string>
#include "tokens.hpp"

int TokenInfo::getValueInt() const { 
    if(value.substr(0, 2) == "0x")
        return stoi(value, 0, 16);
    else
        return stoi(value);
}

std::string TokenInfo::to_string() {
    if (
        token == Token::STRING_LITERAL ||
        token == Token::OBJECT_IDENTIFIER ||
        token == Token::TYPE_IDENTIFIER ||
        token == Token::INTEGER_LITERAL)
        return std::to_string(line) + "," + std::to_string(column) + "," + getTokenStr() + "," + (token == Token::INTEGER_LITERAL ? std::to_string(getValueInt()) : value);
    else
        return std::to_string(line) + "," + std::to_string(column) + "," + getTokenStr();
}