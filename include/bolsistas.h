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