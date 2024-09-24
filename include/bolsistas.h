#ifndef BOLSISTA_H
#define BOLSISTA_H

#include <stdio.h>
#include "sistema.h"
#define MAX 100

typedef struct bolsista Bolsista;

// Funções para manipulação de bolsistas
void adiciona_bolsista(Bolsista** bolsistas, char* nome_bolsa);
int verifica_cpf_existente(char* CPF, Bolsista* bolsistas);
int auxiliar_buscar_bolsista_por_nome(Bolsista* bolsistas, char* nome_bolsista);
int auxiliar_excluir_bolsista_por_nome(Bolsista** bolsistas, char* nome_bolsista);
void listar_bolsistas(Bolsista* bolsistas);
int quantitativo_bolsistas(Bolsista* bolsistas);
Bolsista* ler_bolsista_arquivo(FILE** banco_de_dados, Bolsista* bolsistas);
void insere_bolsista_arquivo(FILE** banco_de_dados, Bolsista* bolsistas);
int verifica_cpf_valido(char* cpf); // Declare a função verifica_cpf_valido se ela existir

#endif //BOLSISTA_H