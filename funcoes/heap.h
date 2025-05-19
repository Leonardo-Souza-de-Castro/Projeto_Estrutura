// funcoes/heap.h
#ifndef HEAP_H
#define HEAP_H

#include "paciente.h"

#define TAM_MAX_HEAP 20

//Struct do heap
typedef struct {
    Paciente* pacientes[TAM_MAX_HEAP];
    int tamanho;
} Heap;

//Cria um novo Heap
Heap* criarHeap(int capacidade);

//Insere valor no heap
int inserirHeap(Heap* heap, Paciente* paciente);

//Remove valor do heap
Paciente* removerHeap(Heap* heap);

//Mostra os valores do heap
void mostrarHeap(Heap* heap);

//Libera o Heap
void liberarHeap(Heap* heap);

#endif