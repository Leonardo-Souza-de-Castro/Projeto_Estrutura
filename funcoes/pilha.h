#ifndef PILHA_H
#define PILHA_H
#include "paciente.h"
#include "fila.h"

//Struct da célula da pilha
typedef struct Celula
{
    struct Celula *anterior;
    struct Celula *proximo;
    Paciente *registro;
    char operacao;
} Celula;

//Struct da pilha
typedef struct
{
    Celula *top;
    int qtde;
} Pilha;


//Insere na pilha
void push(Pilha *Pilha, Paciente *p, char op);

//remove da pilha
Celula *pop(Pilha *pilha) ;

//Desfaz a ultima ação realizada na fila
void desfazer(Fila *fila, Pilha *pilha);

#endif