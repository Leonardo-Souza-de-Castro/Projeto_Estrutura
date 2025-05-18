#ifndef PILHA_H
#define PILHA_H

typedef struct Celula
{
    struct Celula *anterior;
    struct Celula *proximo;
    char valor;
} Celula;

typedef struct
{
    Celula *top;
    int qtde;
} Pilha;

#endif