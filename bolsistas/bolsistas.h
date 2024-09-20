#ifndef BOLSISTA_H
#define BOLSISTA_H

#include "./bags/bolsas.h"

struct bolsista{
    char nome_completo[100];
    long int matricula;
    char curso[50];
    long int CPF;
    Bolsa * bolsa_associada;
    Bolsista * proximo_bolsista;
};

typedef struct bolsista Bolsista;

void adiciona_bolsista(Bolsa * bolsas,char * nome_bolsa, char * nome_bolsista, long int matricula, char * curso, long int CPF);

int quantitativo_bolsistas(Bolsista * bolsistas);

void excluir_bolsista_por_nome(Bolsa * bolsas, char * nome);

Bolsista * busca_bolsista_por_nome(Bolsista * bolsistas, char * nome_bolsista);

int quantitativo_bolsistas(Bolsista * bolsistas);

void listar_bolsistas(Bolsista * bolsistas);

#endif //BOLSISTA_H