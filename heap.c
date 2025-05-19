// Inclui biblioteca padrão de entrada e saída, usada para printf e scanf
#include <stdio.h>
// Inclui biblioteca padrão para alocação dinâmica de memória (malloc, free)
#include <stdlib.h>
// Inclui o arquivo de cabeçalho heap.h que contém a definição da estrutura Heap e funções
#include "funcoes/heap.h"
// Inclui fila.h, pode ser usado em interações futuras ou funções externas
#include "funcoes/fila.h"

// Função estática para trocar dois ponteiros de Paciente, usada internamente no heap
static void trocar(Paciente **a, Paciente **b) {
    Paciente *temp = *a;  // Guarda temporariamente o valor de *a
    *a = *b;              // Atribui o valor de *b para *a
    *b = temp;            // Coloca o valor temporário (original de *a) em *b
}

// Função para criar uma heap vazia com capacidade definida
Heap *criarHeap(int capacidade) {
    // Aloca memória para a estrutura Heap
    Heap* heap = (Heap*) malloc(sizeof(Heap));
    // Se alocação foi bem sucedida
    if (heap != NULL) {
        heap->tamanho = 0; // Inicializa o tamanho da heap como zero (vazia)
    }
    return heap; // Retorna o ponteiro para a heap criada
}

// Função para inserir um paciente na heap
int inserirHeap(Heap *heap, Paciente *paciente) {
    // Se a heap já atingiu a capacidade máxima definida, retorna 0 (falha)
    if (heap->tamanho >= TAM_MAX_HEAP) return 0;

    // Índice onde o novo paciente será inserido (no final da heap)
    int i = heap->tamanho;
    // Coloca o paciente na posição final da heap
    heap->pacientes[i] = paciente;

    // Corrige a propriedade da heap subindo o paciente até a posição correta
    while (i > 0) {
        int pai = (i - 1) / 2;  // Índice do pai do nó atual (em heap binária)
        // Se o paciente atual tem idade maior que o do pai, troca posições para manter max-heap
        if (heap->pacientes[i]->idade > heap->pacientes[pai]->idade) {
            trocar(&heap->pacientes[i], &heap->pacientes[pai]); // troca ponteiros dos pacientes
            i = pai; // Atualiza i para continuar subindo na heap
        } else {
            break; // Se não precisa trocar, sai do loop
        }
    }
    // Incrementa o tamanho da heap após inserção
    heap->tamanho++;
    // Retorna 1 para indicar sucesso
    return 1;
}

// Função para manter a propriedade da heap, "peneirando" o elemento na posição i para baixo
void peneirar(Heap *heap, int i) {
    int maior = i;               // Inicializa maior como índice atual
    int esq = 2 * i + 1;         // Índice do filho esquerdo
    int dir = 2 * i + 2;         // Índice do filho direito

    // Verifica se filho esquerdo existe e tem idade maior que o atual maior
    if (esq < heap->tamanho && heap->pacientes[esq]->idade > heap->pacientes[maior]->idade)
        maior = esq;             // Atualiza maior para o filho esquerdo

    // Verifica se filho direito existe e tem idade maior que o atual maior
    if (dir < heap->tamanho && heap->pacientes[dir]->idade > heap->pacientes[maior]->idade)
        maior = dir;             // Atualiza maior para o filho direito

    // Se maior mudou, troca elementos e continua peneirando recursivamente
    if (maior != i) {
        trocar(&heap->pacientes[i], &heap->pacientes[maior]); // troca o atual com o maior filho
        peneirar(heap, maior); // chama recursivamente para continuar ajeitando a heap
    }
}

// Função para remover o paciente com maior idade da heap (raiz da max-heap)
Paciente *removerHeap(Heap *heap) {
    // Se a heap estiver vazia, retorna NULL (não há nada para remover)
    if (heap->tamanho == 0) return NULL;

    // Guarda o paciente que será removido (raiz da heap)
    Paciente* removido = heap->pacientes[0];
    // Decrementa o tamanho da heap (removendo um elemento)
    heap->tamanho--;
    // Coloca o último paciente no lugar da raiz
    heap->pacientes[0] = heap->pacientes[heap->tamanho];
    // Ajusta a heap para manter a propriedade max-heap a partir da raiz
    peneirar(heap, 0);
    // Retorna o paciente removido
    return removido;
}

// Função para mostrar os pacientes armazenados na heap
void mostrarHeap(Heap *heap) {
    // Verifica se a heap é NULL ou vazia e imprime mensagem se for o caso
    if (heap == NULL || heap->tamanho == 0) {
        printf("Heap vazio.\n");
        return;
    }
    // Percorre todos os pacientes na heap
    for (int i = 0; i < heap->tamanho; i++) {
        Paciente* p = heap->pacientes[i];
        // Imprime nome, idade e RG do paciente
        printf("%s (%d anos) - RG: %s\n", p->nome, p->idade, p->rg);
    }
}

// Função para liberar a memória alocada para a estrutura heap
void liberarHeap(Heap *heap) {
    free(heap); // Libera o ponteiro heap, não libera pacientes (presume-se que paciente é gerenciado externamente)
}

// Função para exibir o menu de opções para interação com a heap
void menuTextoHeap() {
    printf("\n=== GERENCIADOR DE ATENDIMENTO MÉDICO ===\n");
    printf("1. Enfileirar paciente\n");   // Opção para inserir paciente na heap
    printf("2. Desenfileirar paciente\n"); // Opção para remover paciente da heap
    printf("3. Mostrar fila\n");            // Opção para mostrar os pacientes na heap
    printf("0. Sair\n");                    // Opção para sair do menu
    printf("Escolha: ");                    // Solicita entrada do usuário
}

// Função que implementa o loop do menu para interação com a heap
void menuHeap(ListaPacientes *lista, Heap *heap){
    int opcao;  // Variável que armazena a opção digitada pelo usuário
    do {
        menuTextoHeap();   // Exibe o menu na tela
        scanf("%d", &opcao); // Lê opção do usuário
        getchar();           // Limpa o buffer para evitar problemas na próxima leitura

        // Verifica a opção escolhida
        switch (opcao) {
            case 1:{
                // Consulta paciente na lista geral e retorna ponteiro para paciente
                Paciente *paciente = consultarPaciente(lista, NULL);
                // Insere o paciente na heap
                inserirHeap(heap, paciente);
                break;
            }
            case 2:
                // Remove o paciente com maior idade da heap
                removerHeap(heap);
                break;
            case 3:
                // Mostra todos os pacientes da heap
                mostrarHeap(heap);
                break;
            case 0:
                // Mensagem de saída do menu
                printf("Saindo...\n");
                break;
            default:
                // Mensagem para opção inválida
                printf("Opção inválida.\n");
        }
    // Repete o menu até o usuário escolher sair (opção 0)
    } while (opcao != 0);
}
