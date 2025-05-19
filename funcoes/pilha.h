#ifndef PILHA_H
#define PILHA_H

#include "paciente.h"

// Cria uma nova célula da pilha contendo o paciente e a operação realizada
Celula *start_Celula(Paciente *p, char op);

// Cria uma nova pilha vazia
Pilha *start_Pilha();

// Insere um elemento (paciente e operação) no topo da pilha
void push(Pilha *pilha, Paciente *p, char op);

// Remove o elemento do topo da pilha e retorna a célula removida
Celula *pop(Pilha *pilha);

// Desfaz a última ação registrada na pilha, restaurando a fila e/ou a lista
void desfazer(Fila* fila, Pilha* pilha, ListaPacientes *lista);

#endif
