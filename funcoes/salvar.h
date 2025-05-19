// paciente.h
#ifndef SALVAR_H
#define SALVAR_H

void salvarPacientesArquivo(ListaPacientes *lista, const char *nomeArquivo);
void carregarPacientesArquivo(ListaPacientes *lista, const char *nomeArquivo);
void menuSalvar();
#endif