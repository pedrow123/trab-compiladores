#include "tabela_simbolos.h"
#include "compilador.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void atualiza_tipo_simbolos(lista_simbolo_t* lista, char* tipo){
    while(lista != NULL){
        strcpy(lista->simb->tipo_simb, tipo);
        lista = lista->prox;
    }
}

tabela_simbolo_t* insere_simbolos_ts(tabela_simbolo_t* ts, lista_simbolo_t* lista_simb){
    lista_simbolo_t* aux = lista_simb;
    while(aux != NULL){
        
    }
}