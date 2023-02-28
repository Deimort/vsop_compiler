#include "scanner.hpp"
#include "tokens.hpp"

int Scanner::makeToken(Token token) {
    return makeToken(token, std::string(yytext, yyleng));
}

int Scanner::makeToken(Token token, std::string value) {
    return makeToken(token, value, yylineno, column);
}

int Scanner::makeToken(Token token, std::string value, int line, int column) {
    std::cout << TokenInfo(token, value, line, column).to_string() << std::endl;
    countColumn();
    return static_cast<int>(token);
}

int Scanner::makeError(std::string value) {
    return makeError(value, yylineno, column);
}

int Scanner::makeError(std::string error, int line, int column) {
    std::cerr << fileName << ":" << line << ":" << column << ": " << error << std::endl;
    countColumn();
    hasError = true;
    return -1;
}

void Scanner::countColumn() {
    column += yyleng;
}

void Scanner::resetColumn() {
    column = 1;
}

bool Scanner::scan() {
    while (yylex() > 0);
    return hasError;
}