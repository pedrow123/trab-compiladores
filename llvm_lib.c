#include "llvm_lib.h"
#include "compilador.h"
#include <string.h>

void cria_func(FILE* fp, tabela_simbolos_t* ts_original){
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

    while (aux && (strcmp(aux->simb->tipo_simb, "parametro") == 0 || strcmp(aux->simb->tipo_simb, "ponteiro") == 0)) {
        params[count++] = aux;
        aux = aux->prox;
    }

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
    fprintf(fp, "\nthen_%d:\n", id_result);
}

void cria_fim_then(FILE* fp, int if_count){
    fprintf(fp, "br label %%end_if_%d\n", if_count);
    fprintf(fp, "\nelse_%d:\n", if_count);
}

void cria_fim_else(FILE* fp, int if_count){
    fprintf(fp, "br label %%end_if_%d\n", if_count);
    fprintf(fp, "\nend_if_%d:\n", if_count);
}

void cria_while(FILE *fp, int while_count) {
    fprintf(fp, "br label %%while_%d\n", while_count);
    fprintf(fp, "\nwhile_%d:\n", while_count);
}

void cria_do_while(FILE *fp, exp_t *exp, int while_count) {
    fprintf(fp, "br i1 %%%d, label %%do_%d, label %%end_while_%d\n", exp->id_temporario, while_count, while_count);
    fprintf(fp, "\ndo_%d:\n", while_count);
}

void cria_fim_while(FILE *fp, int while_count) {
    fprintf(fp, "br label %%while_%d\n" , while_count);
    fprintf(fp, "\nend_while_%d:\n" , while_count);
}

tabela_simbolos_t * busca_funcao_ts(tabela_simbolos_t * ts, char *nome){
    while(ts != NULL){
        if(strcmp(ts->simb->nome, nome) == 0 && (strcmp(ts->simb->tipo_simb, "funcao") == 0 || strcmp(ts->simb->tipo_simb, "procedure") == 0))
            return ts;
        ts = ts->prox;
    }
    return NULL;
}
void cria_chamada_funcao(FILE* fp, exp_t* argumentos_passados, exp_t* func, simbolo_t* simb_func, int* p_temp_count) {
    if (!simb_func) {
        char erro[256];
        sprintf(erro, "Símbolo da função '%s' não encontrado.", func->nome);
        yyerror(erro);
        return;
    }

    char arg_strings[64][128];
    int arg_count = 0;         

    lista_simbolo_t* param_decl = simb_func->lista_de_parametros;
    exp_t* arg_pass = argumentos_passados;

    while (param_decl != NULL) {
        if (arg_pass == NULL) {
            yyerror("Faltam argumentos na chamada da função.");
            return;
        }

        if (strcmp(converte_tipo(param_decl->simb->tipo), arg_pass->tipo_llvm) != 0) {
            char erro[256];
            sprintf(erro, "Tipo do parâmetro '%s' não corresponde ao argumento.", param_decl->simb->nome);
            yyerror(erro);
        }
        if (strcmp(param_decl->simb->tipo_simb, "ponteiro") == 0 && strcmp(arg_pass->tipo, "variavel") != 0) {
            char erro[256];
            sprintf(erro, "Parâmetro '%s' é por referência (VAR), mas o argumento não é uma variável!", param_decl->simb->nome);
            yyerror(erro);
        }

        
        if (strcmp(param_decl->simb->tipo_simb, "parametro") == 0) {
            exp_t* valor_arg = gera_load_se_necessario(fp, arg_pass, p_temp_count);
            sprintf(arg_strings[arg_count], "%s %%%d", valor_arg->tipo_llvm, valor_arg->id_temporario);

        } else { // Passagem por REFERÊNCIA
            sprintf(arg_strings[arg_count], "ptr @%s", arg_pass->nome);
        }
        
        arg_count++;
        param_decl = param_decl->prox;
        arg_pass = arg_pass->prox;
    }

    if (arg_pass != NULL) {
        yyerror("Foram passados mais argumentos do que a função espera.");
        return;
    }

    int func_result_id = (*p_temp_count)++;
    func->id_temporario = func_result_id;

    fprintf(fp, "%%%d = call %s @%s(", 
            func_result_id, 
            converte_tipo(simb_func->tipo), 
            func->nome);

    for (int i = 0; i < arg_count; i++) {
        fprintf(fp, "%s", arg_strings[i]);
        if (i < arg_count - 1) {
            fprintf(fp, ", ");
        }
    }

    fprintf(fp, ")\n");
}

void cria_chamada_procedimento(FILE* fp, exp_t* argumentos_passados, simbolo_t* simb_proc, int* p_temp_count) {
    if (!simb_proc) {
        yyerror("Procedimento ou função não encontrado para a chamada.");
        return;
    }

    char llvm_args_str[1024] = "";
    char single_arg_str[128];

    lista_simbolo_t* param_decl = simb_proc->lista_de_parametros;
    exp_t* arg_pass = argumentos_passados;

    while (param_decl != NULL) {
        if (arg_pass == NULL) {
            yyerror("Faltam argumentos na chamada do procedimento.");
            return;
        }

        if (strcmp(param_decl->simb->tipo_simb, "parametro") == 0) {
            exp_t* valor_arg = gera_load_se_necessario(fp, arg_pass, p_temp_count);
            sprintf(single_arg_str, "%s %%%d", valor_arg->tipo_llvm, valor_arg->id_temporario);
        } else { 
            if (strcmp(arg_pass->tipo, "variavel") != 0) {
                 yyerror("Parâmetro por referência (VAR) exige uma variável como argumento.");
            }
            sprintf(single_arg_str, "ptr %s%s", get_prefixo_de_escopo(arg_pass->simb), arg_pass->nome);
        }

        if (strlen(llvm_args_str) > 0) {
            strcat(llvm_args_str, ", ");
        }
        strcat(llvm_args_str, single_arg_str);

        param_decl = param_decl->prox;
        arg_pass = arg_pass->prox;
    }

    if (arg_pass != NULL) {
        yyerror("Foram passados mais argumentos do que o procedimento espera.");
        return;
    }

    const char* return_type_str = "void"; 
    if (strcmp(simb_proc->tipo_simb, "funcao") == 0) {
        return_type_str = converte_tipo(simb_proc->tipo);
    }

    fprintf(fp, "call %s @%s(%s)\n", 
            return_type_str, 
            simb_proc->nome, 
            llvm_args_str);
}

void cria_cabecalho(FILE *fp) {
    fprintf(fp, "declare i32 @printf(ptr noundef, ...)\n");
    fprintf(fp, "declare i32 @__isoc99_scanf(ptr noundef, ...)\n");
    fprintf(fp, "@read_int = private unnamed_addr constant [3 x i8] c\"%%d\\00\", align 1\n");
    fprintf(fp, "@write_int = private unnamed_addr constant [4 x i8] c\"%%d\\0A\\00\", align 1\n");
    fprintf(fp, "@read_float = private unnamed_addr constant [3 x i8] c\"%%f\\00\", align 1\n");
    fprintf(fp, "@write_float = private unnamed_addr constant [4 x i8] c\"%%f\\0A\\00\", align 1\n\n");
}

void cria_write(FILE *fp, exp_t *parametros, tabela_simbolos_t *ts, int *temp_id) {
    while (parametros) {
        exp_t *valor = gera_load_se_necessario(fp, parametros, temp_id);

        if (!strcmp("REAL", valor->tipo)) {
            int temp_double = (*temp_id)++; 
            fprintf(fp, "%%%d = fpext float %%%d to double\n", temp_double, valor->id_temporario);
            
            int temp_printf = (*temp_id)++; 
            fprintf(fp, "%%%d = call i32 (ptr, ...) @printf(ptr @write_float, double %%%d)\n", temp_printf, temp_double);
        } else { 
            int temp_printf = (*temp_id)++; 
            fprintf(fp, "%%%d = call i32 (ptr, ...) @printf(ptr @write_int, i32 %%%d)\n", temp_printf, valor->id_temporario);
        }
        parametros = parametros->prox;
    }
}

void cria_read(FILE *fp, exp_t *parametros, tabela_simbolos_t *ts, int *temp_id) {
    while (parametros != NULL) {
        if (strcmp(parametros->tipo, "variavel") != 0) {
            char erro[256];
            sprintf(erro, "Argumento para 'read' deve ser uma variável, mas foi '%s'.", parametros->nome);
            yyerror(erro);
            return;
        }

        simbolo_t* s = busca_simbolo(ts, parametros->nome);
        if (s == NULL) {
            char erro[256];
            sprintf(erro, "Variável '%s' não declarada.", parametros->nome);
            yyerror(erro);
            return;
        }

        fprintf(fp, "%%%d = call i32 (ptr, ...) @scanf(ptr %s, ptr %s%s)\n",
                (*temp_id)++,
                (strcmp(converte_tipo(s->tipo), "float") == 0 ? "@read_real" : "@read_int"),
                get_prefixo_de_escopo(s),
                s->nome);

        parametros = parametros->prox;
    }
}

