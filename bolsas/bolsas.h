#ifndef BOLSA_H
#define BOLSA_H

#include "../bolsistas/bolsistas.h"

typedef struct data Data;

typedef struct bolsa Bolsa;

Bolsa *adiciona_bolsa(char *nome_bolsa, float valor_mensal, Bolsa *bolsas);

void excluir_bolsista_por_nome(Bolsa ** bolsas);

void preenche_bolsa(Bolsa **bolsas);

void adiciona_data(Bolsa *bolsa);

Bolsa *busca_bolsa(char *nome_bolsa, Bolsa *bolsas);

void consultar_bolsas_disponiveis(Bolsa *bolsas);

void auxiliar_listar_bolsistas(Bolsa **bolsas);

void preenche_bolsista(Bolsa **bolsas);

void listar_bolsistas(Bolsista *bolsistas); 

int quantitativo_bolsistas(Bolsista *bolsistas);

#endif //BOLSA_H