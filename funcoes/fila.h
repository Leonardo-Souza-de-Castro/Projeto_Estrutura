// funcoes/fila.h
#ifndef FILA_H
#define FILA_H

#include "paciente.h"

typedef struct NoFila {
    Paciente* paciente;
    struct NoFila* prox;
} NoFila;

typedef struct {
    NoFila* head;
    NoFila* tail;
    int qtd;
} Fila;

Fila* criarFila();
int enfileirar(Fila* fila, Paciente* paciente);
Paciente* desenfileirar(Fila* fila);
void mostrarFila(Fila* fila);
void liberarFila(Fila* fila);

#endif