%option yylineno

%{
#include "parser.tab.h"

char err_buffer[500];
%}

DIGITOS [0-9]+
NUM {DIGITOS}(\.{DIGITOS})?([Ee][+-]?{DIGITOS})?
ID [a-zA-Z][a-zA-Z1-9]*

%%

{NUM} { return NUM; }
"*"|"/"|"div"|"mod"|"and" { return OPERADOR_MULTIPLICATIVO; }
"or" { return OR; }
"-" { return MENOS; }
"+" { return MAIS; }
"="|"<>"|">"|">="|"<"|"<=" { return OPERADOR_RELACIONAL; }
":=" { return OPERADOR_ATRIBUICAO; }
"do" { printf("TOKEN: do\n"); return DO; }
"while" { printf("TOKEN: while\n"); return WHILE; }
"else" { return ELSE; }
"then" { return THEN; }
"if" { printf("TOKEN: if\n"); return IF; }
"end" { return END; }
"begin" { return BEGIN_TOKEN; }
":" { return DOIS_PONTOS; }
"program" { printf("TOKEN: programa\n");return PROGRAM; }
";" { printf("TOKEN: pv\n"); return PONTO_VIRGULA; }
"var" { printf("TOKEN: var\n"); return VAR; }
")" { return FECHA_PARENTESES; }
"(" { return ABRE_PARENTESES; }
"procedure" { printf("TOKEN: procedure\n"); return PROCEDURE; }
"function" { return FUNCTION; }
"real" { return REAL; }
"integer" { printf("TOKEN: INTEIRO\n"); return INTEIRO; }
"." { return PONTO_FINAL; }
"," { return VIRGULA; }
{ID} { 
    yylval.str = strdup(yytext);
    return ID; }

\n {  }
[ \t] {/*ignorar espacos em branco, incluindo tabs*/}

%%