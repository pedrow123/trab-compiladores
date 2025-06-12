#ifndef TABELA_SIMBOLOS_H
#define TABELA_SIMBOLOS_H

typedef struct simbolo {
    char *nome;
    char *tipo;
    char *tipo_simb;
    int escopo;
    struct lista_simbolo* lista_de_parametros;
} simbolo_t;

typedef struct tabela_simbolo {
    simbolo_t *simb;
    struct tabela_simbolo *prox;
    struct tabela_simbolo *prev;
} tabela_simbolos_t;

typedef struct lista_simbolo {
    simbolo_t *simb;
    struct lista_simbolo *prox;
} lista_simbolo_t;

typedef struct exp {
    char* nome;            // nome da variável, função, etc (opcional)
    char* tipo;            // "numero", "var", "funcao", etc
    int id_temporario;     // número do temporário gerado (LLVM)
    char* tipo_llvm;       // i32, float, etc
    struct simbolo* simb; 
    struct exp *prox;
} exp_t;

simbolo_t * cria_simbolo(char *nome, char* tipo_simb, int escopo);

lista_simbolo_t* insere_lista_simbolo(lista_simbolo_t* lista, simbolo_t* simb);

void atualiza_tipo_simbolos(lista_simbolo_t* lista, char* tipo);

void atualiza_tipo_novo(lista_simbolo_t* lista, char* tipo);

void free_lista_simbolo(lista_simbolo_t * lista);

tabela_simbolos_t * cria_novo_simbolo_ts(tabela_simbolos_t * ts, simbolo_t * simb);

tabela_simbolos_t * insere_simbolos_ts(tabela_simbolos_t * ts, lista_simbolo_t * lista);

simbolo_t * busca_simbolo(tabela_simbolos_t * ts, char *nome);

void destroi_tabela(tabela_simbolos_t * ts);

tabela_simbolos_t* destroi_var_locais(tabela_simbolos_t* ts);

void imprime_ts (FILE *fp, tabela_simbolos_t* ts);

void cria_globais(tabela_simbolos_t* ts, FILE* fp);

tabela_simbolos_t* ir_para_fim(tabela_simbolos_t* ts);

exp_t* cria_expressao_binaria(FILE* out_file, exp_t* e1, exp_t* e2, const char* operador, int* id_atual);

exp_t* cria_parametros_funcao(exp_t* raiz, exp_t* nova);

void imprime_tabela_debug(tabela_simbolos_t * ts);

void insere_parametros_funcao(tabela_simbolos_t* ts);

lista_simbolo_t* duplica_lista_simbolo(lista_simbolo_t* original);
exp_t* gera_load_se_necessario(FILE* fp, exp_t* e, int* p_temp_count);
char* get_prefixo_de_escopo(simbolo_t* s);
#endif