// funcoes/heap.c
#include <stdio.h>
#include <stdlib.h>
#include "funcoes/heap.h"
#include "funcoes/fila.h"

static void trocar(Paciente** a, Paciente** b) {
    Paciente* temp = *a;
    *a = *b;
    *b = temp;
}

Heap* criarHeap(int capacidade) {
    Heap* heap = (Heap*) malloc(sizeof(Heap));
    if (heap != NULL) {
        heap->tamanho = 0;
    }
    return heap;
}

int inserirHeap(Heap* heap, Paciente* paciente) {
    if (heap->tamanho >= TAM_MAX_HEAP) return 0;

    int i = heap->tamanho;
    heap->pacientes[i] = paciente;

    while (i > 0) {
        int pai = (i - 1) / 2;
        if (heap->pacientes[i]->idade > heap->pacientes[pai]->idade) {
            trocar(&heap->pacientes[i], &heap->pacientes[pai]);
            i = pai;
        } else {
            break;
        }
    }
    heap->tamanho++;
    return 1;
}

void peneirar(Heap* heap, int i) {
    int maior = i;
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;

    if (esq < heap->tamanho && heap->pacientes[esq]->idade > heap->pacientes[maior]->idade)
        maior = esq;

    if (dir < heap->tamanho && heap->pacientes[dir]->idade > heap->pacientes[maior]->idade)
        maior = dir;

    if (maior != i) {
        trocar(&heap->pacientes[i], &heap->pacientes[maior]);
        peneirar(heap, maior);
    }
}

Paciente* removerHeap(Heap* heap) {
    if (heap->tamanho == 0) return NULL;

    Paciente* removido = heap->pacientes[0];
    heap->tamanho--;
    heap->pacientes[0] = heap->pacientes[heap->tamanho];
    peneirar(heap, 0);
    return removido;
}

void mostrarHeap(Heap* heap) {
    if (heap == NULL || heap->tamanho == 0) {
        printf("Heap vazio.\n");
        return;
    }
    for (int i = 0; i < heap->tamanho; i++) {
        Paciente* p = heap->pacientes[i];
        printf("%s (%d anos) - RG: %s\n", p->nome, p->idade, p->rg);
    }
}

void liberarHeap(Heap* heap) {
    free(heap);
}

void menu() {
    printf("\n=== GERENCIADOR DE ATENDIMENTO MÉDICO ===\n");
    printf("1. Enfileirar paciente\n");
    printf("2. Desenfileirar paciente\n");
    printf("3. Mostrar fila\n");
    printf("0. Sair\n");
    printf("Escolha: ");
}

void menuHeap(ListaPacientes *lista, Heap *heap){
    int opcao;
    do {
        menu();
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                Paciente* paciente = consultarPaciente(lista);
                inserirHeap(heap, paciente);
                break;
            case 2:
                removerHeap(heap);
                break;
            case 3:
                mostrarHeap(heap);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);
}