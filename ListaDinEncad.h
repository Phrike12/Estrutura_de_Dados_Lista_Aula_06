#ifndef LISTA_DIN_ENCAD_H
#define LISTA_DIN_ENCAD_H

struct tarefa {
    int codigo;
    char descricao[40];
    int prioridade;
};

typedef struct elemento* ListaTarefas;

ListaTarefas* cria_lista(void);
void libera_lista(ListaTarefas* li);
int tamanho_lista(ListaTarefas* li);
int lista_cheia(ListaTarefas* li);
int lista_vazia(ListaTarefas* li);
int insere_tarefa_inicio(ListaTarefas* li, struct tarefa t);
int insere_tarefa_final(ListaTarefas* li, struct tarefa t);
int insere_tarefa_ordenada(ListaTarefas* li, struct tarefa t);
int remove_tarefa_inicio(ListaTarefas* li);
int remove_tarefa_final(ListaTarefas* li);
int remove_tarefa(ListaTarefas* li, int codigo);
int busca_tarefa_pos(ListaTarefas* li, int pos, struct tarefa *t);
int busca_tarefa_cod(ListaTarefas* li, int codigo, struct tarefa *t);

int conta_tarefas_prioridade(ListaTarefas* li, int prioridade);
int tarefa_mais_urgente(ListaTarefas* li, struct tarefa *t);
int busca_tarefa_desc(ListaTarefas* li, char *texto, struct tarefa *t);
int insere_tarefa_final_prioridade(ListaTarefas* li, struct tarefa t);
int remove_tarefas_prioridade(ListaTarefas* li, int prioridade);
int inverte_lista(ListaTarefas* li);
int remove_tarefa_pos(ListaTarefas* li, int pos);
int mescla_tarefas(ListaTarefas* dst, ListaTarefas* src);

#endif