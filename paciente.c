#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes/paciente.h"

// Cria uma nova lista vazia
ListaPacientes *criarLista() {
    ListaPacientes *lista = (ListaPacientes*) malloc(sizeof(ListaPacientes));
    if (lista != NULL) {
        lista->inicio = NULL;
        lista->qtd = 0;
    }
    return lista;
}

// Cria uma nova data
Data *criarData(int dia, int mes, int ano) {
    Data *novaData = (Data*) malloc(sizeof(Data));
    if (novaData != NULL) {
        novaData->dia = dia;
        novaData->mes = mes;
        novaData->ano = ano;
    }
    return novaData;
}

Paciente *criarPaciente(char nome[], char rg[], int idade, int dia, int mes, int ano) {
    Paciente *p = malloc(sizeof(Paciente));
    if (!p) return NULL;

    strncpy(p->nome, nome, sizeof(p->nome));
    strncpy(p->rg, rg, sizeof(p->rg));
    p->nome[sizeof(p->nome) - 1] = '\0';  // garante terminação
    p->rg[sizeof(p->rg) - 1] = '\0';

    p->idade = idade;

    p->entrada = malloc(sizeof(Data));
    if (!p->entrada) {
        free(p);
        return NULL;
    }

    p->entrada->dia = dia;
    p->entrada->mes = mes;
    p->entrada->ano = ano;

    return p;
}

// Cria um novo paciente e insere no início da lista
int cadastrarPaciente(ListaPacientes *lista, char nome[], int idade, char rg[], int dia, int mes, int ano) {
    if (lista == NULL) return 0;  // Protege contra ponteiro nulo

    ELista *novo = (ELista *) malloc(sizeof(ELista));
    if (novo == NULL) return 0;

    novo->dados = criarPaciente(nome, rg, idade, dia, mes, ano);
    if (novo->dados == NULL) {
        free(novo);
        return 0;
    }

    novo->prox = NULL;

    if (lista->inicio == NULL) {
        // Lista está vazia
        lista->inicio = novo;
    } else {
        // Percorre até o final da lista
        ELista *atual = lista->inicio;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo;
    }

    // Atualiza contador de pacientes
    lista->qtd++;

    return 1;
}

// Mostra todos os pacientes da lista
void mostrarLista(ListaPacientes *lista) {
    if (lista == NULL || lista->inicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    ELista *aux = lista->inicio;
    while (aux != NULL) {
        printf("Nome: %s\n", aux->dados->nome);
        printf("Idade: %d\n", aux->dados->idade);
        printf("RG: %s\n", aux->dados->rg);
        printf("Data de entrada: %02d/%02d/%04d\n\n",
               aux->dados->entrada->dia,
               aux->dados->entrada->mes,
               aux->dados->entrada->ano);
        aux = aux->prox;
    }
}

// Consulta um paciente pelo RG
Paciente *consultarPaciente(ListaPacientes *lista, char identidade[]) {
    char rg[15];
    if (identidade == NULL)
    {
        printf("Digite seu RG: ");
        fgets(rg, sizeof(rg), stdin);
        rg[strcspn(rg, "\n")] = 0;
    }else{
        strncpy(rg, identidade, sizeof(rg));
    }
    
    if (lista == NULL){
        return NULL;
    }

    ELista *aux = lista->inicio;
    while (aux != NULL) {
        if (strcmp(aux->dados->rg, rg) == 0) {
            Paciente* pacienteLocalizado = criarPaciente(aux->dados->nome, aux->dados->rg, aux->dados->idade, aux->dados->entrada->dia, aux->dados->entrada->mes, aux->dados->entrada->ano);
            return pacienteLocalizado;
        }
        aux = aux->prox;
    }

    printf("Paciente com RG %s não encontrado.\n", rg);
}

// Atualiza os dados de um paciente (encontrado pelo RG)
int atualizarPaciente(ListaPacientes *lista, char rg[], char novoNome[], int novaIdade) {
    if (lista == NULL) return 0;

    ELista *aux = lista->inicio;
    while (aux != NULL) {
        if (strcmp(aux->dados->rg, rg) == 0) {
            strcpy(aux->dados->nome, novoNome);
            aux->dados->idade = novaIdade;
            return 1;
        }
        aux = aux->prox;
    }

    return 0; // não encontrado
}

// Remove paciente pelo RG
int removerPaciente(ListaPacientes *lista, char rg[]) {
    if (lista == NULL || lista->inicio == NULL) return 0;

    ELista *atual = lista->inicio;
    ELista *anterior = NULL;

    while (atual != NULL && strcmp(atual->dados->rg, rg) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) return 0; // paciente não encontrado

    if (anterior == NULL) {
        lista->inicio = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    free(atual->dados->entrada);
    free(atual);
    lista->qtd--;

    return 1;
}

void menuTextoPaciente() {
    printf("\n=== GERENCIADOR DE ATENDIMENTO MÉDICO ===\n");
    printf("1. Cadastro de novo paciente\n");
    printf("2. Consultar paciente cadastrado\n");
    printf("3. Mostrar todos os pacientes cadastrados\n");
    printf("4. Atualizar dados do paciente\n");
    printf("5. Remover paciente\n");
    printf("0. Sair\n");
    printf("Escolha: ");
}

void menuPacientes(ListaPacientes* lista){
    int opcao;
    do {
        menuTextoPaciente();
        scanf("%d", &opcao);
        getchar();

        char nome[TAM_NOME];
        int idade;
        char rg[15];
        char nascimento[11];
        char *teste;
        int dia;
        int mes;
        int ano;

        switch (opcao) {
            case 1:
                printf("Digite seu nome: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0;
                
                printf("Digite sua idade: ");
                scanf("%d", &idade);
                getchar();
                
                printf("Digite seu RG: ");
                fgets(rg, sizeof(rg), stdin);
                rg[strcspn(rg, "\n")] = 0;
                
                printf("Digite sua data de registro (ex: DD/MM/YYYY): ");
                fgets(nascimento, sizeof(nascimento), stdin);
                nascimento[strcspn(nascimento, "\n")] = 0;

                teste = strtok(nascimento, "/");
                if (teste != NULL) dia = atoi(teste);

                teste = strtok(NULL, "/");
                if (teste != NULL) mes = atoi(teste);

                teste = strtok(NULL, "/");
                if (teste != NULL) ano = atoi(teste);
                
                cadastrarPaciente(lista, nome, idade, rg, dia, mes, ano);
                break;
            case 2:{
                Paciente *p = consultarPaciente(lista, NULL);
                if (p != NULL) {
                    printf("\nPaciente encontrado:\n");
                    printf("Nome: %s\n", p->nome);
                    printf("Idade: %d\n", p->idade);
                    printf("RG: %s\n", p->rg);
                    printf("Data de entrada: %02d/%02d/%04d\n",
                        p->entrada->dia,
                        p->entrada->mes,
                        p->entrada->ano);
                    free(p->entrada);
                    free(p);
                } else {
                    printf("Paciente não encontrado.\n");
                }
                    break;
                }
            case 3:
                mostrarLista(lista);
                break;
            case 4:
                printf("Digite seu RG: ");
                fgets(rg, sizeof(rg), stdin);
                rg[strcspn(rg, "\n")] = 0;
                
                printf("Digite seu nome: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0;

                printf("Digite sua idade: ");
                scanf("%d", &idade);

                atualizarPaciente(lista, rg, nome, idade);
                break;
            case 5:

                printf("Digite seu RG: ");
                fgets(rg, sizeof(rg), stdin);
                rg[strcspn(rg, "\n")] = 0;

                removerPaciente(lista, rg);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);
}
