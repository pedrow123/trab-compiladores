%{
#include "parser.tab.h" // Inclui os tokens gerados pelo Bison
%}

%%

"program"      return PROGRAM;
"var"          return VAR;
"integer"      return INTEIRO;
"real"         return REAL;
"function"     return FUNCTION;
"procedure"    return PROCEDURE;
"begin"        return BEGIN_TOKEN;
"end"          return END;
"if"           return IF;
"then"         return THEN;
"else"         return ELSE;
"while"        return WHILE;
"do"           return DO;
":="           return OPERADOR_ATRIBUICAO;
[0-9]+        { yylval.num = atoi(yytext); return NUM; }
[a-zA-Z][a-zA-Z0-9]*  { yylval.str = strdup(yytext); return ID; }

[ \t\n]+     ; // Ignora espaços e quebras de linha
.            return yytext[0]; // Qualquer outro caractere é retornado diretamente

%%

int yywrap() { return 1; }
