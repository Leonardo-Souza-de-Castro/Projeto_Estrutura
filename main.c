// main.c
#include <stdio.h>
#include <stdlib.h>
#include "funcoes/paciente.h"
#include "funcoes/fila.h"
#include "funcoes/heap.h"
#include "funcoes/pilha.h"
#include "funcoes/arvore.h"
#include "funcoes/salvar.h"
#include "funcoes/sobre.h"

void menu() {
    printf("\n=== GERENCIADOR DE ATENDIMENTO MÉDICO ===\n");
    printf("1. Cadastro de paciente\n");
    printf("2. Atendimento\n");
    printf("3. Atendimento prioritário\n");
    printf("4. Pesquisa\n");
    printf("5. Desfazer\n");
    printf("6. Salvar e carregar dados\n");
    printf("7. Sobre\n");
    printf("0. Sair\n");
    printf("Escolha: ");
}

int main() {
    int opcao;
    ListaPacientes* lista = criarLista();
    Fila* fila = criarFila();
    Heap* heap = criarHeap(20);
    Pilha* pilha = criarPilha();

    carregarDados(lista, "dados.txt");

    do {
        menu();
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                menuPacientes(lista);
                break;
            case 2:
                menuFila(lista, fila, pilha);
                break;
            case 3:
                menuHeap(lista, heap);
                break;
            case 4:
                menuArvore(lista);
                break;
            case 5:
                desfazer(fila, pilha);
                break;
            case 6:
                salvarDados(lista, "dados.txt");
                printf("Dados salvos.\n");
                break;
            case 7:
                mostrarSobre();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    liberarLista(lista);
    liberarFila(fila);
    liberarHeap(heap);
    liberarPilha(pilha);
    // liberarArvore(raiz);
    return 0;
}
