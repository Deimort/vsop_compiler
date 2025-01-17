/* This flex/bison example is provided to you as a starting point for your
 * assignment. You are free to use its code in your project.
 *
 * This example implements a simple calculator. You can use the '-l' flag to
 * list all the tokens found in the source file, and the '-p' flag (or no flag)
 * to parse the file and to compute the result.
 *
 * Also, if you have any suggestions for improvements, please let us know.
 */

#include <iostream>
#include <string>
#include <map>

#include "driver.hpp"
#include "parser.hpp"

using namespace std;
using namespace VSOP;

/**
 * @brief Map a token type to a string.
 */
static const std::map<Parser::token_type, string> type_to_string{
    // operators
    {Parser::token::LBRACE, "lbrace"},
    {Parser::token::RBRACE, "rbrace"},
    {Parser::token::LPAR, "lpar"},
    {Parser::token::RPAR, "rpar"},
    {Parser::token::COLON, "colon"},
    {Parser::token::SEMICOLON, "semicolon"},
    {Parser::token::COMMA, "comma"},
    {Parser::token::PLUS, "plus"},
    {Parser::token::MINUS, "minus"},
    {Parser::token::TIMES, "times"},
    {Parser::token::DIV, "div"},
    {Parser::token::POW, "pow"},
    {Parser::token::DOT, "dot"},
    {Parser::token::EQUAL, "equal"},
    {Parser::token::LOWER, "lower"},
    {Parser::token::LOWER_EQUAL, "lower-equal"},
    {Parser::token::ASSIGN, "assign"},
    // keywords
    {Parser::token::AND, "and"},
    {Parser::token::BOOL, "bool"},
    {Parser::token::CLASS, "class"},
    {Parser::token::DO, "do"},
    {Parser::token::ELSE, "else"},
    {Parser::token::EXTENDS, "extends"},
    {Parser::token::FALSE, "false"},
    {Parser::token::IF, "if"},
    {Parser::token::IN, "in"},
    {Parser::token::INT32, "int32"},
    {Parser::token::ISNULL, "isnull"},
    {Parser::token::LET, "let"},
    {Parser::token::NEW, "new"},
    {Parser::token::NOT, "not"},
    {Parser::token::SELF, "self"},
    {Parser::token::STRING, "string"},
    {Parser::token::THEN, "then"},
    {Parser::token::TRUE, "true"},
    {Parser::token::UNIT, "unit"},
    {Parser::token::WHILE, "while"},
    // literals
    {Parser::token::INTEGER_LITERAL, "integer-literal"},
    {Parser::token::STRING_LITERAL, "string-literal"},
    // identifiers
    {Parser::token::TYPE_IDENTIFIER, "type-identifier"},
    {Parser::token::OBJECT_IDENTIFIER, "object-identifier"},
};

/**
 * @brief Print the information about a token
 *
 * @param token the token
 */
static void print_token(Parser::symbol_type token)
{
    position pos = token.location.begin;
    auto type = (Parser::token_type)token.type_get();

    cout << pos.line << ","
         << pos.column << ","
         << type_to_string.at(type);

    switch (type)
    {
    case Parser::token::INTEGER_LITERAL:
    {
        int value = token.value.as<int>();
        cout << "," << value;
        break;
    }

    case Parser::token::TYPE_IDENTIFIER:
    {
        string id = token.value.as<string>();
        cout << "," << id;
        break;
    }

    case Parser::token::OBJECT_IDENTIFIER:
    {
        string id = token.value.as<string>();
        cout << "," << id;
        break;
    }

    case Parser::token::STRING_LITERAL:
    {
        string id = token.value.as<string>();
        cout << "," << id;
        break;
    }

    default:
        break;
    }

    cout << endl;
}

int Driver::lex()
{
    scan_begin();

    int error = 0;

    while (true)
    {
        Parser::symbol_type token = yylex();

        if ((Parser::token_type)token.type_get() == Parser::token::YYEOF || (Parser::token_type)token.type_get() == Parser::token::YYerror)
        {
            if ((Parser::token_type)token.type_get() == Parser::token::YYerror)
                error = 1;
            break;
        }
        if ((Parser::token_type)token.type_get() != Parser::token::YYerror)
            print_token(token);
    }

    scan_end();

    return error;
}

int Driver::parse()
{
    scan_begin();

    parser = make_shared<Parser>(*this);

    int res = parser->parse();
    scan_end();

    return res;
}

int Driver::check()
{
    scan_begin();

    parser = make_shared<Parser>(*this);

    int res = parser->parse();
    auto type_checker = std::make_shared<TypeCheckerVisitor>(*this->program);
    GenericErrorHandler handler(this->source_file, type_checker);
    if (res != 0)
        return res;
    res = handler.handle(*this->program);
    scan_end();

    return res;
}
