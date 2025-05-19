#include <stdio.h>
#include <stdlib.h>
#include "funcoes/paciente.h"

void salvarPacientesArquivo(ListaPacientes *lista) {
    FILE *arquivo = fopen("Dados.txt", "w");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo para escrita");
        return;
    }

    ELista *atual = lista->inicio;
    while (atual != NULL) {
        Paciente *p = atual->dados;
        fprintf(arquivo, "%s;%s;%d;%d;%d;%d\n",
                p->nome, p->rg, p->idade,
                p->entrada->dia, p->entrada->mes, p->entrada->ano);
        atual = atual->prox;
    }

    fclose(arquivo);
    printf("Pacientes salvos em '%s'\n", "Dados.txt");
}

void carregarPacientesArquivo(ListaPacientes *lista) {
    FILE *arquivo = fopen("Dados.txt", "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo para leitura");
        return;
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo)) {
        Paciente *p = malloc(sizeof(Paciente));
        p->entrada = malloc(sizeof(Data));

        sscanf(linha, "%99[^;];%19[^;];%d;%d;%d;%d",
               p->nome, p->rg, &p->idade,
               &p->entrada->dia, &p->entrada->mes, &p->entrada->ano);

        // Insere no início (para manter a ordem de inserção conforme o PDF)
        ELista *novo = malloc(sizeof(ELista));
        novo->dados = p;
        novo->prox = lista->inicio;
        lista->inicio = novo;
        lista->qtd++;
    }

    fclose(arquivo);
    printf("Pacientes carregados de '%s'\n", "Dados.txt");
}

void menuTextoSalvar(){
    printf("\n=== GERENCIADOR DE ATENDIMENTO MÉDICO ===\n");
    printf("1. Salvar dados\n");
    printf("2. Carregar dados\n");
    printf("0. Sair\n");
    printf("Escolha: ");
}

void menuSalvar(ListaPacientes *lista){
    int opcao;
    do {
        menuTextoSalvar();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                salvarPacientesArquivo(lista);
                break;
            case 2:
                carregarPacientesArquivo(lista);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);
}