/* This flex/bison example is provided to you as a starting point for your
 * assignment. You are free to use its code in your project.
 *
 * This example implements a simple calculator. You can use the '-l' flag to
 * list all the tokens found in the source file, and the '-p' flag (or no flag)
 * to parse the file and to compute the result.
 *
 * Also, if you have any suggestions for improvements, please let us know.
 */

%skeleton "lalr1.cc" // -*- C++ -*-
%language "c++"
%require "3.7.5"
%locations

%defines

// Put parser inside a namespace
%define api.namespace {VSOP}

// Give the name of the parser class
%define api.parser.class {Parser}

// Force the token kind enum (used by the lexer) and the symbol kind enum
// (used by the parser) to use the same value for the tokens.
// (e.g. '+' will be represented by the same integer value in both enums.)
%define api.token.raw

// Tokens contain their type, value and location
// Also allow to use the make_TOKEN functions
%define api.token.constructor

// Allow to use C++ objects as semantic values
%define api.value.type variant

// Add some assertions.
%define parse.assert

// C++ code put inside header file
%code requires {
    #include <string>
    #include <memory>

    namespace VSOP
    {
        class Driver;
    }
}

// Add an argument to the parser constructor
%parse-param {VSOP::Driver &driver}

%code {
    
    #include "driver.hpp"

    using namespace std;
}

// Token and symbols definitions
%token
    LBRACE          "{"
    RBRACE          "}"
    LPAR            "("
    RPAR            ")"
    COLON           ":"
    SEMICOLON       ";"
    COMMA           ","
    PLUS            "+"
    MINUS           "-"
    TIMES           "*"
    DIV             "/"
    POW             "^"
    DOT             "."
    EQUAL           "="
    LOWER           "<"
    LOWER_EQUAL     "<="
    ASSIGN          "<-"
    AND             "and"
    BOOL            "bool"
    CLASS           "class"
    DO              "do"
    ELSE            "else"
    EXTENDS         "extends"
    FALSE           "false"
    IF              "if"
    IN              "in"
    INT32           "int32"
    ISNULL          "isnull"
    LET             "let"
    NEW             "new"
    NOT             "not"
    SELF            "self"
    STRING          "string"
    THEN            "then"
    TRUE            "true"
    UNIT            "unit"
    WHILE           "while"
;

%union {
    std::unique_ptr<ProgramNode> programNode;
    std::unique_ptr<ClassNode> classNode;
}

%token <int> INTEGER_LITERAL "integer-literal"
%token <std::string> STRING_LITERAL "string-literal"
%token <std::string> TYPE_IDENTIFIER "type-identifier"
%token <std::string> OBJECT_IDENTIFIER "object-identifier"

%type <programNode> program
%type <classNode> classList

// Precedence
%left "."
%right "^"
%right UNARYMINUS "isnull"
%left "*" "/"
%left "+" "-"
%nonassoc "<" "<=" "="
%right "not"
%left "and"
%right "<-"

%%
// Grammar rules
%start program;

program: classList { $$ = std::make_unique<programNode>()};

classList:
    { $$ = std::vector<classNode>(); }
    | class classList { $$ = std::move($2); $$->push_back(std::move($1)); };

class:
    CLASS TYPE_IDENTIFIER classBody
    | CLASS TYPE_IDENTIFIER EXTENDS TYPE_IDENTIFIER classBody;

classBody:
    LBRACE class-body-content RBRACE;

class-body-content:
    field
    | method
    | field class-body-content
    | method class-body-content;

field:
    OBJECT_IDENTIFIER COLON type
    | OBJECT_IDENTIFIER COLON type ASSIGN expr SEMICOLON;

method:
    OBJECT_IDENTIFIER LPAR formals RPAR COLON type block;

type:
    TYPE_IDENTIFIER
    | INT32
    | BOOL
    | STRING
    | UNIT;

formals:
    | formal COMMA formals;

formal:
    OBJECT_IDENTIFIER COLON type;

block:
    LBRACE expr-list LBRACE;


expr:
    if-expr
    | while-expr
    | let-expr
    | assign-expr
    | unop-expr
    | binop-expr
    | call-expr
    | new-expr
    | literal
    | OBJECT_IDENTIFIER
    | SELF;

expr-list:
    | expr SEMICOLON expr-list;

if-expr:
    IF expr THEN expr
    | IF expr THEN expr ELSE expr;

while-expr:
    WHILE expr DO expr;

let-expr:
    LET OBJECT_IDENTIFIER COLON type IN expr
    | LET OBJECT_IDENTIFIER COLON type ASSIGN expr IN expr;

assign-expr:
    OBJECT_IDENTIFIER ASSIGN expr;

unop-expr:
    NOT expr
    | MINUS expr
    | ISNULL expr;

binop-expr:
    expr comp-op expr
    | expr add-sub-op expr
    | expr mul-div-op expr
    | expr POW expr
    | expr AND expr;

comp-op:
    EQUAL
    | LOWER
    | LOWER_EQUAL;

add-sub-op:
    PLUS
    | MINUS;

mul-div-op:
    TIMES
    | DIV;

call-expr:
    OBJECT_IDENTIFIER LPAR expr-list RPAR
    | expr DOT OBJECT_IDENTIFIER LPAR expr-list RPAR;

new-expr:
    NEW TYPE_IDENTIFIER;

literal:
    INTEGER_LITERAL
    | STRING_LITERAL
    | boolean-literal;

boolean-literal:
    TRUE
    | FALSE;

%%

void VSOP::Parser::error(const location_type& l, const std::string& m)
{
    const position &pos = l.begin;

    cerr << *(pos.filename) << ":"
         << pos.line << ":" 
         << pos.column << ": "
         << m
         << endl;
}
