#include "llvm_lib.h"
#include "compilador.h"
#include <string.h>

void cria_func(FILE* fp, tabela_simbolos_t* ts_original){
    // tabela_simbolos_t* ts = reverter_lista(ts_original);
    // tabela_simbolos_t* ts = ir_para_fim(ts_original);
    tabela_simbolos_t* ts = ts_original;
    while(ts->simb->escopo == 1){
        ts = ts->prox;
    }

    
    fprintf(fp, "\ndefine %s @%s(", converte_tipo(ts->simb->tipo), ts->simb->nome);
    emite_param(fp, ts);
        
}

tabela_simbolos_t* emite_param(FILE* fp, tabela_simbolos_t* nodo) {
    int count = 0;
    tabela_simbolos_t* params[64];

    tabela_simbolos_t* aux = nodo->prox;  // pula o símbolo da função

    while (aux && (strcmp(aux->simb->tipo_simb, "parametro") == 0 || strcmp(aux->simb->tipo_simb, "parametro-ponteiro") == 0)) {
        params[count++] = aux;
        aux = aux->prox;
    }

    printf("%d", count);

    for (int i = count - 1; i >= 0; i--) {
        if (!strcmp(params[i]->simb->tipo_simb, "parametro"))
            fprintf(fp, "%s %%%s_t", converte_tipo(params[i]->simb->tipo), params[i]->simb->nome);
        else
            fprintf(fp, "ptr %%%s_t", params[i]->simb->nome);

        if (i != 0)
            fprintf(fp, ", ");
    }

    fprintf(fp, ") {\nentry:\n\n");

    // Emite código de alocação e store dos parâmetros
    for (int i = count -1; i >= 0; i--) {
        fprintf(fp, "%%%s = alloca %s\n", params[i]->simb->nome, converte_tipo(params[i]->simb->tipo));
        fprintf(fp, "store %s %%%s_t, ptr %%%s\n",
            converte_tipo(params[i]->simb->tipo),
            params[i]->simb->nome,
            params[i]->simb->nome
        );
    }

    tabela_simbolos_t* fim = ir_para_fim(nodo);
    alloca_variaveis_locais(fp, fim);

    return aux;
}



char *converte_tipo (char* tipo) {
    if (!strcmp(tipo, "INTEIRO"))
        return "i32";
    else if (!strcmp(tipo, "REAL"))
        return "float";
    else if (!strcmp(tipo, "VOID"))
        return "void";
    else
        return "i1";
}

void alloca_variaveis_locais(FILE* fp, tabela_simbolos_t* ts_fim) {
    tabela_simbolos_t* aux = ts_fim;

    while (aux) {
        if (aux->simb->escopo == 1 &&
            (!strcmp(aux->simb->tipo_simb, "variavel") || !strcmp(aux->simb->tipo_simb, "retorno"))) {

            fprintf(fp, "%%%s = alloca %s\n", aux->simb->nome, converte_tipo(aux->simb->tipo));
        }

        aux = aux->prev;
    }
}