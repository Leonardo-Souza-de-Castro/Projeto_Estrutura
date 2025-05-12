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

    NoFila* novo = (NoFila*) malloc(sizeof(NoFila));
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

    NoFila* removido = fila->head;
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

    NoFila* aux = fila->head;
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