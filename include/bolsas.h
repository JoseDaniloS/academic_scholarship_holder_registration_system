#ifndef BOLSA_H
#define BOLSA_H

#include "bolsistas.h"
#include <stdio.h>

typedef struct data Data;

typedef struct bolsa Bolsa;

// Funções para manipulação de bolsas
void insere_bolsa(Bolsa** bolsas);

Bolsa* busca_bolsa(char* nome_bolsa, Bolsa* bolsas);

void excluir_bolsas(Bolsa ** bolsas);

void consultar_bolsas_disponiveis(Bolsa** bolsas);

void edita_dados_bolsista(Bolsa **bolsas);

void ler_bolsa_arquivo(FILE** banco_de_dados, Bolsa** bolsas);

void insere_bolsa_arquivo(FILE** banco_de_dados, Bolsa** bolsas);

void auxiliar_listar_bolsistas(Bolsa** bolsas);

void buscar_bolsista_por_matricula(Bolsa **bolsas);

void adiciona_bolsista_na_bolsa(Bolsa** bolsas);

void excluir_bolsista_por_nome(Bolsa** bolsas);

int verifica_bolsa_existente(Bolsa * bolsas, char * nome_bolsa);

void menu_busca_bolsista(Bolsa** bolsas);

void buscar_bolsista_por_nome(Bolsa** bolsas);

int bolsa_vazia(Bolsa* bolsas);

#endif // BOLSA_H