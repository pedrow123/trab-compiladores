#ifndef TABELA_SIMBOLOS_H
#define TABELA_SIMBOLOS_H

typedef struct simbolo {
    char nome[100];
    char tipo[100];
    char tipo_simb[100];
    int escopo;
} simbolo_t;

typedef struct tabela_simbolo {
    simbolo_t *simb;
    tabela_simbolo_t *prox;
} tabela_simbolo_t;

typedef struct lista_simbolo {
    simbolo_t *simb;
    lista_simbolo_t *prox;
} lista_simbolo_t;

#endif