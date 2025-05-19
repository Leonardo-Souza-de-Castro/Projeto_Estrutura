// funcoes/fila.h
#ifndef FILA_H
#define FILA_H
#include "paciente.h"

//Cria uma nova fila
Fila *criarFila();

//Enfileira um valor a fila
int enfileirar(Fila *fila, Paciente *paciente, Pilha *pilha, int flag);

//Desenfileira um valor da fila
Paciente *desenfileirar(Fila *fila, Pilha *pilha, int flag);

//Mostra a fila
void mostrarFila(Fila *fila);

void menuFila(ListaPacientes *lista, Fila *fila, Pilha *pilha);

#endif