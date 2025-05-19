#ifndef SALVAR_H
#define SALVAR_H

#include "paciente.h"

// Salva os dados dos pacientes da lista em um arquivo de texto
void salvarPacientesArquivo(ListaPacientes *lista);

// Carrega os dados dos pacientes de um arquivo de texto para a lista
void carregarPacientesArquivo(ListaPacientes *lista);

// Exibe um menu com opções para salvar ou carregar os dados dos pacientes
void menuSalvar(ListaPacientes *lista);

#endif
