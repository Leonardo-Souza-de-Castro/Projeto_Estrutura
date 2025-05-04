// paciente.h
#ifndef PACIENTE_H
#define PACIENTE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_NOME 100

// Estrutura do paciente com campos básicos e ponteiros para lista duplamente encadeada
typedef struct Paciente {
    int id;
    char nome[TAM_NOME];
    int idade;
    char sintomas[200];
    struct Paciente* ant;
    struct Paciente* prox;
} Paciente;

// Lista de pacientes com ponteiro para o início, fim e contador
typedef struct ListaPacientes {
    Paciente* inicio;
    Paciente* fim;
    int qtd;
} ListaPacientes;

// Função que cria uma lista vazia
ListaPacientes* criar_lista();

// Cria e retorna um novo paciente com os dados informados
Paciente* criar_paciente(int id, const char* nome, int idade, const char* sintomas);

// Insere o paciente no fim da lista
void inserir_paciente(ListaPacientes* lista, Paciente* novo);

// Mostra os dados de todos os pacientes na lista
void listar_pacientes(ListaPacientes* lista);

// Procura e retorna o ponteiro para o paciente com o ID especificado
Paciente* buscar_paciente(ListaPacientes* lista, int id);

// Remove o paciente com o ID informado e retorna 1 se sucesso, 0 se não encontrou
int remover_paciente(ListaPacientes* lista, int id);

// Libera a memória da lista completamente
void liberar_lista(ListaPacientes* lista);

#endif
