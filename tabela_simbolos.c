#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tabela_simbolos.h"
#include "compilador.h"

simbolo_t * cria_simbolo(char *nome, char* tipo_simb, int escopo){
    if (!nome || !tipo_simb) {
        fprintf(stderr, "Erro: nome ou tipo_simb nulo ao criar símbolo\n");
        exit(1);
    }
    simbolo_t * novo = malloc(sizeof(simbolo_t));
    novo->escopo = escopo;
    novo->tipo = strdup("");                // ou NULL se quiser evitar string vazia
    novo->tipo_simb = strdup(tipo_simb);    // aloca e copia a string
    novo->nome = strdup(nome);
    novo->lista_de_parametros = NULL;
    return novo;
}

lista_simbolo_t* insere_lista_simbolo(lista_simbolo_t* lista, simbolo_t* simb){
    // insere no final
    lista_simbolo_t *aux, *novo = malloc(sizeof(lista_simbolo_t));
    if(strcmp(simb->tipo_simb, "procedure") == 0){
        strcpy(simb->tipo, "VOID");
    }
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
    novo->prev = NULL;

    if (ts != NULL) {
        ts->prev = novo;
    }

    return novo;
}
tabela_simbolos_t * insere_simbolos_ts(tabela_simbolos_t * ts, lista_simbolo_t * lista){
    lista_simbolo_t * aux = lista;
    while(aux != NULL){
        // printf("%s\n", aux->simb->nome);
        ts = cria_novo_simbolo_ts(ts, aux->simb);
        aux = aux->prox;
    }
    // printf("---------------------FIM PARAMS------------------------\n");
    free_lista_simbolo(lista);
    return ts;
}

simbolo_t * busca_simbolo(tabela_simbolos_t * ts, char *nome){
    if (ts == NULL) {
        return NULL;
    }
    while(ts != NULL){
        if (ts->simb && ts->simb->nome && strcmp(ts->simb->nome, nome) == 0)
            return ts->simb;
        ts = ts->prox;
    }
    return NULL;
}

void destroi_tabela(tabela_simbolos_t* ts) {
    tabela_simbolos_t* atual = ts;
    tabela_simbolos_t* proximo = NULL;

    while (atual != NULL) {
        // 1. Guarda o ponteiro para o próximo nó ANTES de liberar o atual
        proximo = atual->prox;

        // 2. Libera o conteúdo do símbolo (de dentro para fora)
        if (atual->simb != NULL) {
            // Libera as strings que foram alocadas dinamicamente com strdup
            free(atual->simb->nome);
            free(atual->simb->tipo);
            free(atual->simb->tipo_simb);
            
            // SÓ AGORA libera a própria estrutura do símbolo
            free(atual->simb);
        }

        // 3. Libera o nó da lista
        free(atual);

        // 4. Avança para o próximo nó que foi salvo anteriormente
        atual = proximo;
    }
}

tabela_simbolos_t* destroi_var_locais(tabela_simbolos_t* ts) {
    tabela_simbolos_t* atual = ts;

    while (atual != NULL) {
        // Verifica se o escopo é local (1)
        if (atual->simb && atual->simb->escopo == 1) {
            tabela_simbolos_t* para_remover = atual;
            
            // Pega os vizinhos antes de modificar
            tabela_simbolos_t* anterior = para_remover->prev;
            tabela_simbolos_t* proximo = para_remover->prox;

            if (anterior == NULL) {
                // Estamos removendo o primeiro elemento (a cabeça da lista)
                ts = proximo; // A nova cabeça é o próximo
            } else {
                // Estamos removendo do meio ou do fim
                anterior->prox = proximo;
            }

            if (proximo != NULL) {
                // NOVO E CRUCIAL: Ajusta o ponteiro 'prev' do nó seguinte
                proximo->prev = anterior;
            }

            // Avança o 'atual' para o próximo nó ANTES de liberar a memória
            atual = proximo;

            // CORREÇÃO: Liberar os campos alocados com strdup() primeiro
            if (para_remover->simb) {
                free(para_remover->simb->nome);
                free(para_remover->simb->tipo);
                free(para_remover->simb->tipo_simb);
                free(para_remover->simb); // Agora libera a struct do símbolo
            }
            free(para_remover); // E finalmente, libera o nó da lista

        } else {
            // Se não removeu, apenas avança para o próximo
            atual = atual->prox;
        }
    }

    return ts; // Retorna a nova cabeça da lista (pode ter mudado)
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

tabela_simbolos_t* ir_para_fim(tabela_simbolos_t* ts) {
    while (ts && ts->prox != NULL)
        ts = ts->prox;
    return ts;
}

exp_t* cria_expressao_binaria(FILE* out_file, exp_t* e1, exp_t* e2, const char* operador, int* temp_count) {
    // Verifica compatibilidade de tipo
    if (strcmp(e1->tipo_llvm, e2->tipo_llvm) != 0) {
        fprintf(stderr, "Erro: operação entre tipos incompatíveis: %s e %s\n", e1->tipo_llvm, e2->tipo_llvm);
        exit(1);
    }

    char* tipo_llvm = e1->tipo_llvm;
    int id_result = (*temp_count)++;
    const char* instr = NULL;

    // Operações aritméticas
    if (strcmp(operador, "+") == 0) {
        instr = strcmp(tipo_llvm, "i32") == 0 ? "add i32" : "fadd float";
    } else if (strcmp(operador, "-") == 0) {
        instr = strcmp(tipo_llvm, "i32") == 0 ? "sub i32" : "fsub float";
    } else if (strcmp(operador, "*") == 0) {
        instr = strcmp(tipo_llvm, "i32") == 0 ? "mul i32" : "fmul float";
    } else if (strcmp(operador, "/") == 0) {
        instr = strcmp(tipo_llvm, "i32") == 0 ? "sdiv i32" : "fdiv float";
    }

    // Operações de comparação
    else if (strcmp(operador, "=") == 0) {
        instr = strcmp(tipo_llvm, "i32") == 0 ? "icmp eq"  : "fcmp oeq";
        tipo_llvm = "i1";
    } else if (strcmp(operador, "<>") == 0) {
        instr = strcmp(tipo_llvm, "i32") == 0 ? "icmp ne"  : "fcmp one";
        tipo_llvm = "i1";
    } else if (strcmp(operador, "<") == 0) {
        instr = strcmp(tipo_llvm, "i32") == 0 ? "icmp slt" : "fcmp olt";
        tipo_llvm = "i1";
    } else if (strcmp(operador, "<=") == 0) {
        instr = strcmp(tipo_llvm, "i32") == 0 ? "icmp sle" : "fcmp ole";
        tipo_llvm = "i1";
    } else if (strcmp(operador, ">") == 0) {
        instr = strcmp(tipo_llvm, "i32") == 0 ? "icmp sgt" : "fcmp ogt";
        tipo_llvm = "i1";
    } else if (strcmp(operador, ">=") == 0) {
        instr = strcmp(tipo_llvm, "i32") == 0 ? "icmp sge" : "fcmp oge";
        tipo_llvm = "i1";
    } else {
        fprintf(stderr, "Operador binário não suportado: %s\n", operador);
        exit(1);
    }

    fprintf(out_file, "%%%d = %s %%%d, %%%d\n", id_result, instr, e1->id_temporario, e2->id_temporario);

    exp_t* resultado = malloc(sizeof(exp_t));
    resultado->nome = strdup("exp");
    resultado->tipo = strdup("temp");
    resultado->id_temporario = id_result;
    resultado->tipo_llvm = tipo_llvm;
    return resultado;
}

exp_t* cria_parametros_funcao(exp_t* raiz, exp_t* nova) {
    exp_t* raiz_aux = raiz;
    if (raiz) {
        while (raiz->prox)
            raiz = raiz->prox;
        raiz->prox = nova;

        return raiz_aux;
    } else {
        return nova;
    }
}

// Função para imprimir o estado da tabela de símbolos para depuração
void imprime_tabela_debug(tabela_simbolos_t * ts) {
    printf("\n--- ESTADO DA TABELA DE SÍMBOLOS ---\n");
    tabela_simbolos_t * atual = ts;
    int i = 0;
    while (atual != NULL) {
        printf("Nó %d: Endereço do nó (ts): %p, ", i, (void*)atual);
        if (atual->simb) {
            printf("Endereço do símbolo (ts->simb): %p, ", (void*)atual->simb);
            if (atual->simb->nome) {
                printf("Nome: '%s', Escopo: %d\n", atual->simb->nome, atual->simb->escopo);
            } else {
                printf("Nome: (NULL)\n");
            }
        } else {
            printf("Símbolo (ts->simb): (NULL)\n");
        }
        atual = atual->prox;
        i++;
    }
    printf("--- FIM DO ESTADO ---\n\n");
}

void insere_parametros_funcao(tabela_simbolos_t* ts){
    tabela_simbolos_t* func = ts;
    while(func->simb->escopo == 1){
        func = func->prox;
    }
        
    int count = 0;
    tabela_simbolos_t* params[64];

    tabela_simbolos_t* aux = func->prox;  // pula o símbolo da função

    while (aux && (strcmp(aux->simb->tipo_simb, "parametro") == 0 || strcmp(aux->simb->tipo_simb, "ponteiro") == 0)) {
        params[count++] = aux;
        aux = aux->prox;
    }
    
    for(int i = count-1; i >= 0; i--){
        func->simb->lista_de_parametros = insere_lista_simbolo(
            func->simb->lista_de_parametros, 
            params[i]->simb
        );
        
    }
    printf("Lista de Parâmetros------------------------- FUNÇÃO: %s\n", func->simb->nome);
    lista_simbolo_t* lista_aux = func->simb->lista_de_parametros;
    while(lista_aux != NULL){
        printf("%s\n", lista_aux->simb->nome);
        lista_aux = lista_aux->prox;
    }
    printf("FIM---------------------------------------\n");
}