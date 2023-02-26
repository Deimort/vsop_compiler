
%{
    /* Includes */
    #include <string>
    #include <iostream>
    #include <iomanip>
    #include <sstream>
    #include "tokens.hpp"
%}

%option c++ noyywrap nounput noinput batch yylineno

%{
    using namespace std;

    int makeToken(Token token);
    
    std::stringstream literalStringStream;
%}

lowercase_letter    [a-z]
uppercase_letter    [A-Z]
letter              {lowercase_letter}|{uppercase_letter}
bin_digit           [01]
digit               {bin_digit}|[2-9]
hex_digit           {digit}|[a-fA-F]
whitespace          " "|{tab}|{lf}|{ff}|{cr}
tab                 \t
lf                  \n
ff                  \f
cr                  \r
integer_literal     {digit}+|"0x"{hex_digit}+
type_identifier     {uppercase_letter}({letter}|{digit}|"_")*
object_identifier   {lowercase_letter}({letter}|{digit}|"_")*
escape_sequence     [btnr]|\\|"x"{hex_digit}{2}|"n"(" "|{tab})*
escaped_char        \\{escape_sequence}
regular_char        [^"\n\\]
string_literal      \"({regular_char}|{escaped_char})*\"

%x string
%x backslash
%%

    /* Operators */
"{"                 { return makeToken(Token::LBRACE); }
"}"                 { return makeToken(Token::RBRACE); }
"("                 { return makeToken(Token::LPAR); }
")"                 { return makeToken(Token::RPAR); }
":"                 { return makeToken(Token::COLON); }
";"                 { return makeToken(Token::SEMICOLON); }
","                 { return makeToken(Token::COMMA); }
"+"                 { return makeToken(Token::PLUS); }
"-"                 { return makeToken(Token::MINUS); }
"*"                 { return makeToken(Token::TIMES); }
"/"                 { return makeToken(Token::DIV); }
"^"                 { return makeToken(Token::POW); }
"."                 { return makeToken(Token::DOT); }
"="                 { return makeToken(Token::EQUAL); }
"<"                 { return makeToken(Token::LOWER); }
"<="                { return makeToken(Token::LOWER_EQUAL); }
"<-"                { return makeToken(Token::ASSIGN); }
    /* keywords */
"and"               { return makeToken(Token::AND); }
"bool"              { return makeToken(Token::BOOL); }
"class"             { return makeToken(Token::CLASS); }
"do"                { return makeToken(Token::DO); }
"else"              { return makeToken(Token::ELSE); }
"extends"           { return makeToken(Token::EXTENDS); }
"false"             { return makeToken(Token::FALSE); }
"if"                { return makeToken(Token::IF); }
"in"                { return makeToken(Token::IN); }
"int32"             { return makeToken(Token::INT); }
"isnull"            { return makeToken(Token::ISNULL); }
"let"               { return makeToken(Token::LET); }
"new"               { return makeToken(Token::NEW); }
"not"               { return makeToken(Token::NOT); }
"self"              { return makeToken(Token::SELF); }
"string"            { return makeToken(Token::STRING); }
"then"              { return makeToken(Token::THEN); }
"true"              { return makeToken(Token::TRUE); }
"unit"              { return makeToken(Token::UNIT); }
"while"             { return makeToken(Token::WHILE); }
    /* literals */
{integer_literal}   { return makeToken(Token::INTEGER_LITERAL); }
    /* identifiers */
{type_identifier}   { return makeToken(Token::TYPE_IDENTIFIER); }
{object_identifier} { return makeToken(Token::OBJECT_IDENTIFIER); }
{whitespace}        

\"                  { 
    BEGIN(string); 
    literalStringStream << "\"";
    yymore();
    literalStringStream.str("");
    }

<string>{regular_char}   { literalStringStream << yytext;}
<string>"\\"\n               { BEGIN(backslash); }
<string>{escaped_char}             {
        switch (yytext[1])
        {
            case 'b':
                literalStringStream << "\\x08";
                break;
            case 't':
                literalStringStream << "\\x09";
                break;
            case 'n':
                literalStringStream << "\\x0a";
                break;
            case 'r':
                literalStringStream << "\\x0d";
                break;
            case 'x':
                literalStringStream << "\\x" << yytext[2] << yytext[3];
                break;
            default:
                literalStringStream << yytext;
                break;
        }
}
<string>\"              {
        literalStringStream << "\"\0";
        yytext -= literalStringStream.str().length();
        
        yyleng = literalStringStream.str().length();
        
        for (int i = 0; i < literalStringStream.str().length(); i++)
        {
            yytext[i] = literalStringStream.str()[i];
        }
        BEGIN(INITIAL);
        return makeToken(Token::STRING_LITERAL); 
    }

<backslash>{letter}         {  yymore(); BEGIN(string); }
<backslash>{whitespace}

    /* comments */
%%

int makeToken(Token token)
{
    return static_cast<int>(token);
}