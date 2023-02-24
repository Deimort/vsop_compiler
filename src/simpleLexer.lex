%option noyywrap

%{
    /* Operators */
    #define LBRACE 0
    #define RBRACE 1
    #define LPAR 2
    #define RPAR 3
    #define COLON 4
    #define SEMICOLON 5
    #define COMMA 6
    #define PLUS 7
    #define MINUS 8
    #define TIMES 9
    #define DIVIDE 10
    #define POW 11
    #define DOT 12
    #define EQUAL 13
    #define LOWER 14
    #define LOWER_EQUAL 15
    #define ASSIGN 16

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

%}

%%

    /* Operators */
"{"    { return LBRACE; }
"}"    { return RBRACE; }
"("    { return LPAR; }
")"    { return RPAR; }
":"    { return COLON; }
";"    { return SEMICOLON; }
","    { return COMMA; }
"+"    { return PLUS; }
"-"    { return MINUS; }
"*"    { return TIMES; }
"/"    { return DIVIDE; }
"^"    { return POW; }
"."    { return DOT; }
"="    { return EQUAL; }
"<"    { return LOWER; }
"<="   { return LOWER_EQUAL; }
"<-"    { return ASSIGN; }

%%
