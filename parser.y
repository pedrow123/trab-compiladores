%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabela_simbolos.h"
#include "llvm_lib.h"
#include "compilador.h"

int yylex();
extern FILE *yyin;
extern int yylineno;
FILE *log_file, *out_file;

tabela_simbolos_t* tab_simbolos = NULL;
int escopo_atual = 0;
int variaveis_num = 0;
int temp_count = 0;

char* gera_temp() {
    char* nome = malloc(10);
    sprintf(nome, "t%d", temp_count++);
    return nome;
}

%}

%union {
    struct lista_simbolo* lista_s;
    char *str;
    char* tipo;
}

%token <str> ID
%token <str> NUM
%token OPERADOR_MULTIPLICATIVO OR MENOS MAIS OPERADOR_RELACIONAL 
%token OPERADOR_ATRIBUICAO DO WHILE ELSE THEN IF END BEGIN_TOKEN
%token DOIS_PONTOS PONTO_VIRGULA FECHA_PARENTESES ABRE_PARENTESES
%token FUNCTION PROCEDURE REAL INTEIRO VAR PONTO_FINAL PROGRAM EOL VIRGULA

%type <lista_s> LISTA_DE_IDENTIFICADORES LISTA_DE_PARAMETROS
%type <lista_s> FUNCTION PROCEDURE 
%type <str> FATOR EXPRESSAO EXPRESSAO_SIMPLES TERMO VARIAVEL
%type <tipo> TIPO

%%

PROGRAMA: PROGRAM ID ABRE_PARENTESES LISTA_DE_IDENTIFICADORES FECHA_PARENTESES PONTO_VIRGULA
        DECLARACOES {cria_globais(tab_simbolos, out_file); imprime_ts(log_file, tab_simbolos);}
        DECLARACOES_DE_SUBPROGRAMAS {imprime_ts(log_file, tab_simbolos);}
        {destroi_tabela(tab_simbolos);}
        ;

LISTA_DE_IDENTIFICADORES: ID {$$ = insere_lista_simbolo(NULL, cria_simbolo($1, "variavel", escopo_atual));}
                        | LISTA_DE_IDENTIFICADORES VIRGULA ID {$$ = insere_lista_simbolo($1, cria_simbolo($3, "variavel", escopo_atual));}
                        ;

DECLARACOES: DECLARACOES VAR LISTA_DE_IDENTIFICADORES DOIS_PONTOS TIPO PONTO_VIRGULA {atualiza_tipo_simbolos($3, $5); tab_simbolos = insere_simbolos_ts(tab_simbolos, $3); }
           | /* empty */ 
           ;

TIPO: INTEIRO {$$ = "INTEIRO";}
    | REAL  {$$ = "REAL";}
    ;

DECLARACOES_DE_SUBPROGRAMAS: DECLARACOES_DE_SUBPROGRAMAS DECLARACAO_DE_SUBPROGRAMA PONTO_VIRGULA {imprime_ts(log_file, tab_simbolos); tab_simbolos = destroi_var_locais(tab_simbolos);}
                           | /* empty */
                           ;

DECLARACAO_DE_SUBPROGRAMA: CABECALHO_DE_SUBPROGRAMA DECLARACOES {cria_func(out_file, tab_simbolos);} ENUNCIADO_COMPOSTO {escopo_atual--;}
                         ;

CABECALHO_DE_SUBPROGRAMA: FUNCTION ID
                        {$1 = insere_lista_simbolo(NULL, cria_simbolo($2, "funcao", escopo_atual)); escopo_atual++;
                        }
                         ARGUMENTOS DOIS_PONTOS TIPO {atualiza_tipo_simbolos($1, $6); tab_simbolos = insere_simbolos_ts(tab_simbolos, $1);} PONTO_VIRGULA
                        | PROCEDURE ID
                        {$1 = insere_lista_simbolo(NULL, cria_simbolo($2, "procedure", escopo_atual)); tab_simbolos = insere_simbolos_ts(tab_simbolos, $1);}
                        ARGUMENTOS PONTO_VIRGULA 
                        ;

ARGUMENTOS: ABRE_PARENTESES LISTA_DE_PARAMETROS FECHA_PARENTESES
          | /* empty */
          ;

LISTA_DE_PARAMETROS: LISTA_DE_IDENTIFICADORES DOIS_PONTOS TIPO 
                    {atualiza_tipo_simbolos($1, $3); atualiza_tipo_novo($1, "parametro"); tab_simbolos = insere_simbolos_ts(tab_simbolos, $1);}
                   | VAR LISTA_DE_IDENTIFICADORES DOIS_PONTOS TIPO
                   {atualiza_tipo_simbolos($2, $4); atualiza_tipo_novo($2, "ponteiro"); tab_simbolos = insere_simbolos_ts(tab_simbolos, $2);} 
                   | LISTA_DE_PARAMETROS PONTO_VIRGULA LISTA_DE_IDENTIFICADORES DOIS_PONTOS TIPO
                   {atualiza_tipo_simbolos($3, $5); atualiza_tipo_novo($3, "parametro"); tab_simbolos = insere_simbolos_ts(tab_simbolos, $3);}
                   | LISTA_DE_PARAMETROS PONTO_VIRGULA VAR LISTA_DE_IDENTIFICADORES DOIS_PONTOS TIPO
                   {atualiza_tipo_simbolos($4, $6); atualiza_tipo_novo($4, "ponteiro"); tab_simbolos = insere_simbolos_ts(tab_simbolos, $4);}
                   ;

ENUNCIADO_COMPOSTO: BEGIN_TOKEN ENUNCIADOS_OPCIONAIS END
                  ;

ENUNCIADOS_OPCIONAIS: LISTA_DE_ENUNCIADOS
                    | /* empty */
                    ;

LISTA_DE_ENUNCIADOS: ENUNCIADO
                   | LISTA_DE_ENUNCIADOS PONTO_VIRGULA ENUNCIADO
                   ;

ENUNCIADO: VARIAVEL OPERADOR_ATRIBUICAO EXPRESSAO
        {
            // $1: nome da variável (ex: "tes")
            // $3: nome do temporário com o valor (ex: "%t0")
            fprintf(out_file, "store i32 %s, ptr %%%s\n", $3, $1);
        }
         | CHAMADA_DE_PROCEDIMENTO
         | ENUNCIADO_COMPOSTO
         | IF EXPRESSAO THEN ENUNCIADO ELSE ENUNCIADO
         | WHILE EXPRESSAO DO ENUNCIADO 
         ;

VARIAVEL: ID { $$ = $1; }
        ;

CHAMADA_DE_PROCEDIMENTO: ID
                    | ID ABRE_PARENTESES LISTA_DE_EXPRESSOES FECHA_PARENTESES
                    ;

LISTA_DE_EXPRESSOES: EXPRESSAO
                   | LISTA_DE_EXPRESSOES VIRGULA EXPRESSAO
                   ;

EXPRESSAO: EXPRESSAO_SIMPLES
         | EXPRESSAO_SIMPLES OPERADOR_RELACIONAL EXPRESSAO_SIMPLES
         ;

EXPRESSAO_SIMPLES: TERMO
                 | SINAL TERMO  {
                    $$ = $2; // ignora o sinal por enquanto
                } 
                 | EXPRESSAO_SIMPLES MAIS EXPRESSAO_SIMPLES 
                 | EXPRESSAO_SIMPLES MENOS EXPRESSAO_SIMPLES 
                 | EXPRESSAO_SIMPLES OR EXPRESSAO_SIMPLES 
                 ;

TERMO: FATOR
     | TERMO OPERADOR_MULTIPLICATIVO FATOR
     ;

FATOR: ID {
        simbolo_t* s = busca_simbolo(tab_simbolos, $1);
        char* temp = gera_temp();
        fprintf(out_file, "%%%s = load %s, ptr %%%s\n", temp, converte_tipo(s->tipo), $1);
        $$ = strdup(temp);
    }
     | ID ABRE_PARENTESES LISTA_DE_EXPRESSOES FECHA_PARENTESES
     | NUM {
        char* temp = gera_temp();
        fprintf(out_file, "%%%s = add i32 0, %s\n", temp, $1);  // constante vira temporário
        $$ = strdup(temp);
    }
     | ABRE_PARENTESES EXPRESSAO FECHA_PARENTESES {
        $$ = $2;
    }
     ;

SINAL: MAIS
     | MENOS 
     ;
%%


int main(int argc, char ** argv) {
    log_file = fopen ("compilador.log", "w");
    out_file = fopen ("output.ll", "w");
    if (argc == 2) {
        yyin = fopen(argv[1], "r");
        yylineno=1;
        yyparse();
    } else if (argc == 1) {
        yyparse();
    }    
    fprintf(log_file, "Finalizando compilacao\n");
    fclose(out_file);
    fclose(log_file);
    return 0;
}


int yyerror(const char *s) {
  fprintf(stderr, "Erro na linha %d: %s\n", yylineno,s);
  exit(1);
  //return 0;
}