// funcoes/fila.h
#ifndef FILA_H
#define FILA_H

#include "paciente.h"
#include "pilha.h"

//Struct da Efila (célula da fila)
typedef struct EFila {
    Paciente* paciente;
    struct EFila* prox;
} EFila;


//Struct da fila
typedef struct {
    EFila* head;
    EFila* tail;
    int qtd;
} Fila;

//Cria uma nova fila
Fila* criarFila();

//Enfileira um valor a fila
int enfileirar(Fila* fila, Paciente* paciente, Pilha* pilha, int flag);

//Desenfileira um valor da fila
Paciente* desenfileirar(Fila* fila, Pilha* pilha, int flag);

//Mostra a fila
void mostrarFila(Fila* fila);

//Libera a fila
void liberarFila(Fila* fila);

#endif