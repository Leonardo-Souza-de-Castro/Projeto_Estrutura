// funcoes/heap.h
#ifndef HEAP_H
#define HEAP_H

#include "paciente.h"

// Cria e retorna um novo heap com a capacidade especificada
Heap *criarHeap(int capacidade);

// Insere um paciente no heap mantendo a propriedade de prioridade
int inserirHeap(Heap *heap, Paciente *paciente);

// Remove e retorna o paciente com maior prioridade (no topo do heap)
Paciente *removerHeap(Heap *heap);

// Exibe todos os pacientes presentes no heap
void mostrarHeap(Heap *heap);

// Libera a memória alocada para o heap
void liberarHeap(Heap *heap);

// Interface de menu para operações relacionadas ao heap, utilizando a lista e o heap passados
void menuHeap(ListaPacientes *lista, Heap *heap);

#endif
