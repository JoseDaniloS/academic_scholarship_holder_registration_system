#ifndef BOLSISTA_H
#define BOLSISTA_H

#include "System/system.h"

typedef struct bolsista Bolsista;

void adiciona_bolsista(Bolsa * bolsas,char * nome_bolsa, char * nome_bolsista, long int matricula, char * curso, long int CPF);

int quantitativo_bolsistas(Bolsista * bolsistas);

void excluir_bolsista_por_nome(Bolsista * bolsistas, char * nome_bolsista);

Bolsista * busca_bolsista_por_nome(Bolsista * bolsistas, char * nome_bolsista);

int quantitativo_bolsistas(Bolsista * bolsistas);

void listar_bolsistas(Bolsista * bolsistas);

#endif //BOLSISTA_H