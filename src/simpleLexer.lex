
%{
    /* Includes */
    #include <string>
%}

%option noyywrap nounput noinput batch

%{
    using namespace std;
    using namespace VSOP;

    enum class Tokens : int
{
    /* Operators */
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
    LOWER_EQUAL = 128,
    ASSIGN = 129,
    /* Keywords */
};

    /* Keywords */
    #define AND 17
    #define BOOL 18
    #define CLASS 19
    #define DO 20
    #define ELSE 21
    #define EXTENDS 22
    #define FALSE 23
    #define IF 24
    #define IN 25
    #define INT 26
    #define ISNULL 27
    #define LET 28
    #define NEW 29
    #define NOT 30
    #define SELF 31
    #define STRING 32
    #define THEN 33
    #define TRUE 34
    #define UNIT 35
    #define WHILE 36

    int make_token(Tokens token);

%}

%%

    /* Operators */
"{"    { return make_token(Tokens::LBRACE); }
"}"    { return make_token(Tokens::RBRACE); }
"("    { return make_token(Tokens::LPAR); }
")"    { return make_token(Tokens::RPAR); }
":"    { return make_token(Tokens::COLON); }
";"    { return make_token(Tokens::SEMICOLON); }
","    { return make_token(Tokens::COMMA); }
"+"    { return make_token(Tokens::PLUS); }
"-"    { return make_token(Tokens::MINUS); }
"*"    { return make_token(Tokens::TIMES); }
"/"    { return make_token(Tokens::DIV); }
"^"    { return make_token(Tokens::POW); }
"."    { return make_token(Tokens::DOT); }
"="    { return make_token(Tokens::EQUAL); }
"<"    { return make_token(Tokens::LOWER); }
"<="   { return make_token(Tokens::LOWER_EQUAL); }
"<-"    { return make_token(Tokens::ASSIGN); }

%%

int make_token(Tokens token) 
{
    return static_cast<int>(token);
}