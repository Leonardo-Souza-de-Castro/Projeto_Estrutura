#ifndef PILHA_H
#define PILHA_H

#include "paciente.h"

Celula *start_Celula(Paciente *p, char op);

//Cria uma nova Pilha
Pilha *start_Pilha();

//Insere na pilha
void push(Pilha *pilha, Paciente *p, char op);

//remove da pilha
Celula *pop(Pilha *pilha);

//Desfaz a ultima ação realizada na fila
void desfazer(Fila* fila, Pilha* pilha, ListaPacientes *lista);

#endif