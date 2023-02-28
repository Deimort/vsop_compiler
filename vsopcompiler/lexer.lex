
%{
    /* Includes */
    #include <string>
    #include <iostream>
    #include <iomanip>
    #include <sstream>
    #include <stack>
    #include "scanner.hpp"
    #include "tokens.hpp"
%}

%option c++ noyywrap nounput noinput batch yylineno yyclass="Scanner"

%{
    using namespace std;

    int makeToken(Token token);
    
    std::stringstream literalStringStream;
    int nestedComments = 0;
    int scLine, scColumn;
    typedef struct {
        int line;
        int column;
    } CommentPos;

    stack<CommentPos> commentStack;
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
invalid_hex         "0x"({digit}|[g-zG-Z])*
invalid_digit       {digit}+[a-zA-Z]
invalid_int_literal {invalid_hex}|{invalid_digit}
type_identifier     {uppercase_letter}({letter}|{digit}|"_")*
object_identifier   {lowercase_letter}({letter}|{digit}|"_")*
escape_sequence     [btnr"]|\\|"x"{hex_digit}{2}|"n"(" "|{tab})*
escaped_char        \\{escape_sequence}
regular_char        [^"\n\\]

%x string
%x string_line_feed
%x comment
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
{lf}                { resetColumn(); }
{whitespace}        { countColumn(); }
{invalid_int_literal} { 
        literalStringStream << "lexical error: " << yytext << " is not a valid integer literal";
        int err = makeError(literalStringStream.str(), yylineno, column);
        literalStringStream.str("");
        return err;
    }

"//"[^\n]*          {  }


"(*"               { BEGIN(comment); 
                        commentStack.push({yylineno, column});
                        countColumn();
                    }
<comment>"*)"      { 
                        countColumn();
                        if(nestedComments == 0) 
                        {
                            BEGIN(INITIAL);
                        } else {
                            nestedComments--;
                            commentStack.pop();
                        }
                    }
<comment>"(*"      { 
        nestedComments++; 
        commentStack.push({yylineno, column});
        countColumn(); 
    }
<comment>\n        { resetColumn(); }
<comment>.         { countColumn(); }
<comment><<EOF>>   { 
    BEGIN(INITIAL);
    CommentPos pos = commentStack.top();
    return makeError("lexical error: Unterminated comment", pos.line, pos.column); }

\"                  {
    literalStringStream.str("");
    BEGIN(string);
    literalStringStream << yytext;
    scLine = yylineno;
    scColumn = column;
    countColumn();
    }

<string>{regular_char}*   { literalStringStream << yytext; countColumn(); }

<string>\\                          { BEGIN(backslash); yymore(); }
<backslash>b                        { literalStringStream << "\\x08"; BEGIN(string); countColumn(); }
<backslash>t                        { literalStringStream << "\\x09"; BEGIN(string); countColumn(); }
<backslash>n                        { literalStringStream << "\\x0a"; BEGIN(string); countColumn(); }
<backslash>r                        { literalStringStream << "\\x0d"; BEGIN(string); countColumn(); }
<backslash>x{hex_digit}{2}          { literalStringStream << yytext; BEGIN(string); countColumn(); }
<backslash>\"                       { literalStringStream << "\\x22"; BEGIN(string); countColumn(); }
<backslash>\\                       { literalStringStream << "\\x5c"; BEGIN(string); countColumn(); }
<backslash>.                        { 
        literalStringStream << yytext; 
        BEGIN(string);
        return makeError("lexical error: invalid escape sequence");
        countColumn();
    }
<backslash>\n                       { 
        resetColumn();
        BEGIN(string_line_feed); 
    }
<backslash><<EOF>>                  { 
        BEGIN(INITIAL);
        return makeError("lexical error: Unterminated string literal", scLine, scColumn);
    }

<string>\"              {
        literalStringStream << "\"";
        BEGIN(INITIAL);
        return makeToken(Token::STRING_LITERAL, literalStringStream.str(), scLine, scColumn); 
    }
<string>{lf}            {
        BEGIN(INITIAL);
        yyless(0);
        int error = makeError("lexical error: character '\\n' is illegal in this context.");
        resetColumn();
        return error;
    }

<string><<EOF>>        {
        BEGIN(INITIAL);
        return makeError("lexical error: Unterminated string literal", scLine, scColumn);
    }

<string_line_feed>[^" "|\t]         { 
        literalStringStream << yytext; 
        countColumn();
        BEGIN(string); 
    }
    
<string_line_feed>(" "|{tab})*           { countColumn(); }

.                   { return makeError("lexical error: Invalid character"); }


    /* comments */
%% 