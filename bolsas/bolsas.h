#ifndef BOLSA_H
#define BOLSA_H

#include "./scholarship_holders/bolsistas.h"

struct data{
    int dia;
    int mes;
    int ano;
};

struct bolsa{
    char nome_bolsa[100];
    float valor_mensal;
    Data inicio;
    Data termino;
    Bolsista * bolsistas;
    Bolsa * proxima_bolsa;
};

typedef struct data Data;
typedef struct bolsa Bolsa;

Bolsa * adiciona_bolsa(char * nome_bolsa, float valor_mensal, Bolsa * bolsas);

void adiciona_data(Bolsa * bolsa);

Bolsa * busca_bolsa(char * nome_bolsa, Bolsa * bolsas);

void consultar_bolsas_disponiveis(Bolsa * bolsas);

#endif //BOLSA_H