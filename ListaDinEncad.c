#include <stdlib.h>
#include <string.h>
#include "ListaDinEncad.h"

struct elemento {
    struct tarefa dados;
    struct elemento *prox;
};
typedef struct elemento Elem;

ListaTarefas* cria_lista(void) {
    ListaTarefas* li = (ListaTarefas*) malloc(sizeof(ListaTarefas));
    if (li != NULL)
        *li = NULL;               
    return li;
}

void libera_lista(ListaTarefas* li) {
    if (li != NULL) {
        Elem* no;
        while ((*li) != NULL) {
            no = *li;
            *li = (*li)->prox;    
            free(no);
        }
        free(li);                
    }
}

int tamanho_lista(ListaTarefas* li) {
    if (li == NULL)
        return -1;
    int cont = 0;
    Elem* no = *li;
    while (no != NULL) {          
        cont++;
        no = no->prox;
    }
    return cont;
}

int lista_cheia(ListaTarefas* li) {
    if (li == NULL)
        return -1;
    return 0;                    
}

int lista_vazia(ListaTarefas* li) {
    if (li == NULL)
        return -1;
    if (*li == NULL)
        return 1;
    return 0;
}

int insere_tarefa_inicio(ListaTarefas* li, struct tarefa t) {
    if (li == NULL) return 0;
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) return 0;     
    no->dados = t;
    no->prox = (*li);             
    *li = no;                     
    return 1;
}

int insere_tarefa_final(ListaTarefas* li, struct tarefa t) {
    if (li == NULL) return 0;
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) return 0;
    no->dados = t;
    no->prox = NULL;             
    if ((*li) == NULL) {          
        *li = no;
    } else {
        Elem* aux = *li;
        while (aux->prox != NULL) 
            aux = aux->prox;
        aux->prox = no;
    }
    return 1;
}

int insere_tarefa_ordenada(ListaTarefas* li, struct tarefa t) {
    if (li == NULL) return 0;
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) return 0;
    no->dados = t;
    if ((*li) == NULL) {          
        no->prox = NULL;
        *li = no;
        return 1;
    } else {
        Elem *ant = NULL, *atual = *li;
        while (atual != NULL &&
               atual->dados.prioridade < t.prioridade) {
            ant = atual;
            atual = atual->prox;
        }
        if (atual == *li) {       
            no->prox = (*li);
            *li = no;
        } else {                  
            no->prox = atual;
            ant->prox = no;
        }
        return 1;
    }
}

int remove_tarefa_inicio(ListaTarefas* li) {
    if (li == NULL) return 0;
    if ((*li) == NULL)            
        return 0;
    Elem *no = *li;
    *li = no->prox;             
    free(no);
    return 1;
}

int remove_tarefa_final(ListaTarefas* li) {
    if (li == NULL) return 0;
    if ((*li) == NULL)           
        return 0;
    Elem *ant = NULL, *no = *li;
    while (no->prox != NULL) {
        ant = no;
        no = no->prox;
    }
    if (no == (*li))             
        *li = no->prox;
    else
        ant->prox = no->prox;    
    free(no);
    return 1;
}

int remove_tarefa(ListaTarefas* li, int codigo) {
    if (li == NULL) return 0;
    if ((*li) == NULL)           
        return 0;
    Elem *ant = NULL, *no = *li;
    while (no != NULL && no->dados.codigo != codigo) {
        ant = no;
        no = no->prox;
    }
    if (no == NULL)               
        return 0;
    if (no == *li)                
        *li = no->prox;
    else
        ant->prox = no->prox;    
    free(no);
    return 1;
}

int busca_tarefa_pos(ListaTarefas* li, int pos, struct tarefa *t) {
    if (li == NULL || pos <= 0)
        return 0;
    Elem *no = *li;
    int i = 1;
    while (no != NULL && i < pos) { 
        no = no->prox;
        i++;
    }
    if (no == NULL)               
        return 0;
    else {
        *t = no->dados;
        return 1;
    }
}

int busca_tarefa_cod(ListaTarefas* li, int codigo, struct tarefa *t) {
    if (li == NULL)
        return 0;
    Elem *no = *li;
    while (no != NULL && no->dados.codigo != codigo)
        no = no->prox;
    if (no == NULL)              
        return 0;
    else {
        *t = no->dados;
        return 1;
    }
}

int conta_tarefas_prioridade(ListaTarefas* li, int prioridade) {
    if (li == NULL) return -1;
    int count = 0;
    Elem* no = *li;
    while (no != NULL) {
        if (no->dados.prioridade == prioridade) {
            count++;
        }
        no = no->prox;
    }
    return count;
}

int tarefa_mais_urgente(ListaTarefas* li, struct tarefa *t) {
    if (li == NULL || *li == NULL) return 0;
    Elem* no = *li;
    Elem* urgente = no;
    
    while (no != NULL) {
        if (no->dados.prioridade < urgente->dados.prioridade) {
            urgente = no;
        }
        no = no->prox;
    }
    *t = urgente->dados;
    return 1;
}

int busca_tarefa_desc(ListaTarefas* li, char *texto, struct tarefa *t) {
    if (li == NULL) return 0;
    Elem* no = *li;
    
    while (no != NULL) {
        if (strstr(no->dados.descricao, texto) != NULL) {
            *t = no->dados;
            return 1;
        }
        no = no->prox;
    }
    return 0;
}

int insere_tarefa_final_prioridade(ListaTarefas* li, struct tarefa t) {
    if (li == NULL) return 0;
    Elem* novo = (Elem*) malloc(sizeof(Elem));
    if (novo == NULL) return 0;
    novo->dados = t;

    Elem* no = *li;
    Elem* ultimo_prioridade = NULL;
    Elem* ultimo_lista = NULL;

    while (no != NULL) {
        if (no->dados.prioridade == t.prioridade) {
            ultimo_prioridade = no;
        }
        ultimo_lista = no;
        no = no->prox;
    }

    if (ultimo_prioridade != NULL) {
        novo->prox = ultimo_prioridade->prox;
        ultimo_prioridade->prox = novo;
    } else if (ultimo_lista != NULL) {
        novo->prox = NULL;
        ultimo_lista->prox = novo;
    } else {
        novo->prox = NULL;
        *li = novo;
    }
    return 1;
}

int remove_tarefas_prioridade(ListaTarefas* li, int prioridade) {
    if (li == NULL) return -1;
    int count = 0;
    Elem* ant = NULL;
    Elem* no = *li;

    while (no != NULL) {
        if (no->dados.prioridade == prioridade) {
            Elem* remover = no;
            if (ant == NULL) {
                *li = no->prox;
                no = *li;
            } else {
                ant->prox = no->prox;
                no = no->prox;
            }
            free(remover);
            count++;
        } else {
            ant = no;
            no = no->prox;
        }
    }
    return count;
}

int inverte_lista(ListaTarefas* li) {
    if (li == NULL) return 0;
    if (*li == NULL || (*li)->prox == NULL) return 1;

    Elem* ant = NULL;
    Elem* atual = *li;
    Elem* proximo = NULL;

    while (atual != NULL) {
        proximo = atual->prox; 
        atual->prox = ant;     
        ant = atual;           
        atual = proximo;       
    }
    *li = ant; 
    return 1;
}

int remove_tarefa_pos(ListaTarefas* li, int pos) {
    if (li == NULL || *li == NULL || pos <= 0) return 0;

    Elem* ant = NULL;
    Elem* no = *li;
    int i = 1;

    while (no != NULL && i < pos) {
        ant = no;
        no = no->prox;
        i++;
    }

    if (no == NULL) return 0; 

    if (ant == NULL) {
        *li = no->prox; 
    } else {
        ant->prox = no->prox;
    }
    free(no);
    return 1;
}

int mescla_tarefas(ListaTarefas* dst, ListaTarefas* src) {
    if (dst == NULL || src == NULL) return -1;
    if (*src == NULL) return 0; 

    int count = 0;
    Elem* temp = *src;
    
    while (temp != NULL) {
        count++;
        temp = temp->prox;
    }

    if (*dst == NULL) {
        *dst = *src; 
    } else {
        Elem* aux = *dst;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = *src; 
    }
    
    *src = NULL; 
    return count;
}