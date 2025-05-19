// paciente.h
#ifndef PACIENTE_H
#define PACIENTE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_NOME 100

//Struct de data
typedef struct Data {
    int dia;
    int mes;
    int ano;
} Data;

// Estrutura do paciente com campos básicos 
typedef struct Paciente {
    char rg[15];
    char nome[TAM_NOME];
    int idade;
    Data *entrada;
} Paciente;

//Celula da lista contendo o paciente e o ponteiro do proximo caso
typedef struct ELista {
    Paciente *dados;
    struct ELista *prox;
} ELista;

// Lista de pacientes com ponteiro para o início, fim e contador
typedef struct ListaPacientes {
    ELista *inicio;
    int qtd;
} ListaPacientes;

// Função que cria uma lista vazia
ListaPacientes *criarLista();

//Cria a data para inserir no Cadastro de Paciente
Data *criarData(int dia, int mes, int ano);

// Cria e retorna um novo paciente com os dados informados
int cadastrarPaciente(ListaPacientes* lista, char nome[], int idade, char rg[], int dia, int mes, int ano);

//Consulta um paciente na lista pelo RG
Paciente *consultarPaciente(ListaPacientes *lista, char identidade[]) ;

// Mostra os dados de todos os pacientes na lista
void mostrarLista(ListaPacientes *lista);

// Remove o paciente com o RG informado e retorna 1 se sucesso, 0 se não encontrou
int removerPaciente(ListaPacientes *lista, char rg[]) ;

// Atualiza as informações do paciente
int atualizarPaciente(ListaPacientes *lista, char rg[], char novoNome[], int novaIdade);

#endif
