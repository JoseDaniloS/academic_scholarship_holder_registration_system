# Sistema de cadastros de bolsistas acadêmicos.

## Sumário:
* [Introdução](#Introdução)

* [Problematica](#Problematica)

* [Executar projeto](#Executar-projeto)

* [Funcionalidades](#Funcionalidades)

* [Desenvolvimento](#Desenvolvimento)

* [Estrutura do repositorio](#Estrutura-do-repositorio)

***

## Introdução

Projeto desenvolvido em C para o cadastro de bolsas e bolsistas
acadêmicos que permite o gerenciamento eficiente de informações sobre os beneficiários. O sistema possibilita o registro, busca, edição, consulta, listagem e exclusão de dados dos bolsistas e das recpectivas bolsas. 

## Problematica

A necessidade de um sistema de cadastro de bolsistas acadêmicos surge de uma série de problemas e desafios ao gerenciar programas de bolsas de estudo. Esses desafios criam um ambiente em que o gerenciamento manual se torna ineficaz.

## Executar projeto

- 1º  clone o repositório do projeto:<br>

```c
git clone github.com/classroom-ufersa/academic_scholarship_holder_registration_system.git
```
- 2º execute o programa:<br>
```c
gcc -o main main.c ../src/bolsas.c ../src/bolsistas.c ../src/sistema.c  
```
## Funcionalidades

| Menu                                     | Status |
|--------------------------------------------|--------|
| [ 1 ] - Adicionar Bolsa                      | ✔      |
| [ 2 ] - Adicionar Bolsista                        | ✔      |
| [ 3 ] - Excluir Bolsista                         | ✔      |
| [ 4 ] - Excluir Bolsa                           | ✔      |
| [ 5 ] - Listar Bolsistas             | ✔      |
| [ 6 ] - Buscar Bolsista                   | ✔      |
| [ 7 ] - Editar Dados do Bolsista  | ✔      |
| [ 8 ] - Consultar Bolsas Disponiveis                                       | ✔      
[ 9 ] - Sair                                       | ✔  

## Desenvolvimento<br>
**Listas encadeadas**
- Para o desenvolvimento do projeto foram utilizadas listas encadeadas simples onde cada nó guarda informações de uma bolsa e aponta para a próxima. Além disso, cada bolsa pode ter uma lista de bolsistas, formando uma relação entre si. 

>**Exemplo visual:**

```
Bolsa 1 -> Bolsa 2 -> Bolsa 3 -> NULL
Dentro de cada bolsa (campo Bolsista *bolsistas):
Bolsa 1 pode ter uma lista de bolsistas associados:
Bolsista 1 -> Bolsista 2 -> NULL
```

**Tipos estruturados**

> **Struct Bolsa**
```
struct bolsa
{
    char nome_bolsa[MAX_BOLSA];
    float valor_mensal;
    Data inicio;
    Data termino;
    Bolsista *bolsistas;
    Bolsa *proxima_bolsa;
};
```

<br>

> **Struct bolsista**
```
struct bolsista
{
    char nome_completo[MAX];
    long int matricula;
    char curso[50];
    char CPF[15];
    char bolsa_associada[MAX];
    struct bolsista *proximo_bolsista;
};
```
**TAD (Tipo Abstrato de Dado)**

- Foram utilizadas 3 TADs para melhorar a organização, manutenção e eficiência do código.

**Hierarquia**
```
Bolsa
 └── Bolsista
     └── Sistema
```

> **bolsas.h**

```
#ifndef BOLSA_H
#define BOLSA_H

#include "bolsistas.h"
#include <stdio.h>

typedef struct data Data;

typedef struct bolsa Bolsa;

// Funções para manipulação de bolsas;

/*Função que aloca e preenche os campos de uma nova bolsa.
Recebe como parâmetro um ponteiro duplo de Bolsa*/
void insere_bolsa(Bolsa **bolsas);

/*Função que retorna 0 caso data de termino seja menor que data de inicio e 1 caso contrário
Recebe como parâmetro duas variáveis do tipo Data: inicio e fim*/
int verifica_data_termino(Data inicio, Data fim);

/*Função que insere uma nova bolsa em uma lista ligada de forma ordenada.
Recebe como parâmetros duas variáveis do tipo Bolsa */
void insere_bolsa_ordenada(Bolsa **bolsas, Bolsa *nova_bolsa);

/*Função que lê as bolsas na ordem correta
Recebe como parâmetros duas variáveis do tipo Bolsa*/
void ler_bolsa_no_final(Bolsa **bolsas, Bolsa *nova_bolsa);

/*Função para excluir uma bolsa.
Recebe como parâmetro um ponteiro duplo de Bolsa*/
void excluir_bolsas(Bolsa **bolsas);

/*Função para excluir um bolsista por nome.
Recebe como parâmetro um ponteiro duplo de Bolsa*/
void excluir_bolsista_por_nome(Bolsa **bolsas);

/*Função para verificar se a bolsa ja esta cadastrada.
Recebe como parâmetro um ponteiro de Bolsa e o nome da bolsa*/
int verifica_bolsa_existente(Bolsa *bolsas, char *nome_bolsa);

/*Função para escolher se buscará bolsista por nome ou matricula.
Recebe como parâmetro um ponteiro duplo de Bolsa*/
void menu_busca_bolsista(Bolsa **bolsas);

/*Função para buscar bolsista por nome.
Recebe como parâmetro um ponteiro duplo de Bolsa*/
void buscar_bolsista_por_nome(Bolsa **bolsas);

/*Função para buscar bolsista por matricula.
Recebe como parâmetro um ponteiro duplo de Bolsa*/
void buscar_bolsista_por_matricula(Bolsa **bolsas);

/*Função que busca bolsa
Recebe como parâmetros um ponteiro de Bolsa e o nome da bolsa*/
Bolsa *busca_bolsa(char *nome_bolsa, Bolsa *bolsas);

/*Função para consultar as bolsas disponíveis.
Recebe como parâmetro um ponteiro duplo de Bolsa*/
void consultar_bolsas_disponiveis(Bolsa **bolsas);

/*Função que lista todos os bolsistas cadastrados
Recebe como parâmetro um ponteiro duplo de Bolsa*/
void auxiliar_listar_bolsistas(Bolsa **bolsas);

/*Função que adiciona bolsista em uma bolsa
Recebe como parâmetro um ponteiro duplo de Bolsa*/
void adiciona_bolsista_na_bolsa(Bolsa **bolsas);

/*Função para escanear todas as bolsas armazenadas no banco de dado(arquivo.txt)
Recebe como parâmetro um ponteiro duplo de Bolsa e um ponteiro dupli para o arquivo.txt*/
void ler_bolsa_arquivo(FILE **banco_de_dados, Bolsa **bolsas);

/*Função que insere um bolsa, com seus respectivos compos, noa arquivo.txt
Recebe com parâmetro um ponteiro duplo de Bolsa e um ponteiro dupli para o arquivo.txt*/
void insere_bolsa_arquivo(FILE **banco_de_dados, Bolsa **bolsas);

/*Função que verifica se a lista de bolsas está vazia
Recebe com parâmetro um ponteiro para Bolsa*/
int bolsa_vazia(Bolsa *bolsas);

/*Função que edita os dados do Bolsista a partir de um menu com duas opções: editar por nome ou por matricula
Recebe com parâmetro um ponteiro duplo de Bolsa*/
void edita_dados_bolsista(Bolsa **bolsas);

#endif // BOLSA_H

```
***
<br>

> **bolsistas.h**

```
#ifndef BOLSISTA_H
#define BOLSISTA_H

#include <stdio.h>
#include "sistema.h"
#define MAX 100

// Funções para manipulação de bolsistas

typedef struct bolsista Bolsista;

/*Função que preenche os compos de bolsista e o adiciona à lista
Recebe como parâmetro um ponteiro duplo de bolsistas e uma string com o nome da bolsa*/
void adiciona_bolsista(Bolsista **bolsistas, char *nome_bolsa);

/*Função que insere o bolsista na lista de forma ordenada (ordenação por nome)
Recebe como parâmetros um ponteiro duplo de Bolsista e outro ponteiro de Bolsista*/
void insere_bolsista_ordenado(Bolsista **bolsistas, Bolsista *novo_bolsista);

/*Função que busca um bolsista pelo nome em uma bolsa.
Recebe como parâmetro um ponteiro de Bolsista e o nome do bolsista que sera procurado*/
Bolsista *auxiliar_buscar_bolsista_por_nome(Bolsista *bolsistas, char *nome_bolsista);

/*Função que busca um bolsista pela matricula em uma bolsa.
Recebe como parâmetro um ponteiro de Bolsista e a matricula do bolsista que sera procurado*/
Bolsista *auxiliar_buscar_bolsista_por_matricula(Bolsista *bolsistas, long int matricula);

/*Função que edita os dados do bolsista em uma bolsa
Recebe como parâmetros dois ponteiros para Bolsista*/
void auxiliar_editar_bolsista(Bolsista *bolsista_encontrado, Bolsista *bolsistas);

/*Função que libera a memória dos bolsistas por nome em uma bolsa.
Recebe como parâmetros um ponteiro duplo para Bolsista e uma string com o nome do bolsista  */
int auxiliar_excluir_bolsista_por_nome(Bolsista **bolsistas, char *nome_bolsista);

/*Função que libera a memória dos bolsistas de uma bolsa
Recebe como parâmetro um ponteiro duplo do Bolsista*/
void auxiliar_excluir_bolsas(Bolsista **bolsistas);

/*Função que lista os bolsistas
Recebe como parâmetro um ponteiro de Bolsista*/
void listar_bolsistas(Bolsista *bolsistas);

/*Função que verifica se o CPF digitado ja está cadastrado
Recebe como parâmetro uma string com o CPF e um ponteiro de Bolsista*/
int verifica_cpf_existente(char *CPF, Bolsista *bolsistas);

/*Função que verifica se a matricula digitada ja está cadastrda.
Recebe como parâmetro uma string com a matricula e um ponteiro de Bolsista*/
int verifica_matricula_existente(long int matricula, Bolsista *bolsistas);

/*Função que verifica se um bolsista ja está cadastrado.
Recebe como parâmetro um ponteiro de Bolsista e uma string com o nome do bolsista*/
int verifica_bolsista_existente(Bolsista *bolsistas, char *nome_bolsista);

/*Função que quantifica o total de bolsistas cadastrados em uma bolsa
Recebe como parâmetro um ponteiro de Bolsista*/
int quantitativo_bolsistas(Bolsista *bolsistas);

/*Função que lê os dados de um bolsista armazenados no arquivo.txt(banco de dados)
Recebe como parâmetros um ponteiro duplo de FILE(arquivo) e um ponteiro de Bolsista*/
Bolsista *ler_bolsista_arquivo(FILE **banco_de_dados, Bolsista *bolsistas);

/*Função que insere um bolsista em um arquivo
Recebe como parâmetros um ponteiro duplo de FILE(arquivo) e um ponteiro de Bolsista */
void insere_bolsista_arquivo(FILE **banco_de_dados, Bolsista *bolsistas);

#endif // BOLSISTA_H

```
***
<br>

> **sistema.h**
```
#ifndef SISTEMA_H
#define SISTEMA_H

#include <stdio.h>
#define TAMANHO_CPF 11
#define FALHA 0
#define SUCESSO 1

/*Função que exibe o menu de opções ao usuário*/
void menu_de_opcoes();

/*Função que verifica se o arquivo foi aberto da forma correta*/
FILE * Verificacao(char * nome, char * modo);

/*Função que verifica se o CPF digitado é válido ou não dentro das condições:
    - se o CPF está no formato 000.000.000-00
    - se os numeros são inteiros
    - se contém 11 digitos 
Recebe como parâmetro uma string contendo o CPF digitado*/
int verifica_cpf_valido(char * cpf);

/*Função que verifica se a string digitada é um numero inteiro ou não
Recebe como parâmetro uma string contendo o numero digitado*/
int verifica_inteiro(char * numero);

/*Função que verifica se a string digitada está dentro das condições:
    - se é um numero inteiro E se há espaço em i[2] e i[5]
    - se está no formato DD/MM/AAAA
Recebe como parâmetro uma string contendo a data digitado*/
int verifica_data(char *data);

/*Função que verifica se a string digitada está dentro das condições:
    - se é um número inteiro 
    - se tem 8 digitos
Recebe como parâmetro uma string contendo a data digitado*/
int verifica_matricula_valida(char *numero);

/*Função que verifica se a string digitada é um float ou não
Recebe como parâmetro uma string contendo o numero digitado*/
float verifica_float(char * numero);

/*Funçõa que verifica se a string está dentro das condições:
    - se não é um caracter E se não é um espaço
Recebe como parâmetro uma string contendo o nome digitado*/
int verifica_caracter(char * nome);

/*Função que transforma os caracteres:
    - primeira letra do nome será maiúscula
    - primeira letra apos o espaço também será maiúscula
    - restante das letras serão minúsculas
Recebe como parâmetro uma string contendo o nome digitado*/
char * transforma_caracter_padrao(char * nome);


#endif // SYSTEM_H


```
***
## Estrutura do repositorio
```
Sistema de Cadastros de Bolsistas Acadêmicos
|
├── LICENSE
├── README.md
├── apps
│   ├── main
│   └── main.c
|
├── banco_de_dados
│   └── bolsas.txt
|
├── include
│   ├── bolsas.h
│   ├── bolsistas.h
│   └── sistema.h
|
└── src
    ├── bolsas.c
    ├── bolsistas.c
    └── sistema.c

```
## Desenvolvedores

| [<img loading="lazy" src="https://avatars.githubusercontent.com/u/106347376?v=4" width=115><br><sub>Alice dos Santos Pinheiro</sub>](https://github.com/AliceSantoi) |  [<img loading="lazy" src="https://avatars.githubusercontent.com/u/154340363?v=4" width=115><br><sub>Jose Danilo Santos do Nascimento</sub>](https://github.com/JoseDaniloS) |  
| :---: | :---: 