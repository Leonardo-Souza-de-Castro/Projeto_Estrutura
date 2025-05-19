# 🏥 Gerenciador de Atendimento Médico

Projeto da disciplina **Estrutura de Dados** — 1º semestre de 2025  
Centro Universitário FEI - Ciência da Computação  
Prof. Luciano Rossi

---

## 📌 Descrição

O **Gerenciador de Atendimento Médico** é um sistema em C desenvolvido para gerenciar pacientes em uma clínica ou hospital. O sistema utiliza diversas estruturas de dados para cadastrar pacientes, organizar atendimentos (regulares e prioritários), realizar pesquisas, desfazer operações e manipular arquivos de dados.

Este projeto tem como principal objetivo aplicar os conceitos de **listas encadeadas**, **filas**, **heaps**, **árvores binárias de busca**, **pilhas** e **arquivos**, com foco no aprendizado prático de estruturas de dados dinâmicas.

---

## 🧠 Funcionalidades

### 📋 1. Cadastrar Paciente
- Cadastro de novos pacientes em uma **lista dinâmica encadeada**.
- Manutenção da ordem de inserção (início da lista).
- Operações disponíveis:
  - Cadastrar novo paciente
  - Consultar paciente
  - Atualizar dados
  - Remover paciente
  - Mostrar todos os pacientes

### 🧾 2. Atendimento
- Inserção de pacientes já cadastrados em uma **fila simples** (FIFO).
- Operações disponíveis:
  - Enfileirar paciente
  - Desenfileirar paciente
  - Mostrar fila atual

### 🚨 3. Atendimento Prioritário
- Inserção de pacientes já cadastrados em uma **fila de prioridade (heap máximo)** baseada na **idade**.
- Capacidade máxima: 20 pacientes por dia.
- Operações disponíveis:
  - Enfileirar paciente
  - Desenfileirar paciente
  - Mostrar fila de prioridade

### 🔍 4. Pesquisa
- Inserção de pacientes já cadastrados em uma **árvore binária de busca (ABB)**.
- Critério de ordenação configurável:
  - Ano de registro
  - Mês de registro
  - Dia de registro
  - Idade do paciente
- Operações disponíveis:
  - Mostrar registros ordenados por qualquer um dos critérios acima

### ↩️ 5. Desfazer Operações
- Utiliza uma **pilha** para armazenar operações realizadas na montagem da fila de atendimento.
- Operações disponíveis:
  - Exibir histórico de operações
  - Desfazer última operação (com confirmação do usuário)

### 💾 6. Carregar / Salvar Dados
- Leitura e escrita de arquivos com dados dos pacientes.
- Mantém a ordem de inserção dos registros.
- Operações disponíveis:
  - Carregar pacientes de arquivo
  - Salvar pacientes em arquivo

### ℹ️ 7. Sobre
- Exibe informações dos desenvolvedores:
  - Nome
  - Ciclo
  - Curso
  - Disciplina
  - Data de desenvolvimento

---

## 🗃️ Estruturas de Dados Utilizadas

| Recurso                     | Estrutura de Dados                |
|----------------------------|-----------------------------------|
| Lista de pacientes         | Lista encadeada                   |
| Fila de atendimento        | Fila (FIFO)                       |
| Fila prioritária           | Heap máximo (por idade)           |
| Pesquisa por critério      | Árvore Binária de Busca (ABB)     |
| Desfazer ações             | Pilha                             |
| Armazenamento              | Arquivos (entrada/saída em `.txt`)|

---

## 🔧 Requisitos

- Compilador C (GCC ou compatível)
- Terminal para execução
- Ambiente Linux, macOS ou Windows com suporte a C ANSI

---

## 📁 Organização do Projeto

```text
📦 PROJETO_ESTRUTURA
├── .vscode/                     # Configurações do editor (opcional)
├── funcoes/                     # Arquivos de cabeçalho (.h)
│   ├── arvore.h
│   ├── fila.h
│   ├── heap.h
│   ├── paciente.h
│   ├── pilha.h
│   ├── salvar.h
│   ├── sobre.h
├── a.exe                        # Arquivo executável (gerado na compilação)
├── Dados.txt                    # Arquivo de entrada com dados de pacientes
├── arvore.c
├── fila.c
├── heap.c
├── main.c
├── paciente.c
├── pilha.c
├── salvar.c
├── sobre.c
├── README.md
```

---
## 🚀 Como Executar

1. **Clone o repositório:**

```bash
git clone https://github.com/Leonardo-Souza-de-Castro/Projeto_Estrutura
cd Projeto_Estrutura
```

2. **Compile o projeto:**

```bash
gcc *.c
```

3. **Execute o programa:**
```bash
./a.exe
```

---

## 👨‍💻 Desenvolvedores

**Nomes:** 
 - Felipe Brum Pereira - 22.123.112-9
 - Leonardo Souza de Castro - 22.123.114-5

**Ciclo:** 4º Semestre

**Curso:** Ciência da Computação

**Disciplina:** Estrutura de Dados

**Data:** 19/05/2025