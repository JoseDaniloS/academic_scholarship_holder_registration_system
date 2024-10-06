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