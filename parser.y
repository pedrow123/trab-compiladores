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

int dentro_de_funcao = 0;

int if_count = 0;
%}

%union {
    struct lista_simbolo* lista_s;
    char* str;
    char* tipo;
    struct exp* exp;
    int num;
}

%token <str> ID
%token <str> OPERADOR_RELACIONAL 
%token <str> NUM
%token <str> OPERADOR_MULTIPLICATIVO OR MENOS MAIS 
%token <num> IF WHILE
%token OPERADOR_ATRIBUICAO DO ELSE THEN END BEGIN_TOKEN
%token DOIS_PONTOS PONTO_VIRGULA FECHA_PARENTESES ABRE_PARENTESES
%token FUNCTION PROCEDURE REAL INTEIRO VAR PONTO_FINAL PROGRAM EOL VIRGULA

%type <lista_s> LISTA_DE_IDENTIFICADORES LISTA_DE_PARAMETROS
%type <lista_s> FUNCTION PROCEDURE 
%type <str> VARIAVEL
%type <exp> FATOR
%type <exp> TERMO
%type <exp> LISTA_DE_EXPRESSOES
%type <exp> EXPRESSAO
%type <exp> EXPRESSAO_SIMPLES
%type <tipo> TIPO

%left '+' '-'
%left '*' '/'

%%

PROGRAMA: PROGRAM ID ABRE_PARENTESES LISTA_DE_IDENTIFICADORES FECHA_PARENTESES PONTO_VIRGULA
        DECLARACOES {cria_globais(tab_simbolos, out_file); imprime_ts(log_file, tab_simbolos);}
        DECLARACOES_DE_SUBPROGRAMAS {imprime_ts(log_file, tab_simbolos);
        fprintf(out_file, "\n\ndefine i32 @main(){\nentry:\n");
        }
        ENUNCIADO_COMPOSTO 
        PONTO_FINAL {fprintf(out_file, "ret i32 0\n}");
        destroi_tabela(tab_simbolos);}
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

DECLARACAO_DE_SUBPROGRAMA: CABECALHO_DE_SUBPROGRAMA DECLARACOES {cria_func(out_file, tab_simbolos);} ENUNCIADO_COMPOSTO 
    {
        if (dentro_de_funcao) {
            int temp_id = temp_count++;
            ret_funcao(temp_id, tab_simbolos);
            dentro_de_funcao = 0;
        }
        fprintf(out_file, "}"); 
        escopo_atual--;
    }
                         ;

CABECALHO_DE_SUBPROGRAMA: FUNCTION ID
                        {
                            $1 = insere_lista_simbolo(NULL, cria_simbolo($2, "funcao", escopo_atual)); 
                            escopo_atual++;
                            simbolo_t* retorno = cria_simbolo($2, "retorno", escopo_atual);
                            $1 = insere_lista_simbolo($1, retorno);

                            dentro_de_funcao = 1;
                        }
                         ARGUMENTOS DOIS_PONTOS TIPO {
                            atualiza_tipo_simbolos($1, $6); 
                            tab_simbolos = insere_simbolos_ts(tab_simbolos, $1);
                        } 
                        PONTO_VIRGULA
                        | PROCEDURE ID
                        {$1 = insere_lista_simbolo(NULL, cria_simbolo($2, "procedure", escopo_atual)); escopo_atual++;}
                        ARGUMENTOS {tab_simbolos = insere_simbolos_ts(tab_simbolos, $1);} PONTO_VIRGULA 
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

ENUNCIADO: VARIAVEL OPERADOR_ATRIBUICAO EXPRESSAO {
            if (!strcmp($3->tipo_llvm, "i32")) {
                fprintf(out_file, "store i32 %%%d, ptr %%%s\n", $3->id_temporario, $1);
            } else if (!strcmp($3->tipo_llvm, "float")) {
                fprintf(out_file, "store float %%%d, ptr %%%s\n", $3->id_temporario, $1);
            } else {
                fprintf(stderr, "Tipo LLVM não suportado na atribuição: %s\n", $3->tipo_llvm);
                exit(1);
            }
        }
         | CHAMADA_DE_PROCEDIMENTO
         | ENUNCIADO_COMPOSTO
         | IF EXPRESSAO {
            if_count++;
            cria_if(out_file, $2, if_count);
            $1 = if_count;
        }
         THEN ENUNCIADO {cria_fim_then(out_file, $1);} ELSE ENUNCIADO {cria_fim_else(out_file, $1);}
         | WHILE EXPRESSAO DO ENUNCIADO 
         ;

VARIAVEL: ID 
        ;

CHAMADA_DE_PROCEDIMENTO: ID
                    | ID ABRE_PARENTESES LISTA_DE_EXPRESSOES FECHA_PARENTESES
                    ;

LISTA_DE_EXPRESSOES: EXPRESSAO {$$ = cria_parametros_funcao(NULL, $1);}
                   | LISTA_DE_EXPRESSOES VIRGULA EXPRESSAO {$$ = cria_parametros_funcao($1, $3);}
                   ;

EXPRESSAO: EXPRESSAO_SIMPLES {$$ = $1;}
         | EXPRESSAO_SIMPLES OPERADOR_RELACIONAL EXPRESSAO_SIMPLES { $$ = cria_expressao_binaria(out_file, $1, $3, $2, &temp_count); temp_count++;}
         ;

EXPRESSAO_SIMPLES: TERMO { $$ = $1; }
                 | SINAL TERMO  {
                    $$ = $2; // ignora o sinal por enquanto
                } 
                 | EXPRESSAO_SIMPLES MAIS EXPRESSAO_SIMPLES {
                     $$ = cria_expressao_binaria(out_file, $1, $3, "+", &temp_count);
                 }
                 | EXPRESSAO_SIMPLES MENOS EXPRESSAO_SIMPLES {
                     $$ = cria_expressao_binaria(out_file, $1, $3, "-", &temp_count);
                 }
                 | EXPRESSAO_SIMPLES OR EXPRESSAO_SIMPLES 
                 ;

TERMO: FATOR
     | TERMO OPERADOR_MULTIPLICATIVO FATOR {
         $$ = cria_expressao_binaria(out_file, $1, $3, "*", &temp_count);
     }
     ;

FATOR:ID {
        // imprime_tabela_debug(tab_simbolos); 
        if (tab_simbolos == NULL) {
            fprintf(stderr, "Erro interno: tabela de símbolos não inicializada\n");
            exit(1);
        }
        simbolo_t* s = busca_simbolo(tab_simbolos, $1);
        if (s == NULL) {
            char erro[256];
            sprintf(erro, "variável '%s' não declarada", $1);
            yyerror(erro);
        }
        if(strcmp("variavel", s->tipo_simb) == 0 || strcmp("parametro", s->tipo_simb) == 0 || strcmp("ponteiro", s->tipo_simb) == 0){

            exp_t* e = malloc(sizeof(exp_t));
            e->nome = strdup($1);
            e->prox = NULL;
            e->tipo = "variavel";
            e->tipo_llvm = converte_tipo(s->tipo);
            e->id_temporario = temp_count++;
            fprintf(out_file, "%%%d = load %s, ptr %%%s\n", e->id_temporario, e->tipo_llvm, $1);
            $$ = e;
        } else {
            // CORREÇÃO: Tratar outros casos ou lançar erro
            // Se um ID de função puder ser usado como uma expressão, trate aqui.
            // Por enquanto, vamos lançar um erro para encontrar o problema.
            char erro[256];
            sprintf(erro, "uso inválido do identificador '%s' como expressão", $1);
            yyerror(erro);
            // Ou, se for um erro silencioso, garanta que $$ seja nulo
            // $$ = NULL; 
        }
    }
     | ID ABRE_PARENTESES LISTA_DE_EXPRESSOES FECHA_PARENTESES {
        simbolo_t* s = busca_simbolo(tab_simbolos, $1);
        if (s == NULL) {
            char erro[256];
            sprintf(erro, "variável '%s' não declarada", $1);
            yyerror(erro);
        }
        exp_t* e = malloc(sizeof(exp_t));
        e->nome = strdup($1);
        e->prox = NULL;
        e->tipo = "funcao";
        e->tipo_llvm = converte_tipo(s->tipo);
        e->id_temporario = temp_count++;
        imprime_tabela_debug(tab_simbolos);
        cria_chamada_funcao(out_file, $3, e, tab_simbolos, temp_count);
        // fprintf(out_file, "%%%d = load %s, ptr %%%s\n", e->id_temporario, e->tipo_llvm, $1);
        
        
        $$ = e;
     }
     | NUM {
        exp_t* e = malloc(sizeof(exp_t));

        // Detecta se $1 contém ponto decimal → float
        if (strchr($1, '.')) {
            e->tipo = strdup("numero");
            e->tipo_llvm = strdup("float");
            e->nome = strdup($1);
            e->id_temporario = temp_count++;
            fprintf(out_file, "%%%d = fadd float 0.0, %s\n", e->id_temporario, $1);
        } else {
            e->tipo = strdup("numero");
            e->tipo_llvm = strdup("i32");
            e->nome = strdup($1);
            e->id_temporario = temp_count++;
            fprintf(out_file, "%%%d = add i32 0, %s\n", e->id_temporario, $1);
        }

        $$ = e;
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