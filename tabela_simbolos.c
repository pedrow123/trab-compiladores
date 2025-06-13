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
        if (atual->simb && atual->simb->escopo == 1) {
            tabela_simbolos_t* para_remover = atual;
 
            tabela_simbolos_t* anterior = para_remover->prev;
            tabela_simbolos_t* proximo = para_remover->prox;

            if (anterior == NULL) {
                ts = proximo;
            } else {
                anterior->prox = proximo;
            }

            if (proximo != NULL) {
                proximo->prev = anterior;
            }

            atual = proximo;

            if (para_remover->simb) {
                free(para_remover->simb->nome);
                free(para_remover->simb->tipo);
                free(para_remover->simb->tipo_simb);
                free(para_remover->simb); 
            }
            free(para_remover);

        } else {
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
    exp_t* valor1 = gera_load_se_necessario(out_file, e1, temp_count);

    exp_t* valor2 = gera_load_se_necessario(out_file, e2, temp_count);
    if(!valor1 || !valor2){
        fprintf(stderr, "Não corresponde expressão. \n");
        exit(1);
    }

    // Verifica compatibilidade de tipo
    if (strcmp(valor1->tipo_llvm, valor2->tipo_llvm) != 0) {
        fprintf(stderr, "Erro: operação entre tipos incompatíveis: %s e %s\n", valor1->tipo_llvm, valor2->tipo_llvm);
        exit(1);
    }

    char* tipo_llvm = valor1->tipo_llvm;
    int id_result = (*temp_count)++;
    const char* instr = NULL;

    if (strcmp(operador, "+") == 0) {
        instr = strcmp(tipo_llvm, "i32") == 0 ? "add i32" : "fadd float";
    } else if (strcmp(operador, "-") == 0) {
        instr = strcmp(tipo_llvm, "i32") == 0 ? "sub i32" : "fsub float";
    } else if (strcmp(operador, "*") == 0) {
        instr = strcmp(tipo_llvm, "i32") == 0 ? "mul i32" : "fmul float";
    } else if (strcmp(operador, "/") == 0) {
        instr = strcmp(tipo_llvm, "i32") == 0 ? "sdiv i32" : "fdiv float";
    } else if (strcmp(operador, "or") == 0) {
        if(strcmp(valor1->tipo_llvm, "i32") == 0 && strcmp(valor2->tipo_llvm, "i32") == 0)
            instr = "or i32";
        else {
            fprintf(stderr, "Só é possível fazer comparações or com inteiros.\n");
            exit(1);
        }

    }

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

    fprintf(out_file, "%%%d = %s %%%d, %%%d\n", id_result, instr, valor1->id_temporario, valor2->id_temporario);

    exp_t* resultado = malloc(sizeof(exp_t));
    resultado->nome = strdup("exp");
    resultado->tipo = strdup("temp");
    resultado->id_temporario = id_result;
    resultado->tipo_llvm = tipo_llvm;
    resultado->simb = NULL;
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

lista_simbolo_t* duplica_lista_simbolo(lista_simbolo_t* original) {
    if (original == NULL) return NULL;
    
    lista_simbolo_t* nova_cabeca = malloc(sizeof(lista_simbolo_t));
    nova_cabeca->simb = original->simb;
    
    lista_simbolo_t* nova_atual = nova_cabeca;
    lista_simbolo_t* original_atual = original->prox;
    
    while (original_atual != NULL) {
        nova_atual->prox = malloc(sizeof(lista_simbolo_t));
        nova_atual = nova_atual->prox;
        nova_atual->simb = original_atual->simb;
        original_atual = original_atual->prox;
    }
    nova_atual->prox = NULL;
    return nova_cabeca;
}

simbolo_t* duplica_simbolo(simbolo_t* original) {
    if (original == NULL) {
        return NULL;
    }
    
    simbolo_t* copia = malloc(sizeof(simbolo_t));
    if (copia == NULL) {
        yyerror("Falha ao alocar memória para duplicar símbolo.");
        exit(1);
    }

    copia->nome = strdup(original->nome);
    copia->tipo = strdup(original->tipo);
    copia->tipo_simb = strdup(original->tipo_simb);

    copia->escopo = original->escopo;
    copia->lista_de_parametros = NULL;

    return copia;
}

void insere_parametros_funcao(tabela_simbolos_t* ts){
    tabela_simbolos_t* func = ts;
    while(func->simb->escopo == 1){
        func = func->prox;
    }
        
    int count = 0;
    tabela_simbolos_t* params[64];

    tabela_simbolos_t* aux = func->prox;  

    while (aux && (strcmp(aux->simb->tipo_simb, "parametro") == 0 || strcmp(aux->simb->tipo_simb, "ponteiro") == 0)) {
        params[count++] = aux;
        aux = aux->prox;
    }
    
    for(int i = count-1; i >= 0; i--){
        simbolo_t* simbolo_original = params[i]->simb;

        simbolo_t* copia_do_simbolo = duplica_simbolo(simbolo_original);

        func->simb->lista_de_parametros = insere_lista_simbolo(
            func->simb->lista_de_parametros, 
            copia_do_simbolo 
        );
        
    }
}


exp_t* gera_load_se_necessario(FILE* fp, exp_t* e, int* p_temp_count) {
    if (e == NULL) return NULL;

    // só gera 'load' se for uma referência de variável
    if (strcmp(e->tipo, "variavel") == 0) {
        exp_t* e_valor = malloc(sizeof(exp_t));
        
        e_valor->nome = strdup(e->nome);
        e_valor->prox = NULL;
        e_valor->tipo = strdup(e->tipo); 
        e_valor->tipo_llvm = strdup(e->tipo_llvm);
        e_valor->id_temporario = (*p_temp_count)++;


        fprintf(fp, "%%%d = load %s, ptr %s%s\n", 
                e_valor->id_temporario, 
                e_valor->tipo_llvm, 
                get_prefixo_de_escopo(e->simb), // <<< MUDANÇA
                e->nome);

        return e_valor;
    }

    // se não for 'variavel', já é um valor, retorna sem modificar
    return e;
}

char* get_prefixo_de_escopo(simbolo_t* s) {
    if (s != NULL && s->escopo == 0) {
        return "@";
    }
    return "%";
}