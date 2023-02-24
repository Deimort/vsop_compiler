%option noyywrap

%{
    int numChars = 0, numWords = 0, numLines = 0;
%}

%%

\n  { numLines++; numChars++; }
[^ \t\n]+   { numChars++; numWords++; yyleng++;}
.   { numChars++; }

%%