// funcoes/fila.h
#ifndef FILA_H
#define FILA_H

#include "paciente.h"

// Cria e retorna uma nova fila vazia
Fila *criarFila();

// Adiciona um paciente na fila, registra a operação na pilha se flag for 1
int enfileirar(Fila *fila, Paciente *paciente, Pilha *pilha, int flag);

// Remove e retorna o paciente que está no início da fila, registra operação na pilha se flag for 1
Paciente *desenfileirar(Fila *fila, Pilha *pilha, int flag);

// Exibe os pacientes atualmente na fila
void mostrarFila(Fila *fila);

// Interface de menu para operações relacionadas à fila, recebe referências das estruturas necessárias
void menuFila(ListaPacientes *lista, Fila *fila, Pilha *pilha);

#endif
