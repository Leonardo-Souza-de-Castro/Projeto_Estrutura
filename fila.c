// Inclui a biblioteca padrão de entrada e saída, usada para funções como printf e scanf
#include <stdio.h>
// Inclui a biblioteca padrão para alocação dinâmica de memória, usada para malloc e free
#include <stdlib.h>
// Inclui o arquivo de cabeçalho fila.h, que contém a definição da estrutura Fila e suas funções
#include "funcoes/fila.h"
// Inclui o arquivo pilha.h, pois a fila interage com a pilha para registro de operações (desfazer)
#include "funcoes/pilha.h"

// Função para criar uma fila vazia
Fila *criarFila() {
    // Aloca dinamicamente memória para uma nova estrutura Fila
    Fila *fila = (Fila*) malloc(sizeof(Fila));
    
    // Verifica se a alocação foi bem sucedida (ponteiro não é NULL)
    if (fila != NULL) {
        // Inicializa o ponteiro para o primeiro elemento da fila (head) como NULL
        fila->head = NULL;
        // Inicializa o ponteiro para o último elemento da fila (tail) como NULL
        fila->tail = NULL;
        // Inicializa a quantidade de elementos da fila como zero
        fila->qtd = 0;
    }
    // Retorna o ponteiro para a fila criada (ou NULL se falhou alocação)
    return fila;
}

// Função para adicionar (enfileirar) um paciente na fila
// Parâmetros: fila - a fila onde o paciente será adicionado
// paciente - o paciente a ser adicionado
// pilha - pilha para registrar a operação de enfileirar (para desfazer)
// flag - se 1, registra a operação na pilha; se 0, não registra
int enfileirar(Fila *fila, Paciente *paciente, Pilha *pilha, int flag) {
    // Se fila ou paciente forem NULL, operação inválida, retorna 0 (falha)
    if (fila == NULL || paciente == NULL) return 0;

    // Aloca memória para um novo elemento da fila (tipo EFila)
    EFila *novo = (EFila*) malloc(sizeof(EFila));
    // Se falhar alocar, retorna 0 (falha)
    if (novo == NULL) return 0;

    // Associa o paciente ao novo elemento da fila
    novo->paciente = paciente;
    // O próximo elemento do novo será NULL (pois é o último)
    novo->prox = NULL;

    // Se a fila está vazia (quantidade zero)
    if (fila->qtd == 0) {
        // O novo elemento será o primeiro da fila (head)
        fila->head = novo;
    } else {
        // Caso contrário, liga o último elemento atual ao novo (atualiza o prox do tail)
        fila->tail->prox = novo;
    }

    // Se flag é verdadeira (1), registra na pilha que houve uma operação de enfileiramento
    if (flag)
    {
        push(pilha, paciente, 'E'); // 'E' indica operação de Enfileirar
    }
    
    // Atualiza o ponteiro tail para o novo elemento (último da fila)
    fila->tail = novo;
    // Incrementa a quantidade de elementos da fila
    fila->qtd++;
    // Retorna 1 indicando sucesso na operação
    return 1;
}

// Função para remover (desenfileirar) o paciente do início da fila
// Parâmetros: fila - a fila onde a remoção será feita
// pilha - pilha para registrar a operação de desenfileirar (para desfazer)
// flag - se 1, registra a operação na pilha; se 0, não registra
Paciente *desenfileirar(Fila *fila, Pilha *pilha, int flag) {
    // Se fila for NULL ou estiver vazia (qtd == 0), retorna NULL (não há o que remover)
    if (fila == NULL || fila->qtd == 0) return NULL;

    // Guarda o elemento que será removido (início da fila)
    EFila *removido = fila->head;
    // Pega o paciente associado ao elemento removido
    Paciente *paciente = removido->paciente;
    // Atualiza o início da fila para o próximo elemento (pula o removido)
    fila->head = removido->prox;

    // Se após remoção a fila ficar vazia (head == NULL)
    if (fila->head == NULL) {
        // Atualiza também tail para NULL, pois não há elementos
        fila->tail = NULL;
    }

    // Se flag é verdadeira (1), registra na pilha que houve uma operação de desenfileiramento
    if (flag)
    {
        push(pilha, paciente, 'D'); // 'D' indica operação de Desenfileirar
    }

    // Libera a memória do elemento removido da fila (mas não do paciente, que é retornado)
    free(removido);
    // Decrementa a quantidade de elementos da fila
    fila->qtd--;
    // Retorna o paciente removido da fila
    return paciente;
}

// Função para mostrar os pacientes da fila no console
void mostrarFila(Fila *fila) {
    // Se fila for NULL ou estiver vazia (head == NULL)
    if (fila == NULL || fila->head == NULL) {
        // Informa que a fila está vazia e retorna
        printf("Fila vazia.\n");
        return;
    }

    // Cria um ponteiro auxiliar para percorrer a fila, começando do head
    EFila *aux = fila->head;
    // Percorre a fila até o final (NULL)
    while (aux != NULL) {
        // Pega o paciente do elemento atual
        Paciente *p = aux->paciente;
        // Imprime nome, idade e RG do paciente na tela
        printf("%s (%d anos) - RG: %s\n", p->nome, p->idade, p->rg);
        // Avança para o próximo elemento da fila
        aux = aux->prox;
    }
}

// Função para liberar toda a memória ocupada pela fila
// Remove todos os elementos e libera a estrutura da fila
void liberarFila(Fila *fila, Pilha *pilha) {
    // Enquanto houver elementos na fila
    while (fila->qtd > 0) {
        // Remove elemento da fila e registra a operação na pilha (flag = 1)
        desenfileirar(fila, pilha, 1);
    }
    // Após fila vazia, libera a memória da estrutura fila
    free(fila);
}

// Função que exibe o menu de opções relacionado à fila no console
void menuTextoFila() {
    printf("\n=== GERENCIADOR DE ATENDIMENTO MÉDICO ===\n");
    printf("1. Enfileirar paciente\n");  // Opção 1: adicionar paciente na fila
    printf("2. Desenfileirar paciente\n"); // Opção 2: remover paciente da fila
    printf("3. Mostrar fila\n");           // Opção 3: listar pacientes na fila
    printf("0. Sair\n");                   // Opção 0: sair do menu da fila
    printf("Escolha: ");                   // Solicita que o usuário escolha uma opção
}

// Função que implementa o loop do menu da fila, interagindo com o usuário
// Parâmetros: lista - lista geral de pacientes (para consultar e adicionar na fila)
// fila - a fila onde serão feitas operações
// pilha - pilha para registrar operações para desfazer
void menuFila(ListaPacientes *lista, Fila *fila, Pilha *pilha){
    int opcao;  // Variável para armazenar a opção escolhida pelo usuário
    do {
        // Exibe o menu de opções da fila
        menuTextoFila();
        // Lê a opção digitada pelo usuário
        scanf("%d", &opcao);
        // Limpa o caractere de nova linha do buffer para evitar problemas em próximas leituras
        getchar();

        // Verifica qual opção foi escolhida
        switch (opcao) {
            case 1:{
                // Consulta paciente na lista (func. externa) e retorna ponteiro para paciente selecionado
                Paciente *p = consultarPaciente(lista, NULL);
                // Enfileira esse paciente na fila, registrando a operação na pilha (flag=1)
                enfileirar(fila, p, pilha, 1);
                break;
            }
            case 2:
                // Desenfileira paciente da fila, registrando a operação na pilha (flag=1)
                desenfileirar(fila, pilha, 1);
                break;
            case 3:
                // Mostra todos os pacientes atualmente na fila
                mostrarFila(fila);
                break;
            case 0:
                // Mensagem de saída do menu da fila
                printf("Saindo...\n");
                break;
            default:
                // Caso o usuário digite uma opção inválida
                printf("Opção inválida.\n");
        }
    // Repete o menu até o usuário escolher a opção 0 para sair
    } while (opcao != 0);
}
