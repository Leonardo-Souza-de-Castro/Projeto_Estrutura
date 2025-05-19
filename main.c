// Inclusão das bibliotecas padrão para entrada/saída e alocação dinâmica
#include <stdio.h>
#include <stdlib.h>

// Inclusão dos headers com as definições e funções para manipular pacientes, fila, heap, pilha, árvore, salvar dados e informações do sistema
#include "funcoes/paciente.h"
#include "funcoes/fila.h"
#include "funcoes/heap.h"
#include "funcoes/pilha.h"
#include "funcoes/arvore.h"
#include "funcoes/salvar.h"
#include "funcoes/sobre.h"

// Função que exibe o menu principal do sistema
void menu() {
    printf("\n=== GERENCIADOR DE ATENDIMENTO MÉDICO ===\n");  // Título do sistema
    printf("1. Cadastro de paciente\n");                    // Opção para cadastrar pacientes
    printf("2. Atendimento\n");                              // Opção para atendimento normal (fila)
    printf("3. Atendimento prioritário\n");                  // Opção para atendimento prioritário (heap)
    printf("4. Pesquisa\n");                                 // Opção para realizar pesquisa na árvore
    printf("5. Desfazer\n");                                 // Opção para desfazer última operação (pilha)
    printf("6. Salvar e carregar dados\n");                  // Opção para salvar/carregar dados persistidos
    printf("7. Sobre\n");                                    // Opção para mostrar informações sobre o programa
    printf("0. Sair\n");                                     // Opção para sair do programa
    printf("Escolha: ");                                     // Prompt para entrada da escolha do usuário
}

int main() {
    int opcao;  // Variável para armazenar a opção do usuário

    // Cria a lista dinâmica de pacientes
    ListaPacientes *lista = criarLista();

    // Cria a fila para atendimento
    Fila *fila = criarFila();

    // Cria a heap com capacidade para 20 pacientes (atendimento prioritário)
    Heap *heap = criarHeap(20);

    // Cria a pilha para armazenar operações para desfazer (undo)
    Pilha *pilha = start_Pilha();

    // Loop principal que mantém o programa rodando até o usuário escolher sair (opção 0)
    do {
        menu();               // Exibe o menu principal
        scanf("%d", &opcao);  // Lê a opção digitada pelo usuário
        getchar();            // Limpa o buffer do teclado para evitar problemas na próxima leitura

        // Avalia a opção escolhida e executa a função correspondente
        switch (opcao) {
            case 1:
                menuPacientes(lista);    // Chama menu para cadastro/manutenção de pacientes
                break;
            case 2:
                menuFila(lista, fila, pilha); // Chama menu para atendimento via fila (FIFO)
                break;
            case 3:
                menuHeap(lista, heap);   // Chama menu para atendimento prioritário via heap (max-heap)
                break;
            case 4:
                menuArvore(lista);       // Chama menu para pesquisa na estrutura árvore
                break;
            case 5:
                desfazer(fila, pilha, lista); // Chama função para desfazer a última operação realizada
                break;
            case 6:
                menuSalvar(lista);       // Chama menu para salvar ou carregar dados da lista de pacientes
                break;
            case 7:
                mostrarSobre();          // Exibe informações "Sobre" o programa
                break;
            case 0:
                printf("Saindo...\n");   // Mensagem de saída do programa
                break;
            default:
                printf("Opção inválida.\n"); // Mensagem para opção digitada inválida
        }
    // Continua enquanto opção for diferente de zero (0)
    } while (opcao != 0);

    

    return 0; // Retorna 0 indicando término normal do programa
}
