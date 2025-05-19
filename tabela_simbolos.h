#ifndef TABELA_SIMBOLOS_H
#define TABELA_SIMBOLOS_H

typedef struct simbolo {
    char nome[100];
    char tipo[100]; // integer, float
    char tipo_simb[100]; // variavel, function, procedure
    int escopo;
} simbolo_t;

typedef struct tabela_simbolo {
    simbolo_t *simb;
    struct tabela_simbolo *prox;
} tabela_simbolos_t;

typedef struct lista_simbolo {
    simbolo_t *simb;
    struct lista_simbolo *prox;
} lista_simbolo_t;

simbolo_t * cria_simbolo(char *nome, char* tipo_simb, int escopo);

lista_simbolo_t* insere_lista_simbolo(lista_simbolo_t* lista, simbolo_t* simb);

void atualiza_tipo_simbolos(lista_simbolo_t* lista, char* tipo);

void atualiza_tipo_novo(lista_simbolo_t* lista, char* tipo);

void free_lista_simbolo(lista_simbolo_t * lista);

tabela_simbolos_t * cria_novo_simbolo_ts(tabela_simbolos_t * ts, simbolo_t * simb);

tabela_simbolos_t * insere_simbolos_ts(tabela_simbolos_t * ts, lista_simbolo_t * lista);

simbolo_t * busca_simbolo(tabela_simbolos_t * ts, char *nome);

tabela_simbolos_t * destroi_tabela(tabela_simbolos_t * ts);

tabela_simbolos_t* destroi_var_locais(tabela_simbolos_t* ts);

void imprime_ts (FILE *fp, tabela_simbolos_t* ts);

void cria_globais(tabela_simbolos_t* ts, FILE* fp);

#endif