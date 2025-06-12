#ifndef LLVM_LIB_H
#define LLVM_LIB_H

#include <stdlib.h>
#include <stdio.h>
#include "tabela_simbolos.h"

void cria_func(FILE* fp, tabela_simbolos_t* ts_original);
char *converte_tipo (char* tipo);
tabela_simbolos_t* emite_param (FILE* fp, tabela_simbolos_t* nodo);
void alloca_variaveis_locais(FILE* fp, tabela_simbolos_t* ts_fim);
void ret_funcao(int temp_id, tabela_simbolos_t* ts);
void cria_if(FILE* fp, exp_t* exp, int if_count);
void cria_fim_then(FILE* fp, int if_count);
void cria_fim_else(FILE* fp, int if_count);
// void cria_chamada_funcao(FILE* fp, exp_t* parametros, exp_t* func, tabela_simbolos_t* ts, int temp_count);
void cria_chamada_funcao(FILE* fp, exp_t* argumentos_passados, exp_t* func, simbolo_t* simb_func, int* p_temp_count);

#endif