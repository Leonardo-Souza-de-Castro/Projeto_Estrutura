// paciente.h
#ifndef PACIENTE_H
#define PACIENTE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_NOME 100

// Estrutura do paciente com campos básicos e ponteiros para lista duplamente encadeada
typedef struct Paciente {
    char rg[15];
    char nome[TAM_NOME];
    int idade;
    Data* entrada;
} Paciente;

typedef struct ELista {
    Paciente* dados;
    struct ELista* prox;
} ELista;

typedef struct Data {
    int dia;
    int mes;
    int ano;
} Data;

// Lista de pacientes com ponteiro para o início, fim e contador
typedef struct ListaPacientes {
    ELista* inicio;
    int qtd;
} ListaPacientes;

// Função que cria uma lista vazia
ListaPacientes* criarLista();

Data* criarData(int dia, int mes, int ano);

// Cria e retorna um novo paciente com os dados informados
int cadastrarPaciente(ListaPacientes* lista, char nome[], int idade, char rg[], int dia, int mes, int ano);

Paciente* consultarPaciente(ListaPacientes* lista);

// Mostra os dados de todos os pacientes na lista
void mostrarLista(ListaPacientes* lista);

// Procura e retorna o ponteiro para o paciente com o ID especificado
Paciente* consultarPaciente(ListaPacientes* lista);

// Remove o paciente com o ID informado e retorna 1 se sucesso, 0 se não encontrou
int removerPaciente(ListaPacientes* lista, char rg[]) ;

// Atualiza as informações do paciente
int atualizarPaciente(ListaPacientes* lista, char rg[], char novoNome[], int novaIdade);

// Libera a memória da lista completamente
void liberar_lista(ListaPacientes* lista);

#endif
