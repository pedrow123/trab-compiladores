%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();
void yyerror(const char *s);
extern int yylineno;
%}

%union {
    int inteiro;
    double real;
    char *str;
}

%token <str> ID
%token NUM OPERADOR_MULTIPLICATIVO OR MENOS MAIS OPERADOR_RELACIONAL 
%token OPERADOR_ATRIBUICAO DO WHILE ELSE THEN IF END BEGIN_TOKEN
%token DOIS_PONTOS PONTO_VIRGULA FECHA_PARENTESES ABRE_PARENTESES
%token PROCEDURE FUNCTION REAL INTEIRO VAR PONTO_FINAL PROGRAM EOL VIRGULA

%type <str> LISTA_DE_IDENTIFICADORES 
%type <str> TIPO

%%

PROGRAMA: PROGRAM ID PONTO_VIRGULA
          DECLARACOES
          { printf("Programa válido!\n"); }
        ;

LISTA_DE_IDENTIFICADORES: ID
                        | LISTA_DE_IDENTIFICADORES VIRGULA ID
                        ;

DECLARACOES: DECLARACOES VAR LISTA_DE_IDENTIFICADORES DOIS_PONTOS TIPO PONTO_VIRGULA 
           | /* empty */ 
           ;

TIPO: INTEIRO {$$ = "INTEIRO";}
    | REAL  {$$ = "REAL";}
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Erro: %s na linha: %d\n", s, yylineno);
}

int main() {
    yyparse();
    return 0;
}
