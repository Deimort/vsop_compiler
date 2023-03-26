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
    #include "AST/nodes.hpp"

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

// 
%token <int> INTEGER_LITERAL "integer-literal"
%token <std::string> STRING_LITERAL "string-literal"
%token <std::string> TYPE_IDENTIFIER "type-identifier"
%token <std::string> OBJECT_IDENTIFIER "object-identifier"

// Non-terminals
%type <std::vector<std::shared_ptr<ClassNode>>> program
%type <std::vector<std::shared_ptr<ClassNode>>> classList
%type <std::shared_ptr<ClassNode>> class
%type <std::shared_ptr<ClassBodyNode>> classBody
%type <std::shared_ptr<ClassBodyNode>> classBodyContent
%type <std::shared_ptr<FieldNode>> field
%type <std::shared_ptr<MethodNode>> method
%type <std::string> type
%type <std::shared_ptr<ExprNode>> expr
%type <std::vector<std::shared_ptr<ExprNode>>> exprList
%type <std::shared_ptr<BlockNode>> block
%type <std::shared_ptr<IfNode>> ifExpr
%type <std::shared_ptr<WhileNode>> whileExpr
%type <std::shared_ptr<LetNode>> letExpr
%type <std::shared_ptr<NewNode>> newExpr
%type <std::shared_ptr<CallNode>> callExpr
%type <std::shared_ptr<AssignNode>> assignExpr
%type <std::shared_ptr<UnOpNode>> unOpExpr
%type <std::shared_ptr<BinOpNode>> binOpExpr
%type <std::shared_ptr<LiteralNode>> literal
%type <std::shared_ptr<LiteralNode>> booleanLiteral
%type <std::vector<std::shared_ptr<ExprNode>>> args
%type <std::vector<std::shared_ptr<FormalNode>>> formals
%type <std::shared_ptr<FormalNode>> formal

// Precedence
%right "in"
%right "while" "do"
%right "then" "else"
%right "<-"
%left "and"
%right "not"
%nonassoc "<" "<=" "="
%left "+" "-"
%left "*" "/"
%right UNARYMINUS "isnull"
%right "^"
%left "."

%%
// Grammar rules
%start program;

program: classList { $$ = $1; driver.setProgram($$); driver.result = 0; };

classList:
    class { $$ = std::vector<std::shared_ptr<ClassNode>>(); $$.push_back($1); }
    | classList class { $$ = $1; $$.push_back($2); };

class:
    CLASS TYPE_IDENTIFIER classBody { $$ = std::make_shared<ClassNode>($2, $3); }
    | CLASS TYPE_IDENTIFIER EXTENDS TYPE_IDENTIFIER classBody { $$ = std::make_shared<ClassNode>($2, $5, $4); };

classBody:
    LBRACE classBodyContent RBRACE { $$ = $2; };

classBodyContent:
    classBodyContent field { $$ = $1; $$->addField($2); }
    | classBodyContent method { $$ = $1; $$->addMethod($2); }
    | %empty { $$ = std::make_shared<ClassBodyNode>(); };

field:
    OBJECT_IDENTIFIER COLON type SEMICOLON { $$ = std::make_shared<FieldNode>($1, $3); }
    | OBJECT_IDENTIFIER COLON type ASSIGN expr SEMICOLON { $$ = std::make_shared<FieldNode>($1, $3, $5); };

method:
    OBJECT_IDENTIFIER LPAR formals RPAR COLON type block { $$ = std::make_shared<MethodNode>($1, $3, $6, $7); };

type:
    TYPE_IDENTIFIER { $$ = $1; }
    | INT32 { $$ = "int32"; }
    | BOOL { $$ = "bool"; }
    | STRING { $$ = "string"; }
    | UNIT { $$ = "unit"; };

formals:
    formal COMMA formals { $$ = $3; $$.insert($$.begin(), $1); }
    | formal { $$ = std::vector<std::shared_ptr<FormalNode>>(); $$.push_back($1); }
    | %empty { $$ = std::vector<std::shared_ptr<FormalNode>>(); };

formal:
    OBJECT_IDENTIFIER COLON type { $$ = std::make_shared<FormalNode>($1, $3); };

block:
    LBRACE exprList RBRACE { $$ = std::make_shared<BlockNode>($2); };

exprList:
    expr { $$ = std::vector<std::shared_ptr<ExprNode>>(); $$.push_back($1); }
    | expr SEMICOLON exprList { $$ = $3; $$.insert($$.begin(), $1); }

expr:
    ifExpr { $$ = $1;}
    | whileExpr { $$ = $1; }
    | letExpr { $$ = $1;}
    | assignExpr { $$ = $1;}
    | unOpExpr { $$ = $1;}
    | binOpExpr { $$ = $1;}
    | callExpr { $$ = $1;}
    | newExpr { $$ = $1;}
    | OBJECT_IDENTIFIER { $$ = std::make_shared<IdentifierNode>($1); }
    | SELF { $$ = std::make_shared<SelfNode>(); }
    | literal { $$ = $1; }
    | LPAR RPAR { $$ = std::make_shared<UnitNode>(); }
    | LPAR expr RPAR { $$ = $2; }
    | block { $$ = $1; };

args:
    expr { $$ = std::vector<std::shared_ptr<ExprNode>>(); $$.push_back($1); }
    | expr COMMA args { $$ = $3; $$.insert($$.begin(), $1); }
    | %empty { $$ = std::vector<std::shared_ptr<ExprNode>>(); };

ifExpr:
    IF expr THEN expr { $$ = std::make_shared<IfNode>($2, $4); }
    | IF expr THEN expr ELSE expr { $$ = std::make_shared<IfNode>($2, $4, $6); }

whileExpr:
    WHILE expr DO expr { $$ = std::make_shared<WhileNode>($2, $4); };

letExpr:
    LET OBJECT_IDENTIFIER COLON type IN expr { $$ = std::make_shared<LetNode>($2, $4, $6); }
    | LET OBJECT_IDENTIFIER COLON type ASSIGN expr IN expr { $$ = std::make_shared<LetNode>($2, $4, $8, $6); };

assignExpr:
    OBJECT_IDENTIFIER ASSIGN expr { $$ = std::make_shared<AssignNode>($1, $3); };

unOpExpr:
    NOT expr { $$ = std::make_shared<NotUnOpNode>($2); }
    | MINUS expr %prec UNARYMINUS { $$ = std::make_shared<MinusUnOpNode>($2); }
    | ISNULL expr { $$ = std::make_shared<IsnullUnOpNode>($2); };

binOpExpr:
    expr EQUAL expr { $$ = std::make_shared<EqualBinOpNode>($1, $3); }
    | expr LOWER expr { $$ = std::make_shared<LowerBinOpNode>($1, $3); }
    | expr LOWER_EQUAL expr { $$ = std::make_shared<LowerOrEqualBinOpNode>($1, $3); }
    | expr PLUS expr { $$ = std::make_shared<AddBinOpNode>($1, $3); }
    | expr MINUS expr { $$ = std::make_shared<MinusBinOpNode>($1, $3); }
    | expr TIMES expr { $$ = std::make_shared<MulBinOpNode>($1, $3); }
    | expr DIV expr { $$ = std::make_shared<DivBinOpNode>($1, $3); }
    | expr POW expr { $$ = std::make_shared<PowBinOpNode>($1, $3); }
    | expr AND expr { $$ = std::make_shared<AndBinOpNode>($1, $3); };

callExpr:
    OBJECT_IDENTIFIER LPAR args RPAR { $$ = std::make_shared<CallNode>($1, $3); }
    | expr DOT OBJECT_IDENTIFIER LPAR args RPAR { $$ = std::make_shared<CallNode>($3, $5, $1); };

newExpr:
    NEW TYPE_IDENTIFIER { $$ = std::make_shared<NewNode>($2);};

literal:
    INTEGER_LITERAL { $$ = std::make_shared<LiteralNode>(std::to_string($1)); }
    | STRING_LITERAL { $$ = std::make_shared<LiteralNode>($1); }
    | booleanLiteral { $$ = $1; };

booleanLiteral:
    TRUE { $$ = std::make_shared<LiteralNode>("true"); }
    | FALSE { $$ = std::make_shared<LiteralNode>("false"); };

%%

void VSOP::Parser::error(const location_type& l, const std::string& m)
{
    driver.result = 1;
    const position &pos = l.begin;

    cerr << *(pos.filename) << ":"
         << pos.line << ":" 
         << pos.column << ": "
         << m
         << endl;
}
