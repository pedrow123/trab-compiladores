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

    printf("Tipo simbolo: %s\n", ts->simb->tipo);    
    fprintf(fp, "\ndefine %s @%s(", converte_tipo(ts->simb->tipo), ts->simb->nome);
    emite_param(fp, ts);
        
}

tabela_simbolos_t* emite_param(FILE* fp, tabela_simbolos_t* nodo) {
    int count = 0;
    tabela_simbolos_t* params[64];

    tabela_simbolos_t* aux = nodo->prox;  // pula o símbolo da função

    while (aux && (strcmp(aux->simb->tipo_simb, "parametro") == 0 || strcmp(aux->simb->tipo_simb, "ponteiro") == 0)) {
        params[count++] = aux;
        aux = aux->prox;
    }

    printf("%d", count);

    for (int i = count - 1; i >= 0; i--) {
        if (!strcmp(params[i]->simb->tipo_simb, "parametro"))
            fprintf(fp, "%s %%%s_t", converte_tipo(params[i]->simb->tipo), params[i]->simb->nome);
        else
            fprintf(fp, "ptr %%%s", params[i]->simb->nome);

        if (i != 0)
            fprintf(fp, ", ");
    }

    fprintf(fp, ") {\nentry:\n\n");

    // Emite código de alocação e store dos parâmetros
    for (int i = count -1; i >= 0; i--) {
        if (!strcmp(params[i]->simb->tipo_simb, "parametro")){

            fprintf(fp, "%%%s = alloca %s\n", params[i]->simb->nome, converte_tipo(params[i]->simb->tipo));
            fprintf(fp, "store %s %%%s_t, ptr %%%s\n",
                converte_tipo(params[i]->simb->tipo),
                params[i]->simb->nome,
                params[i]->simb->nome
            );
        }
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

void ret_funcao(int temp_id, tabela_simbolos_t* ts){
    while(ts != NULL){
        if(strcmp(ts->simb->tipo_simb, "retorno") == 0)
        break;
        ts = ts->prox;
    }
    fprintf(out_file, "%%%d = load %s, ptr %%%s\n", temp_id, converte_tipo(ts->simb->tipo), ts->simb->nome);
    fprintf(out_file, "ret %s %%%d\n", converte_tipo(ts->simb->tipo), temp_id);
}

void cria_if(FILE* fp, exp_t* exp, int if_count){
    int id_result = if_count;
    fprintf(fp, "br i1 %%%d, label %%then_%d, label %%else_%d\n", exp->id_temporario, id_result, id_result);
    fprintf(fp, "then_%d:\n", id_result);
}

void cria_fim_then(FILE* fp, int if_count){
    fprintf(fp, "br label %%end_if_%d\n", if_count);
    fprintf(fp, "else_%d:\n", if_count);
}

void cria_fim_else(FILE* fp, int if_count){
    fprintf(fp, "br label %%end_if_%d\n", if_count);
    fprintf(fp, "end_if_%d:\n", if_count);
}

tabela_simbolos_t * busca_funcao_ts(tabela_simbolos_t * ts, char *nome){
    while(ts != NULL){
        if(strcmp(ts->simb->nome, nome) == 0 && strcmp(ts->simb->tipo_simb, "funcao") == 0)
            return ts;
        ts = ts->prox;
    }
    return NULL;
}

void cria_chamada_funcao(FILE* fp, exp_t* parametros, exp_t* func, tabela_simbolos_t* ts, int temp_count){
    tabela_simbolos_t* ts_func = busca_funcao_ts(ts, func->nome);
    if (!ts_func) {
        char erro[256];
        sprintf(erro, "Função '%s' não foi declarada anteriormente!", func->nome);
        yyerror(erro);
    }
    printf("%s\n", ts_func->simb->nome);
    printf("%s\n", ts_func->prox->simb->nome);

    imprime_tabela_debug(ts);

    fprintf(fp, "%%%d := call %s @%s(", temp_count, converte_tipo(ts_func->simb->tipo), func->nome);

    tabela_simbolos_t* aux = ts_func->prox;  // pula o símbolo da função
    tabela_simbolos_t* params[64];
    int count = 0;

    while (aux && (strcmp(aux->simb->tipo_simb, "parametro") == 0 || strcmp(aux->simb->tipo_simb, "ponteiro") == 0)) {
        params[count++] = aux;
        aux = aux->prox;
        printf("%d %s\n", count, params[count-1]->simb->nome);
    }

    printf("AAAAAAAAAAAAAAAA %d", count);

    for (int i = count - 1; i >= 0; i--) {
        if (!parametros) {
            yyerror("Faltam argumentos na chamada da função.");
            break;
        }

        if (strcmp(params[i]->simb->tipo, parametros->tipo) != 0) {
            char erro[256];
            sprintf(erro, "Tipo do parâmetro '%s' não corresponde ao argumento '%s'.", params[i]->simb->nome, parametros->nome);
            yyerror(erro);
        }

        if (strcmp(params[i]->simb->tipo_simb, "ponteiro") == 0 && strcmp(parametros->tipo, "var") != 0) {
            char erro[256];
            sprintf(erro, "Parâmetro '%s' é por referência, mas o argumento não é uma variável!", params[i]->simb->nome);
            yyerror(erro);
        }

        fprintf(fp, "%s %%%d", converte_tipo(parametros->tipo_llvm), parametros->id_temporario);
        if (i > 0) {
            fprintf(fp, ", ");
        }

        parametros = parametros->prox;

    }

    if (parametros) {
        yyerror("Foram passados mais argumentos do que a função espera.");
    }

    fprintf(fp, ")\n");
}