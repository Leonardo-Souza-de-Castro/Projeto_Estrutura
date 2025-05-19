#ifndef ARVORE_H
#define ARVORE_H

//Struct dos nós
typedef struct EABB {
    Paciente* dados;
    struct EABB* FilhoEsq;
    struct EABB* FilhoDir;
} EABB;

//Struct da arvore
typedef struct {
    EABB* raiz;
    int qtd;
} ABB;

//Cria um novo nó
EABB* criar_no(Paciente* p);

//Cria uma nova arvore
ABB* criar_arvore();

//Insere os pacientes cadastrados na arvore ordenando por idade
void inserir_por_idade(ABB* arvore, Paciente* valor);

//Insere os pacientes cadastrados na arvore ordendando por ano
void inserir_por_ano(ABB* arvore, Paciente* valor);

//Insere os pacientes cadastrados na arvore ordenando por mes
void inserir_por_mes(ABB* arvore, Paciente* valor);

//Insere os pacientes cadastrados na arvore ordenando por dia
void inserir_por_dia(ABB* arvore, Paciente* valor) ;

//Exibi a arvore em ordem
void exibir_em_ordem(EABB* raiz);

//Menu com as opções de pesquisa que chama as outras funções
void menuArvore(ListaPacientes *lista);

#endif