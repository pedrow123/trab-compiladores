#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tabela_simbolos.h"
#include "compilador.h"

simbolo_t * cria_simbolo(char *nome, char* tipo_simb, int escopo){
    simbolo_t * novo = malloc(sizeof(simbolo_t));
    novo->escopo = escopo;
    strcpy(novo->tipo, "");
    strcpy(novo->tipo_simb, tipo_simb);
    strcpy(novo->nome, nome);
    return novo;
}

lista_simbolo_t* insere_lista_simbolo(lista_simbolo_t* lista, simbolo_t* simb){
    // insere no final
    lista_simbolo_t *aux, *novo = malloc(sizeof(lista_simbolo_t));
    novo->simb = simb;
    novo->prox = NULL;
    if(lista == NULL){
        return novo;
    }
    aux = lista;
    while(aux->prox != NULL)
        aux = aux->prox;
    aux->prox = novo;
    return lista;
}

void atualiza_tipo_simbolos(lista_simbolo_t* lista, char* tipo){
    while(lista != NULL){
        strcpy(lista->simb->tipo, tipo);
        lista = lista->prox;
    }
}

void atualiza_tipo_novo(lista_simbolo_t* lista, char* tipo){
    while(lista != NULL){
        strcpy(lista->simb->tipo_simb, tipo);
        lista = lista->prox;
    }
}

void free_lista_simbolo(lista_simbolo_t * lista){
    if(lista == NULL)
        return;
    free_lista_simbolo(lista->prox);
    free(lista);
}

tabela_simbolos_t * cria_novo_simbolo_ts(tabela_simbolos_t * ts, simbolo_t * simb){
    simbolo_t *simb_busca = busca_simbolo(ts, simb->nome);
    if(simb_busca != NULL && simb_busca->escopo == simb->escopo){
        char erro[500];
        sprintf(erro, "simbolo '%s' ja declarado antes", simb->nome);
        yyerror(erro);
    }
    tabela_simbolos_t * novo = malloc(sizeof(tabela_simbolos_t));
    novo->simb = simb;
    novo->prox = ts;
    return novo;
}
tabela_simbolos_t * insere_simbolos_ts(tabela_simbolos_t * ts, lista_simbolo_t * lista){
    lista_simbolo_t * aux = lista;
    while(aux != NULL){
        ts = cria_novo_simbolo_ts(ts, aux->simb);
        aux = aux->prox;
    }
    free_lista_simbolo(lista);
    return ts;
}

simbolo_t * busca_simbolo(tabela_simbolos_t * ts, char *nome){
    while(ts != NULL){
        if(strcmp(ts->simb->nome, nome) == 0)
            return ts->simb;
        ts = ts->prox;
    }
    return NULL;
}

tabela_simbolos_t * destroi_tabela(tabela_simbolos_t * ts){
    tabela_simbolos_t * aux;
    while(ts != NULL){
        free(ts->simb);
        aux = ts;
        ts = ts->prox;
        free(aux);
    }
    return ts;
}

tabela_simbolos_t* destroi_var_locais(tabela_simbolos_t* ts) {
    tabela_simbolos_t* atual = ts;
    tabela_simbolos_t* anterior = NULL;

    while (atual != NULL) {
        if (atual->simb->escopo == 1) {
            tabela_simbolos_t* temp = atual;
            if (anterior == NULL) {
                // Removendo o primeiro elemento da lista
                ts = atual->prox;
                atual = ts;
            } else {
                anterior->prox = atual->prox;
                atual = atual->prox;
            }
            free(temp->simb);
            free(temp);
        } else {
            anterior = atual;
            atual = atual->prox;
        }
    }

    return ts;
}

void imprime_ts (FILE *fp, tabela_simbolos_t* ts) {
    fprintf(fp, "----- TABELA DE SÍMBOLOS -----\n");
    while (ts != NULL) {
        fprintf(fp, "nome: %s, tipo simbolo: %s, tipo: %s, escopo: %d \n", ts->simb->nome, ts->simb->tipo_simb, ts->simb->tipo, ts->simb->escopo);
        ts = ts->prox;
    }
    fprintf(fp, "------------------------------\n");
}

void cria_globais(tabela_simbolos_t* ts, FILE* fp){
    while(ts != NULL){
        if(strcmp(ts->simb->tipo, "INTEIRO") == 0){
            fprintf(fp, "@%s global i32 0\n", ts->simb->nome);
        } else {
            fprintf(fp, "@%s global float 0\n", ts->simb->nome);
        }
        ts = ts->prox;
    }
}