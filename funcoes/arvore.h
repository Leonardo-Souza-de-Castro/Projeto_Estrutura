#ifndef ARVORE_H
#define ARVORE_H

#include "paciente.h"  // Inclui a definição da estrutura Paciente, usada nas funções da árvore

// Cria um novo nó da árvore binária de busca com o paciente fornecido
EABB *criar_no(Paciente *p);

// Inicializa e retorna uma nova árvore binária de busca vazia
ABB *criar_arvore();

// Insere um paciente na árvore ordenando os nós pela idade do paciente
void inserir_por_idade(ABB *arvore, Paciente *valor);

// Insere um paciente na árvore ordenando os nós pelo ano do cadastro
void inserir_por_ano(ABB *arvore, Paciente *valor);

// Insere um paciente na árvore ordenando os nós pelo mês do cadastro
void inserir_por_mes(ABB *arvore, Paciente *valor);

// Insere um paciente na árvore ordenando os nós pelo dia do cadastro
void inserir_por_dia(ABB *arvore, Paciente *valor);

// Exibe os nós da árvore em ordem (in-order traversal)
void exibir_em_ordem(EABB *raiz);

// Menu para pesquisa de pacientes usando árvore binária
void menuArvore(ListaPacientes *lista);

#endif
