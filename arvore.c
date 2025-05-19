#include <stdio.h>
#include <stdlib.h>
#include "funcoes/fila.h"
#include "funcoes/pilha.h"
#include "funcoes/arvore.h"
#include "funcoes/paciente.h"

//Cria um novo no da arvore, com os dados do paciente e os filhos Nulos
EABB *criar_no(Paciente *p) {
    EABB *novo = malloc(sizeof(EABB));
    novo->dados = p;
    novo->FilhoEsq = NULL;
    novo->FilhoDir = NULL;
    return novo;
}

//Inicializa uma nova arvore vazia
ABB *criar_arvore() {
    ABB *a = malloc(sizeof(ABB));
    a->raiz = NULL;
    a->qtd = 0;
    return a;
}

//Insere um novo nó na arvore ordenado pela idade
void inserir_por_idade(ABB *arvore, Paciente *valor) {
    EABB *novo = criar_no(valor); 
    EABB *anterior = NULL;
    EABB *atual = arvore->raiz;  

    while (atual != NULL) { //Percore a arvore
        anterior = atual;
        if (valor->idade <= atual->dados->idade) { //Valida se idade a ser inserida é menor ou igual a que esta contida no nó atual da arvore
            atual = atual->FilhoEsq; //Se for, atual vai se tornar seu filho esquerdo
        } else {
            atual = atual->FilhoDir; // Se não for, atual vai se tornar seu filho direito
        }
    }

    if (anterior == NULL) { //Se depois disso tudo anterior for nulo então a arvore ta vazia e novo se torna a raiz
        arvore->raiz = novo;
    } else if (valor->idade <= anterior->dados->idade) {//Valida se a idade inserida pe menor ou igual a que esta contida no nó anterior
        anterior->FilhoEsq = novo; //Se for, o filho esquerdo de anterior vai ser o novo
    } else {
        anterior->FilhoDir = novo;//Se não for, o filho direito de anterior é o novo
    }

    arvore->qtd++; //Incrementa o contador
}

//Insere um novo nó na arvore ordenado pelo ano de entrada
//Segue a mesma lógica da idade porém compara o ano
void inserir_por_ano(ABB *arvore, Paciente *valor) {
    EABB *novo = criar_no(valor);
    EABB *anterior = NULL;
    EABB *atual = arvore->raiz;

    while (atual != NULL) {
        anterior = atual;
        if (valor->entrada->ano <= atual->dados->entrada->ano) {
            atual = atual->FilhoEsq;
        } else {
            atual = atual->FilhoDir;
        }
    }

    if (anterior == NULL) {
        arvore->raiz = novo;
    } else if (valor->entrada->ano <= anterior->dados->entrada->ano) {
        anterior->FilhoEsq = novo;
    } else {
        anterior->FilhoDir = novo;
    }

    arvore->qtd++;
}

//Insere um novo nó na arvore ordenado pelo anmes de entrada
//Segue a mesma lógica da idade porém compara o mes
void inserir_por_mes(ABB *arvore, Paciente *valor) {
    EABB *novo = criar_no(valor);
    EABB *anterior = NULL;
    EABB *atual = arvore->raiz;

    while (atual != NULL) {
        anterior = atual;
        if (valor->entrada->mes <= atual->dados->entrada->mes) {
            atual = atual->FilhoEsq;
        } else {
            atual = atual->FilhoDir;
        }
    }

    if (anterior == NULL) {
        arvore->raiz = novo;
    } else if (valor->entrada->mes <= anterior->dados->entrada->mes) {
        anterior->FilhoEsq = novo;
    } else {
        anterior->FilhoDir = novo;
    }

    arvore->qtd++;
}

//Insere um novo nó na arvore ordenado pelo dia de entrada
//Segue a mesma lógica da idade porém compara o dia
void inserir_por_dia(ABB *arvore, Paciente *valor) {
    EABB *novo = criar_no(valor);
    EABB *anterior = NULL;
    EABB *atual = arvore->raiz;

    while (atual != NULL) {
        anterior = atual;
        if (valor->entrada->dia <= atual->dados->entrada->dia) {
            atual = atual->FilhoEsq;
        } else {
            atual = atual->FilhoDir;
        }
    }

    if (anterior == NULL) {
        arvore->raiz = novo;
    } else if (valor->entrada->dia <= anterior->dados->entrada->dia) {
        anterior->FilhoEsq = novo;
    } else {
        anterior->FilhoDir = novo;
    }

    arvore->qtd++;
}

//Percore a arvore pela raiz e exibi os nós ordenados
void exibir_em_ordem(EABB *raiz) {
    if (raiz != NULL) {
        exibir_em_ordem(raiz->FilhoEsq);

        printf("Nome: %s\n", raiz->dados->nome);
        printf("RG: %s\n", raiz->dados->rg);
        printf("Idade: %d\n", raiz->dados->idade);
        printf("Data de entrada: %02d/%02d/%04d\n",
               raiz->dados->entrada->dia,
               raiz->dados->entrada->mes,
               raiz->dados->entrada->ano);
        printf("-----------------------\n");

        exibir_em_ordem(raiz->FilhoDir);
    }
}

void liberar_arvore(EABB *raiz) {
    if (!raiz) return;
    liberar_arvore(raiz->FilhoEsq);
    liberar_arvore(raiz->FilhoDir);
    free(raiz);
}

//Print das infos do menu
void menuTextoArvore() {
    printf("\n=== GERENCIADOR DE ATENDIMENTO MÉDICO ===\n");
    printf("1. Pesquisar por idade\n");
    printf("2. Pesquisar por ano de entrada\n");
    printf("3. Pesquisar por mes de entrada\n");
    printf("4. Pesquisar por dia de entrada\n");
    printf("0. Sair\n");
    printf("Escolha: ");
}

//Valida a opção selecionada e chama a função correspondente
void menuArvore(ListaPacientes *lista){
    int opcao;
    do {
        menuTextoArvore();
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: {

                ABB *teste = criar_arvore();
                ELista *aux = lista->inicio;
                
                if (aux == NULL) {
                    printf("A lista de pacientes está vazia.\n");
                    break;
                }
                
                while (aux != NULL) {
                    inserir_por_idade(teste, aux->dados);
                    aux = aux->prox;
                }
                
                printf("Pacientes ordenados por idade:\n");
                exibir_em_ordem(teste->raiz);
                liberar_arvore(teste->raiz);
                break;
            }

            case 2: {

                ABB *teste = criar_arvore();
                ELista *aux = lista->inicio;
                
                if (aux == NULL) {
                    printf("A lista de pacientes está vazia.\n");
                    break;
                }
                
                while (aux != NULL) {
                    inserir_por_ano(teste, aux->dados);
                    aux = aux->prox;
                }
                
                printf("Pacientes ordenados por iano de entrada:\n");
                exibir_em_ordem(teste->raiz);
                liberar_arvore(teste->raiz);
                break;
            }
                case 3: {

                    ABB *teste = criar_arvore();
                    ELista *aux = lista->inicio;
                    
                    if (aux == NULL) {
                        printf("A lista de pacientes está vazia.\n");
                        break;
                    }
                    
                    while (aux != NULL) {
                        inserir_por_mes(teste, aux->dados);
                        aux = aux->prox;
                    }
                    
                    printf("Pacientes ordenados por mes de entrada:\n");
                    exibir_em_ordem(teste->raiz);
                    liberar_arvore(teste->raiz);
                    break;
                }
            case 4: {

                ABB *teste = criar_arvore();
                ELista *aux = lista->inicio;
                
                if (aux == NULL) {
                    printf("A lista de pacientes está vazia.\n");
                    break;
                }
                
                while (aux != NULL) {
                    inserir_por_dia(teste, aux->dados);
                    aux = aux->prox;
                }
                
                printf("Pacientes ordenados por dia:\n");
                exibir_em_ordem(teste->raiz);
                liberar_arvore(teste->raiz);
                break;
            }
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);
}