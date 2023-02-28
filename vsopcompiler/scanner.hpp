#pragma once
#ifndef yyFlexLexerOnce
#include <FlexLexer.h>
#endif
#include <vector>
#include "tokens.hpp"

class Scanner : public yyFlexLexer {
public:
    Scanner(std::istream *in, std::string fileName) : yyFlexLexer(in), fileName(fileName) {}
    virtual int yylex();
    int makeToken(Token token);
    int makeToken(Token token, std::string value);
    int makeToken(Token token, std::string value, int line, int column);
    int makeError(std::string value);
    int makeError(std::string value, int line, int column);
    void countColumn();
    void resetColumn();
    bool scan();
    std::vector<TokenInfo> getTokens() const;
    bool hasErrorOccured() const { return hasError; }

private:
    std::string fileName;
    int column = 1;
    bool hasError = false;
};