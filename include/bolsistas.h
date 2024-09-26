#ifndef BOLSISTA_H
#define BOLSISTA_H

#include <stdio.h>
#include "sistema.h"
#define MAX 100

typedef struct bolsista Bolsista;

// Funções para manipulação de bolsistas
void adiciona_bolsista(Bolsista **bolsistas, char *nome_bolsa);

void insere_bolsista_ordenado(Bolsista ** bolsistas, Bolsista * novo_bolsista);

int auxiliar_excluir_bolsista_por_nome(Bolsista **bolsistas, char *nome_bolsista);

int verifica_cpf_existente(char *CPF, Bolsista *bolsistas);

void listar_bolsistas(Bolsista *bolsistas);

void auxiliar_editar_bolsista(Bolsista *bolsista_encontrado, Bolsista *bolsistas);

Bolsista *auxiliar_buscar_bolsista_por_nome(Bolsista *bolsistas, char *nome_bolsista);

void auxiliar_excluir_bolsas(Bolsista ** bolsistas);

Bolsista *auxiliar_buscar_bolsista_por_matricula(Bolsista *bolsistas, long int matricula);

int verifica_bolsista_existente(Bolsista * bolsistas, char * nome_bolsista);

int quantitativo_bolsistas(Bolsista* bolsistas);

int quantitativo_bolsistas(Bolsista *bolsistas);

Bolsista *ler_bolsista_arquivo(FILE **banco_de_dados, Bolsista *bolsistas);

void insere_bolsista_arquivo(FILE **banco_de_dados, Bolsista *bolsistas);

int verifica_cpf_valido(char *cpf);

#endif // BOLSISTA_H