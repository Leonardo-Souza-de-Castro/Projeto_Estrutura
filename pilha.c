#include <stdio.h>
#include <stdlib.h>
#include "funcoes/pilha.h"
#include "funcoes/fila.h"

Celula *start_Celula(char valor)
{
    Celula *nova = malloc(sizeof(Celula));
    nova->anterior = NULL;
    nova->proximo = NULL;
    nova->valor = valor;
    return nova;
}

Pilha *start_Pilha()
{
    Pilha *Pilha = malloc(sizeof(Pilha));
    Pilha->qtde = 0;
    Pilha->top = NULL;
    return Pilha;
}

void push(Pilha *Pilha, char valor)
{
    Celula *nova = start_Celula(valor);
    if (Pilha->qtde != 0)
    {
        nova->proximo = Pilha->top;
        Pilha->top->anterior = nova;
    }
    Pilha->top = nova;
    Pilha->qtde++;
}

char pop(Pilha *Pilha)
{
    if (Pilha->qtde > 0)
    {
        char valor = Pilha->top->valor;
        Celula *top = Pilha->top;
        Pilha->top = Pilha->top->proximo;
        if (Pilha->top != NULL)
            Pilha->top->anterior = NULL;
        Pilha->qtde--;
        free(top);
        return valor;
    }
    else
    {
        return 'x';
    }
}