%{
    /* Includes */
    #include <string>
    #include <iostream>
    #include <iomanip>
    #include <sstream>
    #include <stack>
    #include "parser.hpp"
    #include "driver.hpp"
%}

%option noyywrap nounput noinput batch

%{
    using namespace std;
    using namespace VSOP;

    
    Parser::symbol_type make_INTEGER_LITERAL(const string &s, const location &loc);

    static void print_error(const position &pos, const string &m);

    #define YY_USER_ACTION  loc.columns(yyleng);

    stringstream literalStringStream;
    int nestedComments = 0;

    stack<location> commentStack;
    location loc;
    location strLoc;
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
regular_char        [^"\n\\]

%x string_literal
%x string_line_feed
%x comment
%x backslash
%%
%{
    loc.step();
%}


    /* Operators */
"{"                 { return Parser::make_LBRACE(loc); }
"}"                 { return Parser::make_RBRACE(loc); }
"("                 { return Parser::make_LPAR(loc); }
")"                 { return Parser::make_RPAR(loc); }
":"                 { return Parser::make_COLON(loc); }
";"                 { return Parser::make_SEMICOLON(loc); }
","                 { return Parser::make_COMMA(loc); }
"+"                 { return Parser::make_PLUS(loc); }
"-"                 { return Parser::make_MINUS(loc); }
"*"                 { return Parser::make_TIMES(loc); }
"/"                 { return Parser::make_DIV(loc); }
"^"                 { return Parser::make_POW(loc); }
"."                 { return Parser::make_DOT(loc); }
"="                 { return Parser::make_EQUAL(loc); }
"<"                 { return Parser::make_LOWER(loc); }
"<="                { return Parser::make_LOWER_EQUAL(loc); }
"<-"                { return Parser::make_ASSIGN(loc); }
    /* keywords */
"and"               { return Parser::make_AND(loc); }
"bool"              { return Parser::make_BOOL(loc); }
"class"             { return Parser::make_CLASS(loc); }
"do"                { return Parser::make_DO(loc); }
"else"              { return Parser::make_ELSE(loc); }
"extends"           { return Parser::make_EXTENDS(loc); }
"false"             { return Parser::make_FALSE(loc); }
"if"                { return Parser::make_IF(loc); }
"in"                { return Parser::make_IN(loc); }
"int32"             { return Parser::make_INT32(loc); }
"isnull"            { return Parser::make_ISNULL(loc); }	
"let"               { return Parser::make_LET(loc); }
"new"               { return Parser::make_NEW(loc); }
"not"               { return Parser::make_NOT(loc); }
"self"              { return Parser::make_SELF(loc); }
"string"            { return Parser::make_STRING(loc); }
"then"              { return Parser::make_THEN(loc); }
"true"              { return Parser::make_TRUE(loc); }
"unit"              { return Parser::make_UNIT(loc); }
"while"             { return Parser::make_WHILE(loc); }
    /* literals */
{integer_literal}   { return make_INTEGER_LITERAL(yytext, loc); }
    /* identifiers */
{type_identifier}   { return Parser::make_TYPE_IDENTIFIER(yytext, loc); }
{object_identifier} { return Parser::make_OBJECT_IDENTIFIER(yytext, loc); }

    /* comments */
{lf}                { loc.lines(); loc.step(); }
{whitespace}        { loc.step(); }
{invalid_int_literal} { 
        literalStringStream << yytext << " is not a valid integer literal";
        print_error(loc.begin, literalStringStream.str());
        literalStringStream.str("");
        return Parser::make_YYerror(loc);
    }

"//"[^\n]*          {  }

\"                  {
    BEGIN(string_literal);
    literalStringStream.str("");
    literalStringStream << yytext;
    strLoc = loc;
    loc.step();
    }

"(*"               { BEGIN(comment); 
                        commentStack.push(loc);
                        loc.step();
                    }
<comment>"*)"      { 
                        loc.step();
                        if(nestedComments == 0) 
                        {
                            BEGIN(INITIAL);
                        } else {
                            nestedComments--;
                            commentStack.pop();
                        }
                    }
<comment>"(*"       {
                        nestedComments++; 
                        commentStack.push(loc);
                        loc.step();
                    }
<comment>{lf}        { loc.lines(); loc.step(); }
<comment>.         { loc.step(); }
<comment><<EOF>>   { 
    BEGIN(INITIAL);
    location commLoc = commentStack.top();
    print_error(commLoc.begin, "Unterminated comment");
    return Parser::make_YYerror(loc);
} 



<string_literal>{regular_char}*   { literalStringStream << yytext; loc.step(); }

<string_literal>\\                          { BEGIN(backslash); }
<backslash>b                        { literalStringStream << "\\x08"; BEGIN(string_literal); loc.step(); }
<backslash>t                        { literalStringStream << "\\x09"; BEGIN(string_literal); loc.step(); }
<backslash>n                        { literalStringStream << "\\x0a"; BEGIN(string_literal); loc.step(); }
<backslash>r                        { literalStringStream << "\\x0d"; BEGIN(string_literal); loc.step(); }
<backslash>x{hex_digit}{2}          { literalStringStream << "\\" << yytext; BEGIN(string_literal); loc.step(); }
<backslash>\"                       { literalStringStream << "\\x22"; BEGIN(string_literal); loc.step(); }
<backslash>\\                       { literalStringStream << "\\x5c"; BEGIN(string_literal); loc.step(); }
<backslash>.                        { 
        literalStringStream << yytext; 
        BEGIN(string_literal);
        print_error(loc.begin, "invalid escape sequence");
        loc.step();
        return Parser::make_YYerror(loc);
    }
<backslash>\n                       { 
        loc.lines(); loc.step();
        BEGIN(string_line_feed); 
    }
<backslash><<EOF>>                  { 
        BEGIN(INITIAL);
        print_error(strLoc.begin, "Unterminated string literal");
        return Parser::make_YYerror(loc);
    }

<string_literal>\"              {
        literalStringStream << "\"";
        loc.step();
        BEGIN(INITIAL);
        return Parser::make_STRING_LITERAL(literalStringStream.str(), strLoc); 
    }
<string_literal>{lf}            {
        BEGIN(INITIAL);
        print_error(loc.begin, "character '\\n' is illegal in this context.");
        loc.lines();
        loc.step();
        return Parser::make_YYerror(loc);
    }

<string_literal><<EOF>>        {
        BEGIN(INITIAL);
        print_error(strLoc.begin, "Unterminated string literal");
        return Parser::make_YYerror(strLoc);
    }

<string_line_feed>[^" "|\t]         { 
        literalStringStream << yytext; 
        loc.step();
        BEGIN(string_literal); 
    }
    
<string_line_feed>(" "|{tab})*           { loc.step(); }

.                   {  
                        print_error(loc.begin, "Invalid character"); 
                        return Parser::make_YYerror(loc); 
                    }

<<EOF>>     {return Parser::make_YYEOF(loc);}
    /* comments */
%%

Parser::symbol_type make_INTEGER_LITERAL(const string &s,
                                const location& loc)
{
    int n;
    if(s.substr(0, 2) == "0x")
        n = stoi(s, 0, 16);
    else
        n = stoi(s);

    return Parser::make_INTEGER_LITERAL(n, loc);
}

static void print_error(const position& pos, const string& m)
{
    cerr << *(pos.filename) << ":"
         << pos.line << ":"
         << pos.column << ":"
         << " lexical error: "
         << m
         << endl;
}

void Driver::scan_begin() 
{
    loc.initialize(&source_file);

    if (source_file.empty() || source_file == "-")
        yyin = stdin;
    else if (!(yyin = fopen(source_file.c_str(), "r")))
    {
        cerr << "cannot open " << source_file << ": " << strerror(errno) << '\n';
        exit(EXIT_FAILURE);
    }
}

void Driver::scan_end()
{
    fclose(yyin);
}
