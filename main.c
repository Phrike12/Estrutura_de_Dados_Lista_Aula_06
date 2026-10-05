#include <stdio.h>
#include <string.h>
#include "ListaDinEncad.h"

static struct tarefa mk(int codigo, const char *descricao, int prioridade) {
    struct tarefa t;
    t.codigo = codigo;
    strncpy(t.descricao, descricao, sizeof(t.descricao) - 1);
    t.descricao[sizeof(t.descricao) - 1] = '\0';
    t.prioridade = prioridade;
    return t;
}

static void imprime(const char *rotulo, ListaTarefas *li) {
    int i, n = tamanho_lista(li);
    struct tarefa t;
    
    printf("\n>>> %s (Total: %d tarefa%s)\n", rotulo, n, n == 1 ? "" : "s");
    
    if (n == 0) {
        printf("    [ Lista Vazia ]\n");
    } else {
        for (i = 1; i <= n; i++) {
            busca_tarefa_pos(li, i, &t);
            printf("    %d. Cod: %02d | Prioridade: %d | Tarefa: %s\n", 
                   i, t.codigo, t.prioridade, t.descricao);
        }
    }
    printf("\n");
}

int main(void) {
    ListaTarefas *li = cria_lista();
    struct tarefa t;

    printf("\n====================================================\n");
    printf("       TESTE DO GERENCIADOR DE TAREFAS (AULA 06)    \n");
    printf("====================================================\n");

    insere_tarefa_final(li, mk(1, "Comprar pao", 2));
    insere_tarefa_final(li, mk(2, "Estudar C", 1));
    insere_tarefa_final(li, mk(3, "Limpar casa", 3));
    insere_tarefa_final(li, mk(4, "Fazer exercicio", 2));
    imprime("LISTA INICIAL DE TAREFAS", li);

    printf("[Teste 1] Contar quantas tarefas tem Prioridade 2:\n");
    printf("-> Resultado: Existem %d tarefa(s) com prioridade 2.\n", conta_tarefas_prioridade(li, 2));

    printf("\n[Teste 2] Buscar qual e a tarefa mais urgente (Prioridade mais baixa):\n");
    if (tarefa_mais_urgente(li, &t)) {
        printf("-> Resultado: A mais urgente e '%s' (Prioridade %d).\n", t.descricao, t.prioridade);
    }

    printf("\n[Teste 3] Buscar uma tarefa pela palavra 'dar C':\n");
    if (busca_tarefa_desc(li, "dar C", &t)) {
        printf("-> Resultado: Encontrada! O codigo dela e %d (%s).\n", t.codigo, t.descricao);
    }

    printf("\n[Teste 4] Inserir nova tarefa ('Ligar para mae', P:2) agrupada com as outras de mesma prioridade:");
    insere_tarefa_final_prioridade(li, mk(5, "Ligar para mae", 2));
    imprime("LISTA APOS INSERIR NOVA TAREFA", li);

    printf("[Teste 5] Remover TODAS as tarefas que tenham Prioridade 2:\n");
    int removidas = remove_tarefas_prioridade(li, 2);
    printf("-> Resultado: Foram removidas %d tarefa(s).\n", removidas);
    imprime("LISTA APOS REMOCAO", li);

    printf("[Teste 6] Inverter a ordem da lista inteira:");
    inverte_lista(li);
    imprime("LISTA INVERTIDA", li);

    printf("[Teste 7] Remover especificamente a tarefa que esta na 1a posicao:");
    remove_tarefa_pos(li, 1);
    imprime("LISTA APOS REMOVER A 1a POSICAO", li);

    printf("[Teste 8] Mesclar a lista principal com uma nova lista secundaria:\n");
    ListaTarefas *li2 = cria_lista();
    insere_tarefa_final(li2, mk(10, "Nova Tarefa 1", 1));
    insere_tarefa_final(li2, mk(11, "Nova Tarefa 2", 3));
    
    int mescladas = mescla_tarefas(li, li2);
    printf("-> Resultado: Foram transferidas %d tarefa(s) da lista secundaria para a principal.", mescladas);
    imprime("LISTA PRINCIPAL FINAL", li);
    imprime("LISTA SECUNDARIA (Verificando se ficou vazia)", li2);

    libera_lista(li);
    libera_lista(li2);
    
    printf("====================================================\n");
    printf("                TESTES FINALIZADOS                  \n");
    printf("====================================================\n\n");

    return 0;
}