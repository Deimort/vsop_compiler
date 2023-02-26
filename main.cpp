#include <iostream>
#include <string>
#include <fstream>
#include <FlexLexer.h>
#include "src/tokens.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " input_file\n";
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open())
    {
        std::cerr << "Error: could not open input file '" << argv[1] << "'\n";
        return 1;
    }

    yyFlexLexer lexer(&inputFile);

    int error = 0;
    int tokenID = 0;
    while (tokenID = lexer.yylex())
    {
        Token tokenType = static_cast<Token>(tokenID);
        std::string token = tokensMap.at(tokenType);
        std::string value = std::string(lexer.YYText(), lexer.YYLeng());
        int line = lexer.lineno();
        if (
            tokenType == Token::STRING_LITERAL ||
            tokenType == Token::OBJECT_IDENTIFIER ||
            tokenType == Token::TYPE_IDENTIFIER ||
            tokenType == Token::INTEGER_LITERAL ||
            tokenType == Token::ERROR)
            std::cout << line << "," << 12 << "," << token << "," << value << std::endl;
        else
            std::cout << line << "," << 12 << "," << token << std::endl;
    }
}