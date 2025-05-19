#include <stdio.h>
#include <stdlib.h>
#include "funcoes/pilha.h"
#include "funcoes/fila.h"
#include "funcoes/paciente.h"

// Função que cria uma nova célula da pilha com o paciente e operação fornecidos
Celula *start_Celula(Paciente *p, char op)
{
    Celula *nova = malloc(sizeof(Celula));  // Aloca memória para uma nova célula
    nova->anterior = NULL;                   // Inicializa o ponteiro anterior como NULL
    nova->proximo = NULL;                    // Inicializa o ponteiro próximo como NULL
    nova->registro = p;                      // Associa o paciente passado à célula
    nova->operacao = op;                     // Armazena o caractere da operação realizada
    return nova;                            // Retorna o ponteiro para a nova célula criada
}

// Função que inicializa uma pilha vazia
Pilha *start_Pilha()
{
    Pilha *Pilha = malloc(sizeof(Pilha));   // Aloca memória para a pilha
    Pilha->qtde = 0;                        // Inicializa a quantidade de elementos com 0
    Pilha->top = NULL;                      // Inicializa o topo da pilha como NULL (vazia)
    return Pilha;                          // Retorna a pilha inicializada
}

// Função que insere um elemento no topo da pilha (push)
void push(Pilha *Pilha, Paciente *p, char op)
{
    Celula *nova = start_Celula(p, op);   // Cria uma nova célula com o paciente e operação
    if (Pilha->qtde != 0)                  // Se a pilha não estiver vazia
    {
        nova->proximo = Pilha->top;        // Aponta o próximo da nova célula para o topo atual
        Pilha->top->anterior = nova;       // Ajusta o anterior do topo atual para a nova célula
    }
    Pilha->top = nova;                     // Atualiza o topo da pilha para a nova célula
    Pilha->qtde++;                        // Incrementa a quantidade de elementos da pilha
}

// Função que remove e retorna o elemento do topo da pilha (pop)
Celula *pop(Pilha *pilha) {
    if (pilha->qtde == 0) return NULL;    // Se a pilha estiver vazia, retorna NULL

    Celula *topo = pilha->top;             // Guarda o ponteiro para o topo atual
    pilha->top = topo->proximo;            // Atualiza o topo para o próximo elemento da pilha
    if (pilha->top != NULL)                 // Se novo topo não for NULL
        pilha->top->anterior = NULL;       // Ajusta o anterior do novo topo para NULL

    pilha->qtde--;                         // Decrementa a quantidade de elementos da pilha
    return topo;                          // Retorna a célula removida do topo
}

// Função que mostra o log de operações armazenado na pilha
void mostrarLog(Pilha* pilha) {
    Celula* atual = pilha->top;            // Começa pelo topo da pilha
    printf("\nLog de operações:\n");
    while (atual != NULL) {                 // Percorre todas as células da pilha
        printf("Operação: %c, Paciente: %s\n", atual->operacao, atual->registro->nome);
        atual = atual->proximo;             // Vai para a próxima célula da pilha
    }
}

// Função para desfazer a última operação realizada, baseada na pilha de operações
void desfazer(Fila* fila, Pilha* pilha, ListaPacientes *lista) {
    if (pilha->qtde == 0) {                 // Se não houver operações para desfazer
        printf("Nenhuma operação para desfazer.\n");
        return;                            // Sai da função
    }

    mostrarLog(pilha);                      // Mostra o log atual de operações

    Celula *topo = pilha->top;             // Pega a operação mais recente (topo da pilha)

    Paciente *p = consultarPaciente(lista, topo->registro->rg);  // Busca o paciente na lista pelo RG
    if (p == NULL) {                       // Se paciente não for encontrado
        printf("Paciente não encontrado na lista.\n");
        return;                           // Sai da função
    }

    // Exibe as informações do paciente encontrado e operação a ser desfeita
    printf("Paciente encontrado:\n");
    printf("Nome: %s\n", p->nome);
    printf("Idade: %d\n", p->idade);
    printf("RG: %s\n", p->rg);
    printf("Data de entrada: %02d/%02d/%04d\n", p->entrada->dia, p->entrada->mes, p->entrada->ano);
    printf("Operação a ser desfeita: %c\n", topo->operacao);

    char opcao;
    printf("Deseja realmente desfazer a operação? (s/n): ");
    scanf(" %c", &opcao);                   // Lê a confirmação do usuário (sim ou não)

    if (opcao == 's' || opcao == 'S') {    // Se o usuário confirmar a desfazer
        if (topo->operacao == 'D' || topo->operacao == 'E') {
            // Se a operação foi 'D' (remover) ou 'E' (enfileirar), recoloca paciente na fila
            enfileirar(fila, topo->registro, pilha, 0);  // Enfileira paciente sem registrar operação no log
            pop(pilha);                   // Remove a operação da pilha (desfeita)
        } else {
            printf("Operação desconhecida. Nenhuma ação realizada.\n");  // Caso operação não reconhecida
        }
    }
}
