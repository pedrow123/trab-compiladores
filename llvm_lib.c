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

    // --- Bloco de Debug 1: Inspecionando os Argumentos da CHAMADA (x, y) ---
    printf("\n--- DEBUG: Inspecionando Argumentos na Chamada da Função '%s' ---\n", func->nome);
    exp_t* arg_atual = parametros;
    int arg_num = 0;
    if (arg_atual == NULL) {
        printf("  -> Nenhum argumento foi passado para a função.\n");
    } else {
        while (arg_atual != NULL) {
            printf("  Argumento #%d:\n", arg_num);
            printf("    -> nome:        '%s'\n", arg_atual->nome ? arg_atual->nome : "(null)");
            printf("    -> tipo:        '%s'\n", arg_atual->tipo ? arg_atual->tipo : "(null)");
            printf("    -> tipo_llvm:   '%s'\n", arg_atual->tipo_llvm ? arg_atual->tipo_llvm : "(null)");
            arg_atual = arg_atual->prox;
            arg_num++;
        }
    }
    printf("--- FIM DA INSPEÇÃO DE ARGUMENTOS ---\n\n");
    // --- FIM DO Bloco de Debug 1 ---


    // --- NOVO Bloco de Debug 2: Inspecionando os Parâmetros da DECLARAÇÃO (a, b) ---
    tabela_simbolos_t* simb_func_debug = busca_funcao_ts(ts, func->nome);
    printf("\n--- DEBUG: Inspecionando Parâmetros da DECLARAÇÃO da Função %s ---\n", simb_func_debug->simb->nome);
    if (simb_func_debug && simb_func_debug->simb->lista_de_parametros) {
        lista_simbolo_t* param_atual = simb_func_debug->simb->lista_de_parametros;
        int param_num = 0;
        while (param_atual != NULL) {
            printf("  Parâmetro Declarado #%d:\n", param_num);
            if (param_atual->simb) {
                printf("    -> nome: '%s'\n", param_atual->simb->nome ? param_atual->simb->nome : "(null)");
                printf("    -> tipo: '%s'\n", param_atual->simb->tipo ? param_atual->simb->tipo : "(null)"); // <<< PROCURE POR UM '(null)' AQUI
                printf("    -> tipo_simb: '%s'\n", param_atual->simb->tipo_simb ? param_atual->simb->tipo_simb : "(null)");
            } else {
                printf("    -> ERRO: O ponteiro para o símbolo nesta lista é nulo!\n");
            }
            param_atual = param_atual->prox;
            param_num++;
        }
    } else {
        printf("  -> A função não foi encontrada ou não tem uma lista de parâmetros salva.\n");
    }
    printf("--- FIM DA INSPEÇÃO DA DECLARAÇÃO ---\n\n");
    // --- FIM do Novo Bloco de Debug 2 ---

    simbolo_t* simb_func = busca_simbolo(ts, func->nome);
    if (!simb_func) {
        char erro[256];
        sprintf(erro, "Função '%s' não foi declarada anteriormente!", func->nome);
        yyerror(erro);
        return;
    }

    fprintf(fp, "%%%d = call %s @%s(", temp_count, converte_tipo(simb_func->tipo), func->nome);

    lista_simbolo_t* param_decl = simb_func->lista_de_parametros;
    exp_t* arg_pass = parametros;

    while (param_decl != NULL) {
        if (arg_pass == NULL) {
            yyerror("Faltam argumentos na chamada da função.");
            fprintf(fp, ")\n"); // Fecha a chamada para evitar erro de sintaxe LLVM
            return;
        }

        // Exemplo: Verificação de tipo (ajuste conforme necessário)
        if (strcmp(converte_tipo(param_decl->simb->tipo), arg_pass->tipo_llvm) != 0) {
            char erro[256];
            sprintf(erro, "Tipo do parâmetro '%s' não corresponde ao argumento.", param_decl->simb->nome);
            yyerror(erro);
        }
        // Exemplo: Verificação de parâmetro por referência (VAR)
        if (strcmp(param_decl->simb->tipo_simb, "ponteiro") == 0 && strcmp(arg_pass->tipo, "variavel") != 0) {
            char erro[256];
            sprintf(erro, "Parâmetro '%s' é por referência (VAR), mas o argumento não é uma variável!", param_decl->simb->nome);
            yyerror(erro);
        }
        // --- FIM DAS VERIFICAÇÕES ---

        // Imprime o argumento na chamada LLVM
        fprintf(fp, "%s %%%d", arg_pass->tipo_llvm, arg_pass->id_temporario);

        // Avança para o próximo parâmetro e próximo argumento
        param_decl = param_decl->prox;
        arg_pass = arg_pass->prox;

        // Imprime a vírgula se ainda houver mais parâmetros declarados
        if (param_decl != NULL) {
            fprintf(fp, ", ");
        }
    }

    // 5. Após o laço, verifica se sobraram argumentos que não foram usados
    if (arg_pass != NULL) {
        yyerror("Foram passados mais argumentos do que a função espera.");
    }

    // 6. Fecha a instrução de chamada LLVM
    fprintf(fp, ")\n");
    
}