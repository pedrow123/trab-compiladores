#ifndef LLVM_LIB_H
#define LLVM_LIB_H

#include <stdlib.h>
#include <stdio.h>
#include "tabela_simbolos.h"

void cria_func(FILE* fp, tabela_simbolos_t* ts);
char *converte_tipo (char* tipo);
tabela_simbolos_t* emite_param (FILE* fp, tabela_simbolos_t* nodo);

#endif