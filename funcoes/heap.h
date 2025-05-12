// funcoes/heap.h
#ifndef HEAP_H
#define HEAP_H

#include "paciente.h"

#define TAM_MAX_HEAP 20

typedef struct {
    Paciente* pacientes[TAM_MAX_HEAP];
    int tamanho;
} Heap;

Heap* criarHeap(int capacidade);
int inserirHeap(Heap* heap, Paciente* paciente);
Paciente* removerHeap(Heap* heap);
void mostrarHeap(Heap* heap);
void liberarHeap(Heap* heap);

#endif