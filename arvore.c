#include <stdio.h>              // Biblioteca padrão de entrada e saída
#include <stdlib.h>             // Biblioteca padrão para alocação dinâmica e funções gerais
#include "funcoes/fila.h"       // Inclui definição de fila (não usada diretamente aqui)
#include "funcoes/pilha.h"      // Inclui definição de pilha (não usada diretamente aqui)
#include "funcoes/arvore.h"     // Inclui definições da árvore
#include "funcoes/paciente.h"   // Inclui definições da estrutura Paciente

// Função que cria um novo nó da árvore com um paciente
EABB *criar_no(Paciente *p) {
    EABB *novo = malloc(sizeof(EABB));    // Aloca memória para o novo nó da árvore
    novo->dados = p;                      // Associa o paciente passado ao campo dados do nó
    novo->FilhoEsq = NULL;                // Inicializa o filho esquerdo como NULL (não tem filho ainda)
    novo->FilhoDir = NULL;                // Inicializa o filho direito como NULL (não tem filho ainda)
    return novo;                         // Retorna o novo nó criado
}

// Função que cria uma árvore vazia
ABB *criar_arvore() {
    ABB *a = malloc(sizeof(ABB));        // Aloca memória para a estrutura da árvore
    a->raiz = NULL;                      // Inicializa a raiz como NULL (árvore vazia)
    a->qtd = 0;                         // Inicializa a quantidade de nós com zero
    return a;                          // Retorna a árvore criada
}

// Insere um paciente na árvore ordenando pela idade
void inserir_por_idade(ABB *arvore, Paciente *valor) {
    EABB *novo = criar_no(valor);        // Cria um novo nó para o paciente
    EABB *anterior = NULL;                // Ponteiro para manter o nó anterior na busca
    EABB *atual = arvore->raiz;           // Começa a busca da raiz da árvore

    while (atual != NULL) {               // Enquanto não chegar numa folha (NULL)
        anterior = atual;                 // Atual nó vira o anterior
        if (valor->idade <= atual->dados->idade) {  // Se idade do paciente menor ou igual que a do nó atual
            atual = atual->FilhoEsq;     // Desce para o filho esquerdo
        } else {
            atual = atual->FilhoDir;     // Senão, desce para o filho direito
        }
    }

    if (anterior == NULL) {               // Se árvore estava vazia (raiz nula)
        arvore->raiz = novo;              // Novo nó vira a raiz da árvore
    } else if (valor->idade <= anterior->dados->idade) {  // Se paciente menor ou igual que nó anterior
        anterior->FilhoEsq = novo;       // Novo nó é filho esquerdo do anterior
    } else {
        anterior->FilhoDir = novo;       // Senão, filho direito do anterior
    }

    arvore->qtd++;                       // Incrementa contador de nós na árvore
}

// Insere um paciente na árvore ordenando pelo ano de entrada
void inserir_por_ano(ABB *arvore, Paciente *valor) {
    EABB *novo = criar_no(valor);        // Cria nó com paciente
    EABB *anterior = NULL;                // Nó anterior na busca
    EABB *atual = arvore->raiz;           // Começa na raiz

    while (atual != NULL) {               // Enquanto não chegar na folha
        anterior = atual;                 // Atual vira anterior
        if (valor->entrada->ano <= atual->dados->entrada->ano) {  // Compara ano da entrada
            atual = atual->FilhoEsq;     // Vai para filho esquerdo se menor ou igual
        } else {
            atual = atual->FilhoDir;     // Senão vai para filho direito
        }
    }

    if (anterior == NULL) {               // Se árvore vazia
        arvore->raiz = novo;              // Novo nó vira raiz
    } else if (valor->entrada->ano <= anterior->dados->entrada->ano) {  // Menor ou igual
        anterior->FilhoEsq = novo;       // Insere à esquerda
    } else {
        anterior->FilhoDir = novo;       // Insere à direita
    }

    arvore->qtd++;                       // Incrementa quantidade de nós
}

// Insere um paciente na árvore ordenando pelo mês de entrada
void inserir_por_mes(ABB *arvore, Paciente *valor) {
    EABB *novo = criar_no(valor);        // Cria novo nó
    EABB *anterior = NULL;                // Nó anterior
    EABB *atual = arvore->raiz;           // Inicia na raiz

    while (atual != NULL) {               // Percorre enquanto não nulo
        anterior = atual;                 // Atual vira anterior
        if (valor->entrada->mes <= atual->dados->entrada->mes) {   // Compara mês
            atual = atual->FilhoEsq;     // Vai para esquerda se menor ou igual
        } else {
            atual = atual->FilhoDir;     // Senão para direita
        }
    }

    if (anterior == NULL) {               // Se árvore vazia
        arvore->raiz = novo;              // Novo nó vira raiz
    } else if (valor->entrada->mes <= anterior->dados->entrada->mes) {  // Menor ou igual
        anterior->FilhoEsq = novo;       // Insere à esquerda
    } else {
        anterior->FilhoDir = novo;       // Insere à direita
    }

    arvore->qtd++;                       // Incrementa contador
}

// Insere um paciente na árvore ordenando pelo dia de entrada
void inserir_por_dia(ABB *arvore, Paciente *valor) {
    EABB *novo = criar_no(valor);        // Cria nó novo
    EABB *anterior = NULL;                // Guarda nó anterior
    EABB *atual = arvore->raiz;           // Começa na raiz

    while (atual != NULL) {               // Enquanto nó atual não for NULL
        anterior = atual;                 // Atual vira anterior
        if (valor->entrada->dia <= atual->dados->entrada->dia) {    // Compara dia
            atual = atual->FilhoEsq;     // Vai para filho esquerdo se menor ou igual
        } else {
            atual = atual->FilhoDir;     // Senão vai para filho direito
        }
    }

    if (anterior == NULL) {               // Se árvore vazia
        arvore->raiz = novo;              // Novo nó vira raiz
    } else if (valor->entrada->dia <= anterior->dados->entrada->dia) {  // Menor ou igual
        anterior->FilhoEsq = novo;       // Insere à esquerda
    } else {
        anterior->FilhoDir = novo;       // Insere à direita
    }

    arvore->qtd++;                       // Incrementa contador de nós
}

// Função para exibir os dados dos pacientes da árvore em ordem crescente
void exibir_em_ordem(EABB *raiz) {
    if (raiz != NULL) {                  // Se o nó atual não for NULL
        exibir_em_ordem(raiz->FilhoEsq); // Percorre subárvore esquerda primeiro

        // Exibe as informações do paciente no nó atual
        printf("Nome: %s\n", raiz->dados->nome);                // Mostra nome
        printf("RG: %s\n", raiz->dados->rg);                    // Mostra RG
        printf("Idade: %d\n", raiz->dados->idade);              // Mostra idade
        printf("Data de entrada: %02d/%02d/%04d\n",              // Mostra data entrada formatada
               raiz->dados->entrada->dia,
               raiz->dados->entrada->mes,
               raiz->dados->entrada->ano);
        printf("-----------------------\n");                      // Linha separadora

        exibir_em_ordem(raiz->FilhoDir); // Percorre subárvore direita por fim
    }
}

// Função para liberar a memória alocada da árvore, liberando todos os nós recursivamente
void liberar_arvore(EABB *raiz) {
    if (!raiz) return;                   // Se nó for NULL, retorna sem fazer nada
    liberar_arvore(raiz->FilhoEsq);     // Libera a subárvore esquerda primeiro
    liberar_arvore(raiz->FilhoDir);     // Depois libera a subárvore direita
    free(raiz);                        // Libera a memória do nó atual
}

// Função que exibe o menu de opções do gerenciador de atendimento
void menuTextoArvore() {
    printf("\n=== GERENCIADOR DE ATENDIMENTO MÉDICO ===\n"); // Título do menu
    printf("1. Pesquisar por idade\n");                      // Opção 1: pesquisar por idade
    printf("2. Pesquisar por ano de entrada\n");             // Opção 2: pesquisar por ano
    printf("3. Pesquisar por mes de entrada\n");             // Opção 3: pesquisar por mês
    printf("4. Pesquisar por dia de entrada\n");             // Opção 4: pesquisar por dia
    printf("0. Sair\n");                                      // Opção 0: sair do menu
    printf("Escolha: ");                                      // Pede para escolher uma opção
}

// Função que implementa o menu interativo da árvore
void menuArvore(ListaPacientes *lista){
    int opcao;                           // Variável para guardar a opção do usuário

    do {
        menuTextoArvore();               // Exibe o menu de opções
        scanf("%d", &opcao);             // Lê a opção escolhida pelo usuário
        getchar();                      // Consome o '\n' que fica no buffer após scanf

        switch (opcao) {
            case 1: {                   // Se opção for 1 - pesquisa por idade
                ABB *teste = criar_arvore();  // Cria árvore vazia para essa pesquisa
                ELista *aux = lista->inicio;  // Aponta para o início da lista de pacientes
                
                if (aux == NULL) {             // Se a lista estiver vazia
                    printf("A lista de pacientes está vazia.\n");  // Informa o usuário
                    break;                   // Sai do case 1
                }
                
                while (aux != NULL) {        // Enquanto houver pacientes na lista
                    inserir_por_idade(teste, aux->dados);  // Insere na árvore ordenando por idade
                    aux = aux->prox;         // Vai para o próximo paciente da lista
                }
                
                printf("Pacientes ordenados por idade:\n");  // Informa que vai mostrar dados ordenados
                exibir_em_ordem(teste->raiz);               // Exibe todos os pacientes em ordem crescente de idade
                liberar_arvore(teste->raiz);                 // Libera a memória da árvore temporária
                break;                                       // Sai do case 1
            }

            case 2: {                   // Se opção for 2 - pesquisa por ano de entrada
                ABB *teste = criar_arvore();               // Cria árvore vazia
                ELista *aux = lista->inicio;               // Começa na lista de pacientes
                
                if (aux == NULL) {                          // Se lista vazia
                    printf("A lista de pacientes está vazia.\n");  // Informa
                    break;                                 // Sai do case 2
                }
                
                while (aux != NULL) {                       // Para cada paciente
                    inserir_por_ano(teste, aux->dados);   // Insere na árvore ordenando por ano
                    aux = aux->prox;                       // Próximo paciente
                }
                
                printf("Pacientes ordenados por iano de entrada:\n");  // Imprime título da listagem
                exibir_em_ordem(teste->raiz);                         // Exibe em ordem crescente pelo ano
                liberar_arvore(teste->raiz);                           // Libera árvore temporária
                break;                                                 // Sai do case 2
            }

            case 3: {                   // Se opção for 3 - pesquisa por mês de entrada
                ABB *teste = criar_arvore();           // Cria árvore vazia
                ELista *aux = lista->inicio;           // Aponta início da lista
                
                if (aux == NULL) {                      // Se lista vazia
                    printf("A lista de pacientes está vazia.\n");  // Informa
                    break;                             // Sai do case 3
                }
                
                while (aux != NULL) {                   // Para cada paciente
                    inserir_por_mes(teste, aux->dados);   // Insere na árvore ordenando por mês
                    aux = aux->prox;                   // Próximo paciente
                }
                
                printf("Pacientes ordenados por mes de entrada:\n");  // Imprime título
                exibir_em_ordem(teste->raiz);                         // Exibe em ordem crescente por mês
                liberar_arvore(teste->raiz);                           // Libera árvore
                break;                                                 // Sai do case 3
            }

            case 4: {                   // Se opção for 4 - pesquisa por dia de entrada
                ABB *teste = criar_arvore();           // Cria árvore vazia
                ELista *aux = lista->inicio;           // Aponta início da lista
                
                if (aux == NULL) {                      // Se lista vazia
                    printf("A lista de pacientes está vazia.\n");  // Informa
                    break;                             // Sai do case 4
                }
                
                while (aux != NULL) {                   // Para cada paciente da lista
                    inserir_por_dia(teste, aux->dados);   // Insere ordenando por dia
                    aux = aux->prox;                   // Próximo paciente
                }
                
                printf("Pacientes ordenados por dia de entrada:\n");  // Título do resultado
                exibir_em_ordem(teste->raiz);                         // Exibe em ordem crescente por dia
                liberar_arvore(teste->raiz);                           // Libera árvore
                break;                                                 // Sai do case 4
            }

            case 0:                    // Se opção for 0 - sair do menu
                printf("Saindo do menu da árvore...\n");    // Mensagem de saída
                break;                                     // Sai do loop e da função

            default:                   // Se opção inválida
                printf("Opção inválida, tente novamente.\n");  // Alerta usuário
        }

    } while (opcao != 0);               // Repete até o usuário escolher sair (0)
}
