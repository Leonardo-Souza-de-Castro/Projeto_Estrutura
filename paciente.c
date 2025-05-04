#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "paciente.h"

// Cria uma nova lista vazia
Lista* criarLista() {
    Lista* lista = (Lista*) malloc(sizeof(Lista));
    if (lista != NULL) {
        lista->inicio = NULL;
        lista->qtd = 0;
    }
    return lista;
}

// Cria uma nova data
Data* criarData(int dia, int mes, int ano) {
    Data* novaData = (Data*) malloc(sizeof(Data));
    if (novaData != NULL) {
        novaData->dia = dia;
        novaData->mes = mes;
        novaData->ano = ano;
    }
    return novaData;
}

// Cria um novo paciente e insere no início da lista
int cadastrarPaciente(Lista* lista, char nome[], int idade, char rg[], int dia, int mes, int ano) {
    if (lista == NULL) return 0;

    ELista* novo = (ELista*) malloc(sizeof(ELista));
    if (novo == NULL) return 0;

    novo->dados.entrada = criarData(dia, mes, ano);
    if (novo->dados.entrada == NULL) {
        free(novo);
        return 0;
    }

    strcpy(novo->dados.nome, nome);
    strcpy(novo->dados.rg, rg);
    novo->dados.idade = idade;

    novo->prox = lista->inicio;
    lista->inicio = novo;
    lista->qtd++;

    return 1;
}

// Mostra todos os pacientes da lista
void mostrarLista(Lista* lista) {
    if (lista == NULL || lista->inicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    ELista* aux = lista->inicio;
    while (aux != NULL) {
        printf("Nome: %s\n", aux->dados.nome);
        printf("Idade: %d\n", aux->dados.idade);
        printf("RG: %s\n", aux->dados.rg);
        printf("Data de entrada: %02d/%02d/%04d\n\n",
               aux->dados.entrada->dia,
               aux->dados.entrada->mes,
               aux->dados.entrada->ano);
        aux = aux->prox;
    }
}

// Consulta um paciente pelo RG
void consultarPaciente(Lista* lista, char rg[]) {
    if (lista == NULL) return;

    ELista* aux = lista->inicio;
    while (aux != NULL) {
        if (strcmp(aux->dados.rg, rg) == 0) {
            printf("Paciente encontrado:\n");
            printf("Nome: %s\n", aux->dados.nome);
            printf("Idade: %d\n", aux->dados.idade);
            printf("RG: %s\n", aux->dados.rg);
            printf("Data de entrada: %02d/%02d/%04d\n",
                   aux->dados.entrada->dia,
                   aux->dados.entrada->mes,
                   aux->dados.entrada->ano);
            return;
        }
        aux = aux->prox;
    }

    printf("Paciente com RG %s não encontrado.\n", rg);
}

// Atualiza os dados de um paciente (encontrado pelo RG)
int atualizarPaciente(Lista* lista, char rg[], char novoNome[], int novaIdade) {
    if (lista == NULL) return 0;

    ELista* aux = lista->inicio;
    while (aux != NULL) {
        if (strcmp(aux->dados.rg, rg) == 0) {
            strcpy(aux->dados.nome, novoNome);
            aux->dados.idade = novaIdade;
            return 1;
        }
        aux = aux->prox;
    }

    return 0; // não encontrado
}

// Remove paciente pelo RG
int removerPaciente(Lista* lista, char rg[]) {
    if (lista == NULL || lista->inicio == NULL) return 0;

    ELista* atual = lista->inicio;
    ELista* anterior = NULL;

    while (atual != NULL && strcmp(atual->dados.rg, rg) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) return 0; // paciente não encontrado

    if (anterior == NULL) {
        lista->inicio = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    free(atual->dados.entrada);
    free(atual);
    lista->qtd--;

    return 1;
}
