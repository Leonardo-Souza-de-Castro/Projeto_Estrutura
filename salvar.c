#include <stdio.h>
#include <stdlib.h>
#include "funcoes/paciente.h"

// Função para salvar a lista de pacientes em arquivo texto "Dados.txt"
void salvarPacientesArquivo(ListaPacientes *lista) {
    FILE *arquivo = fopen("Dados.txt", "w");    // Abre o arquivo para escrita (apaga conteúdo antigo)
    if (arquivo == NULL) {                       // Se não conseguiu abrir, exibe erro e retorna
        perror("Erro ao abrir arquivo para escrita");
        return;
    }

    ELista *atual = lista->inicio;               // Pega o início da lista de pacientes
    while (atual != NULL) {                       // Percorre toda a lista enquanto houver pacientes
        Paciente *p = atual->dados;               // Aponta para o paciente atual
        // Escreve no arquivo as informações do paciente, separadas por ponto e vírgula
        fprintf(arquivo, "%s;%s;%d;%d;%d;%d\n",
                p->nome, p->rg, p->idade,
                p->entrada->dia, p->entrada->mes, p->entrada->ano);
        atual = atual->prox;                      // Passa para o próximo paciente da lista
    }

    fclose(arquivo);                              // Fecha o arquivo após escrever todos pacientes
    printf("Pacientes salvos em '%s'\n", "Dados.txt");  // Confirmação para o usuário
}

// Função para carregar pacientes do arquivo "Dados.txt" para a lista em memória
void carregarPacientesArquivo(ListaPacientes *lista) {
    FILE *arquivo = fopen("Dados.txt", "r");    // Abre o arquivo para leitura
    if (arquivo == NULL) {                       // Se não conseguir abrir, exibe erro e retorna
        perror("Erro ao abrir arquivo para leitura");
        return;
    }

    char linha[256];                             // Buffer para ler uma linha do arquivo
    while (fgets(linha, sizeof(linha), arquivo)) {  // Lê linha a linha até o fim do arquivo
        Paciente *p = malloc(sizeof(Paciente));     // Aloca memória para um novo paciente
        p->entrada = malloc(sizeof(Data));           // Aloca memória para a data de entrada

        // Faz o parsing da linha, extraindo campos separados por ';'
        sscanf(linha, "%99[^;];%19[^;];%d;%d;%d;%d",
               p->nome, p->rg, &p->idade,
               &p->entrada->dia, &p->entrada->mes, &p->entrada->ano);

        // Cria um novo elemento para a lista encadeada e insere no início
        ELista *novo = malloc(sizeof(ELista));
        novo->dados = p;                          // Aponta para o paciente recém criado
        novo->prox = lista->inicio;               // O próximo do novo elemento será o atual início
        lista->inicio = novo;                      // Atualiza o início da lista para o novo elemento
        lista->qtd++;                             // Incrementa a quantidade de pacientes na lista
    }

    fclose(arquivo);                             // Fecha o arquivo após ler todos os pacientes
    printf("Pacientes carregados de '%s'\n", "Dados.txt");  // Confirmação para o usuário
}

// Função que exibe o menu de opções de salvar/carregar dados
void menuTextoSalvar(){
    printf("\n=== GERENCIADOR DE ATENDIMENTO MÉDICO ===\n");
    printf("1. Salvar dados\n");
    printf("2. Carregar dados\n");
    printf("0. Sair\n");
    printf("Escolha: ");
}

// Função que controla o menu de salvar e carregar dados
void menuSalvar(ListaPacientes *lista){
    int opcao;
    do {
        menuTextoSalvar();                      // Exibe as opções do menu
        scanf("%d", &opcao);                    // Lê a opção escolhida pelo usuário

        switch (opcao) {
            case 1:
                salvarPacientesArquivo(lista); // Chama função para salvar os pacientes
                break;
            case 2:
                carregarPacientesArquivo(lista); // Chama função para carregar pacientes do arquivo
                break;
            case 0:
                printf("Saindo...\n");          // Mensagem ao sair do menu
                break;
            default:
                printf("Opção inválida.\n");    // Caso o usuário digite opção fora do menu
        }
    } while (opcao != 0);                      // Repete o menu até o usuário escolher sair
}
