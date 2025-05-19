#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes/paciente.h"  // Inclui a definição das estruturas e funções relacionadas a pacientes

// Função que cria e retorna uma nova lista de pacientes vazia
ListaPacientes *criarLista() {
    // Aloca memória para a lista
    ListaPacientes *lista = (ListaPacientes*) malloc(sizeof(ListaPacientes));
    if (lista != NULL) {      // Verifica se a alocação foi bem-sucedida
        lista->inicio = NULL; // Inicializa o ponteiro para o início da lista como NULL (lista vazia)
        lista->qtd = 0;       // Inicializa a quantidade de pacientes como zero
    }
    return lista;             // Retorna o ponteiro para a lista criada (ou NULL se falhou)
}

// Função que cria e retorna uma nova data com dia, mês e ano fornecidos
Data *criarData(int dia, int mes, int ano) {
    Data *novaData = (Data*) malloc(sizeof(Data));  // Aloca memória para uma estrutura Data
    if (novaData != NULL) {                          // Verifica sucesso da alocação
        novaData->dia = dia;                         // Define o dia
        novaData->mes = mes;                         // Define o mês
        novaData->ano = ano;                         // Define o ano
    }
    return novaData;                                 // Retorna o ponteiro para a nova data (ou NULL se falhou)
}

// Função que cria um paciente com nome, RG, idade e data de entrada
Paciente *criarPaciente(char nome[], char rg[], int idade, int dia, int mes, int ano) {
    Paciente *p = malloc(sizeof(Paciente));  // Aloca memória para o paciente
    if (!p) return NULL;                      // Se falhou, retorna NULL

    // Copia o nome e RG para o paciente usando strncpy para evitar overflow
    strncpy(p->nome, nome, sizeof(p->nome));
    strncpy(p->rg, rg, sizeof(p->rg));
    // Garante que as strings terminem com '\0' (segurança)
    p->nome[sizeof(p->nome) - 1] = '\0';
    p->rg[sizeof(p->rg) - 1] = '\0';

    p->idade = idade;                         // Define a idade do paciente

    // Aloca memória para a data de entrada
    p->entrada = malloc(sizeof(Data));
    if (!p->entrada) {                        // Se falhou alocar a data, libera paciente e retorna NULL
        free(p);
        return NULL;
    }

    // Define a data de entrada
    p->entrada->dia = dia;
    p->entrada->mes = mes;
    p->entrada->ano = ano;

    return p;                                // Retorna o ponteiro para o paciente criado
}

// Função que cria um novo paciente e o insere no final da lista de pacientes
int cadastrarPaciente(ListaPacientes *lista, char nome[], int idade, char rg[], int dia, int mes, int ano) {
    if (lista == NULL) return 0;  // Se o ponteiro para lista for inválido, retorna 0 (falha)

    // Aloca memória para um novo elemento da lista encadeada
    ELista *novo = (ELista *) malloc(sizeof(ELista));
    if (novo == NULL) return 0;   // Se falhou, retorna 0

    // Cria o paciente com os dados fornecidos e armazena no campo dados do novo elemento
    novo->dados = criarPaciente(nome, rg, idade, dia, mes, ano);
    if (novo->dados == NULL) {    // Se falhou a criação do paciente
        free(novo);               // Libera o nó criado para a lista
        return 0;                 // Retorna falha
    }

    novo->prox = NULL;            // Define o próximo elemento como NULL (será o último da lista)

    if (lista->inicio == NULL) {  // Se a lista estiver vazia
        lista->inicio = novo;     // Novo elemento vira o primeiro
    } else {
        // Caso contrário, percorre até o último elemento da lista
        ELista *atual = lista->inicio;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo;       // Insere o novo paciente no final da lista
    }

    lista->qtd++;                 // Incrementa a contagem total de pacientes na lista

    return 1;                    // Retorna sucesso na inserção
}

// Função que exibe os dados de todos os pacientes da lista
void mostrarLista(ListaPacientes *lista) {
    if (lista == NULL || lista->inicio == NULL) {  // Verifica se a lista existe e não está vazia
        printf("Lista vazia.\n");
        return;  // Sai da função pois não há nada a mostrar
    }

    ELista *aux = lista->inicio;   // Inicializa auxiliar apontando para o primeiro elemento
    while (aux != NULL) {          // Percorre toda a lista até o final
        // Imprime os dados do paciente atual
        printf("Nome: %s\n", aux->dados->nome);
        printf("Idade: %d\n", aux->dados->idade);
        printf("RG: %s\n", aux->dados->rg);
        printf("Data de entrada: %02d/%02d/%04d\n\n",
               aux->dados->entrada->dia,
               aux->dados->entrada->mes,
               aux->dados->entrada->ano);
        aux = aux->prox;           // Avança para o próximo elemento
    }
}

// Função que busca um paciente pelo RG na lista
Paciente *consultarPaciente(ListaPacientes *lista, char identidade[]) {
    char rg[15];               // Buffer para armazenar o RG a buscar

    // Se identidade (RG) não foi fornecido (NULL), pede entrada do usuário
    if (identidade == NULL) {
        printf("Digite seu RG: ");
        fgets(rg, sizeof(rg), stdin);              // Lê RG do teclado
        rg[strcspn(rg, "\n")] = 0;                 // Remove o '\n' que fgets lê junto
    } else {
        // Caso RG tenha sido passado como parâmetro, copia para a variável rg
        strncpy(rg, identidade, sizeof(rg));
        rg[sizeof(rg) - 1] = '\0';                 // Garante terminação da string
    }

    if (lista == NULL) {
        return NULL;                               // Se lista inválida, retorna NULL (não encontrado)
    }

    ELista *aux = lista->inicio;                   // Começa a busca no início da lista
    while (aux != NULL) {
        if (strcmp(aux->dados->rg, rg) == 0) {    // Se RGs são iguais
            // Cria uma cópia do paciente encontrado para retornar (evita mexer na lista direta)
            Paciente* pacienteLocalizado = criarPaciente(aux->dados->nome,
                                                         aux->dados->rg,
                                                         aux->dados->idade,
                                                         aux->dados->entrada->dia,
                                                         aux->dados->entrada->mes,
                                                         aux->dados->entrada->ano);
            return pacienteLocalizado;             // Retorna a cópia do paciente
        }
        aux = aux->prox;                           // Continua procurando na lista
    }

    // Se não encontrou o paciente, avisa o usuário
    printf("Paciente com RG %s não encontrado.\n", rg);
    return NULL;                                   // Retorna NULL para indicar paciente não achado
}

// Função para atualizar nome e idade de um paciente identificado pelo RG
int atualizarPaciente(ListaPacientes *lista, char rg[], char novoNome[], int novaIdade) {
    if (lista == NULL) return 0;  // Proteção contra lista inválida

    ELista *aux = lista->inicio;  // Inicia busca no início da lista
    while (aux != NULL) {
        if (strcmp(aux->dados->rg, rg) == 0) {    // Se RG igual
            strcpy(aux->dados->nome, novoNome);   // Atualiza o nome
            aux->dados->idade = novaIdade;        // Atualiza a idade
            return 1;                             // Retorna sucesso
        }
        aux = aux->prox;                           // Continua buscando
    }

    return 0;  // Paciente não encontrado, retorna falha
}

// Função para remover paciente da lista pelo RG
int removerPaciente(ListaPacientes *lista, char rg[]) {
    if (lista == NULL || lista->inicio == NULL) return 0; // Lista inválida ou vazia

    ELista *atual = lista->inicio;    // Ponteiro para elemento atual na busca
    ELista *anterior = NULL;           // Ponteiro para elemento anterior

    // Percorre até encontrar paciente com RG ou chegar ao fim
    while (atual != NULL && strcmp(atual->dados->rg, rg) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) return 0;  // Não encontrou o paciente

    // Remove o paciente da lista
    if (anterior == NULL) {
        // Se é o primeiro da lista, atualiza o início
        lista->inicio = atual->prox;
    } else {
        // Caso contrário, ajusta o ponteiro do anterior para pular o removido
        anterior->prox = atual->prox;
    }

    // Libera memória da data de entrada e do nó da lista
    free(atual->dados->entrada);
    free(atual);
    lista->qtd--;   // Decrementa a quantidade de pacientes

    return 1;       // Retorna sucesso na remoção
}

// Função que exibe o menu texto específico para gerenciamento de pacientes
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
    int opcao;  // Variável para armazenar a opção do menu escolhida pelo usuário
    do {
        menuTextoPaciente();           // Exibe o menu de opções para o paciente
        scanf("%d", &opcao);           // Lê a opção escolhida pelo usuário
        getchar();                    // Consome o caractere '\n' deixado no buffer pelo scanf

        char nome[TAM_NOME];          // Array para armazenar o nome do paciente
        int idade;                    // Variável para armazenar a idade do paciente
        char rg[15];                  // Array para armazenar o RG do paciente
        char nascimento[11];          // Array para armazenar a data de registro (ex: DD/MM/YYYY)
        char *teste;                  // Ponteiro auxiliar para manipular a string de data
        int dia;                      // Variável para o dia da data de nascimento
        int mes;                      // Variável para o mês da data de nascimento
        int ano;                      // Variável para o ano da data de nascimento

        switch (opcao) {
            case 1:
                printf("Digite seu nome: ");
                fgets(nome, sizeof(nome), stdin);                 // Lê o nome completo do paciente
                nome[strcspn(nome, "\n")] = 0;                    // Remove o '\n' que fgets adiciona no final
                
                printf("Digite sua idade: ");
                scanf("%d", &idade);                               // Lê a idade do paciente
                getchar();                                        // Consome o '\n' do buffer
                
                printf("Digite seu RG: ");
                fgets(rg, sizeof(rg), stdin);                      // Lê o RG do paciente
                rg[strcspn(rg, "\n")] = 0;                         // Remove o '\n' do final
                
                printf("Digite sua data de registro (ex: DD/MM/YYYY): ");
                fgets(nascimento, sizeof(nascimento), stdin);      // Lê a data de registro como string
                nascimento[strcspn(nascimento, "\n")] = 0;         // Remove o '\n' do final

                // Quebra a string nascimento no formato DD/MM/YYYY para extrair dia, mês e ano
                teste = strtok(nascimento, "/");                    // Pega o dia (antes da primeira barra)
                if (teste != NULL) dia = atoi(teste);               // Converte o dia para inteiro
                
                teste = strtok(NULL, "/");                           // Pega o mês (entre as barras)
                if (teste != NULL) mes = atoi(teste);               // Converte o mês para inteiro
                
                teste = strtok(NULL, "/");                           // Pega o ano (depois da última barra)
                if (teste != NULL) ano = atoi(teste);               // Converte o ano para inteiro
                
                cadastrarPaciente(lista, nome, idade, rg, dia, mes, ano);  // Chama função para cadastrar paciente
                break;

            case 2:{
                Paciente *p = consultarPaciente(lista, NULL);       // Consulta paciente (parâmetro NULL pode indicar busca padrão)
                if (p != NULL) {                                     // Se paciente encontrado, exibe informações
                    printf("\nPaciente encontrado:\n");
                    printf("Nome: %s\n", p->nome);
                    printf("Idade: %d\n", p->idade);
                    printf("RG: %s\n", p->rg);
                    printf("Data de entrada: %02d/%02d/%04d\n",     // Formata a data com dois dígitos para dia e mês, quatro para ano
                        p->entrada->dia,
                        p->entrada->mes,
                        p->entrada->ano);
                    free(p->entrada);                                // Libera a memória alocada para a data de entrada
                    free(p);                                         // Libera a memória alocada para o paciente retornado
                } else {
                    printf("Paciente não encontrado.\n");            // Caso paciente não exista na lista
                }
                break;
            }
            case 3:
                mostrarLista(lista);                                 // Mostra todos os pacientes da lista
                break;
            case 4:
                printf("Digite seu RG: ");
                fgets(rg, sizeof(rg), stdin);                        // Lê RG do paciente para atualização
                rg[strcspn(rg, "\n")] = 0;                           // Remove '\n' do final
                
                printf("Digite seu nome: ");
                fgets(nome, sizeof(nome), stdin);                     // Lê novo nome do paciente
                nome[strcspn(nome, "\n")] = 0;                        // Remove '\n' do final

                printf("Digite sua idade: ");
                scanf("%d", &idade);                                  // Lê nova idade do paciente

                atualizarPaciente(lista, rg, nome, idade);            // Atualiza paciente com os novos dados
                break;
            case 5:
                printf("Digite seu RG: ");
                fgets(rg, sizeof(rg), stdin);                        // Lê RG do paciente a ser removido
                rg[strcspn(rg, "\n")] = 0;                           // Remove '\n' do final

                removerPaciente(lista, rg);                           // Remove paciente da lista pelo RG
                break;
            case 0:
                printf("Saindo...\n");                                // Mensagem ao sair do menu
                break;
            default:
                printf("Opção inválida.\n");                          // Mensagem para opção não reconhecida
        }
    } while (opcao != 0);                                              // Repete o menu enquanto a opção for diferente de 0
}

