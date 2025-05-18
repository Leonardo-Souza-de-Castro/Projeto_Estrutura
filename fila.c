// funcoes/fila.c
#include <stdio.h>
#include <stdlib.h>
#include "funcoes/fila.h"

Fila* criarFila() {
    Fila* fila = (Fila*) malloc(sizeof(Fila));
    if (fila != NULL) {
        fila->head = NULL;
        fila->tail = NULL;
        fila->qtd = 0;
    }
    return fila;
}

int enfileirar(Fila* fila, Paciente* paciente) {
    if (fila == NULL || paciente == NULL) return 0;

    EFila* novo = (EFila*) malloc(sizeof(EFila));
    if (novo == NULL) return 0;

    novo->paciente = paciente;
    novo->prox = NULL;

    if (fila->qtd == 0) {
        fila->head = novo;
    } else {
        fila->tail->prox = novo;
    }
    fila->tail = novo;
    fila->qtd++;
    return 1;
}

Paciente* desenfileirar(Fila* fila) {
    if (fila == NULL || fila->qtd == 0) return NULL;

    EFila* removido = fila->head;
    Paciente* paciente = removido->paciente;
    fila->head = removido->prox;

    if (fila->head == NULL) {
        fila->tail = NULL;
    }

    free(removido);
    fila->qtd--;
    return paciente;
}

void mostrarFila(Fila* fila) {
    if (fila == NULL || fila->head == NULL) {
        printf("Fila vazia.\n");
        return;
    }

    EFila* aux = fila->head;
    while (aux != NULL) {
        Paciente* p = aux->paciente;
        printf("%s (%d anos) - RG: %s\n", p->nome, p->idade, p->rg);
        aux = aux->prox;
    }
}

void liberarFila(Fila* fila) {
    while (fila->qtd > 0) {
        desenfileirar(fila);
    }
    free(fila);
}

void menu() {
    printf("\n=== GERENCIADOR DE ATENDIMENTO MÉDICO ===\n");
    printf("1. Enfileirar paciente\n");
    printf("2. Desenfileirar paciente\n");
    printf("3. Mostrar fila\n");
    printf("0. Sair\n");
    printf("Escolha: ");
}

void menuFila(ListaPacientes *lista, Fila *fila){
    int opcao;
    do {
        menu();
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                Paciente* p = consultarPaciente(lista);
                enfileirar(fila, p); //não sei oq passar como parametro aqui
                break;
            case 2:
                desenfileirar(fila);
                break;
            case 3:
                mostrarFila(fila);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);
}