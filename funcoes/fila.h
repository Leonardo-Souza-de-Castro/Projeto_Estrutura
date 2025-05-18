// funcoes/fila.h
#ifndef FILA_H
#define FILA_H

#include "paciente.h"

typedef struct EFila {
    Paciente* paciente;
    struct EFila* prox;
} EFila;

typedef struct {
    EFila* head;
    EFila* tail;
    int qtd;
} Fila;

Fila* criarFila();
int enfileirar(Fila* fila, Paciente* paciente);
Paciente* desenfileirar(Fila* fila);
void mostrarFila(Fila* fila);
void liberarFila(Fila* fila);

#endif