#ifndef BOLSISTA_H
#define BOLSISTA_H

#include <stdio.h>

typedef struct bolsista Bolsista;

void adiciona_bolsista(Bolsista **bolsistas, char *nome_bolsa);

int auxiliar_buscar_bolsista_por_nome(Bolsista *bolsistas, char *nome_bolsista);

int auxiliar_excluir_bolsista_por_nome(Bolsista **bolsistas, char *nome_bolsista);

void listar_bolsistas(Bolsista *bolsistas);

int quantitativo_bolsistas(Bolsista *bolsistas);

void insere_bolsista_arquivo(FILE ** banco_de_dados, Bolsista * bolsistas);

Bolsista * ler_bolsista_arquivo(FILE ** banco_de_dados, Bolsista * bolsistas);

#endif //BOLSISTA_H