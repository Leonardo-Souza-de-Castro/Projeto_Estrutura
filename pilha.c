#include <stdio.h>
#include <stdlib.h>
#include "funcoes/pilha.h"
#include "funcoes/fila.h"
#include "funcoes/paciente.h"

Celula *start_Celula(Paciente *p, char op)
{
    Celula *nova = malloc(sizeof(Celula));
    nova->anterior = NULL;
    nova->proximo = NULL;
    nova->registro = p;
    nova->operacao = op;
    return nova;
}

Pilha *start_Pilha()
{
    Pilha *Pilha = malloc(sizeof(Pilha));
    Pilha->qtde = 0;
    Pilha->top = NULL;
    return Pilha;
}

void push(Pilha *Pilha, Paciente *p, char op)
{
    Celula *nova = start_Celula(p, op);
    if (Pilha->qtde != 0)
    {
        nova->proximo = Pilha->top;
        Pilha->top->anterior = nova;
    }
    Pilha->top = nova;
    Pilha->qtde++;
}

Celula *pop(Pilha *pilha) {
    if (pilha->qtde == 0) return NULL;

    Celula *topo = pilha->top;
    pilha->top = topo->proximo;
    if (pilha->top != NULL)
        pilha->top->anterior = NULL;

    pilha->qtde--;
    return topo;
}

void mostrarLog(Pilha* pilha) {
    Celula* atual = pilha->top;
    printf("\nLog de operações:\n");
    while (atual != NULL) {
        printf("Operação: %c, Paciente: %s\n", atual->operacao, atual->registro->nome);
        atual = atual->proximo;
    }
}

void desfazer(Fila* fila, Pilha* pilha, ListaPacientes *lista) {
    if (pilha->qtde == 0) {
        printf("Nenhuma operação para desfazer.\n");
        return;
    }

    mostrarLog(pilha);

    Celula *topo = pilha->top;

    Paciente *p = consultarPaciente(lista, topo->registro->rg);
    if (p == NULL) {
        printf("Paciente não encontrado na lista.\n");
        return;
    }

    printf("Paciente encontrado:\n");
    printf("Nome: %s\n", p->nome);
    printf("Idade: %d\n", p->idade);
    printf("RG: %s\n", p->rg);
    printf("Data de entrada: %02d/%02d/%04d\n", p->entrada->dia, p->entrada->mes, p->entrada->ano);
    printf("Operação a ser desfeita: %c\n", topo->operacao);

    char opcao;
    printf("Deseja realmente desfazer a operação? (s/n): ");
    scanf(" %c", &opcao);

    if (opcao == 's' || opcao == 'S') {
        if (topo->operacao == 'D' || topo->operacao == 'E') {
            // Recoloca o paciente na fila sem registrar no log
            enfileirar(fila, topo->registro, pilha, 0);
            pop(pilha);  // Remove a operação da pilha de log
        } else {
            printf("Operação desconhecida. Nenhuma ação realizada.\n");
        }
    }
}