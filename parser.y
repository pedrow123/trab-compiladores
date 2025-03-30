%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();
void yyerror(const char *s);
%}

%token PROGRAM ID PONTO_FINAL VAR INTEIRO REAL FUNCTION PROCEDURE
%token ABRE_PARENTESES FECHA_PARENTESES PONTO_VIRGULA DOIS_PONTOS
%token BEGIN_TOKEN END IF THEN ELSE WHILE DO OPERADOR_ATRIBUICAO
%token OPERADOR_RELACIONAL MAIS MENOS OR OPERADOR_MULTIPLICATIVO NUM

%%

PROGRAMA: PROGRAM ID ABRE_PARENTESES LISTA_DE_IDENTIFICADORES FECHA_PARENTESES PONTO_VIRGULA
          DECLARACOES DECLARACOES_DE_SUBPROGRAMAS ENUNCIADO_COMPOSTO PONTO_FINAL
          { printf("Programa válido!\n"); }
        ;

LISTA_DE_IDENTIFICADORES: ID
                        | LISTA_DE_IDENTIFICADORES ',' ID
                        ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Erro sintático: %s\n", s);
}

int main() {
    yyparse();
    return 0;
}
