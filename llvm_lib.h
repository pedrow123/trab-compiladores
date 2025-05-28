#ifndef LLVM_LIB_H
#define LLVM_LIB_H

#include <stdlib.h>
#include <stdio.h>
#include "tabela_simbolos.h"

void cria_func(FILE* fp, tabela_simbolos_t* ts_original);
char *converte_tipo (char* tipo);
tabela_simbolos_t* emite_param (FILE* fp, tabela_simbolos_t* nodo);
void alloca_variaveis_locais(FILE* fp, tabela_simbolos_t* ts_fim);

#endif