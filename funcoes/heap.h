// funcoes/heap.h
#ifndef HEAP_H
#define HEAP_H

#include "paciente.h"

//Cria um novo Heap
Heap *criarHeap(int capacidade);

//Insere valor no heap
int inserirHeap(Heap *heap, Paciente *paciente);

//Remove valor do heap
Paciente *removerHeap(Heap *heap);

//Mostra os valores do heap
void mostrarHeap(Heap *heap);

//Libera o Heap
void liberarHeap(Heap *heap);

void menuHeap(ListaPacientes *lista, Heap *heap);

#endif