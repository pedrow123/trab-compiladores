#include "llvm_lib.h"
#include "compilador.h"
#include <string.h>

void cria_func(FILE* fp, tabela_simbolos_t* ts){
    while(ts->simb->escopo == 1){
        ts = ts->prox;
    }

    fprintf(fp, "\ndefine %s @%s(", converte_tipo(ts->simb->tipo), ts->simb->nome);
    ts = emite_param(fp, ts->prox);
}

tabela_simbolos_t* emite_param (FILE* fp, tabela_simbolos_t* nodo) {
    // Primeira etapa: coletar parâmetros em ordem correta
    tabela_simbolos_t* parametros[64]; // limite de até 64 params
    int count = 0;

    tabela_simbolos_t* aux = nodo;
    while (aux && (!strcmp("parametro", aux->simb->tipo_simb) || !strcmp("parametro-ponteiro", aux->simb->tipo_simb))) {
        parametros[count++] = aux;
        aux = aux->prox;
    }

    // Gera a assinatura da função
    for (int i = 0; i < count; i++) {
        if (!strcmp("parametro", parametros[i]->simb->tipo_simb)) {
            fprintf(fp, "%s %%%s_t", converte_tipo(parametros[i]->simb->tipo), parametros[i]->simb->nome);
        } else if (!strcmp("parametro-ponteiro", parametros[i]->simb->tipo_simb)) {
            fprintf(fp, "ptr %%%s_t", parametros[i]->simb->nome);
        }

        if (i != count - 1)
            fprintf(fp, ", ");
    }

    fprintf(fp, ") {\nentry:\n\n");

    // Agora alloca os parâmetros
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%%%s = alloca %s\n", parametros[i]->simb->nome, converte_tipo(parametros[i]->simb->tipo));
        fprintf(fp, "store %s %%%s_t, ptr %%%s\n",
            converte_tipo(parametros[i]->simb->tipo),
            parametros[i]->simb->nome,
            parametros[i]->simb->nome
        );
    }

    // Atualiza nodo para continuar emitindo variáveis
    nodo = aux;

    // Alloca variáveis locais
    while (nodo && (!strcmp("variavel", nodo->simb->tipo_simb) || !strcmp("retorno", nodo->simb->tipo_simb))) {
        fprintf(fp, "%%%s = alloca %s\n", nodo->simb->nome, converte_tipo(nodo->simb->tipo));
        nodo = nodo->prox;
    }

    return nodo;
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