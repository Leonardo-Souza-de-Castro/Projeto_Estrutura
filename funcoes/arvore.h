#ifndef ARVORE_H
#define ARVORE_H

typedef struct EABB {
    Paciente dados;
    struct EABB* FilhoEsq;
    struct EABB* FilhoDir;
} EABB;

typedef struct {
    EABB* Raiz;
    int qtd;
} ABB;

#endif