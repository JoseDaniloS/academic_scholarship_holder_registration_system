#ifndef SYSTEM_H
#define SYSTEM_H

//#include "bolsas.h"// Inclui o arquivo que contém a estrutura e as funções relacionadas a 'Bolsa'
#include <stdio.h>
#define TAMANHO_CPF 11
#define FALHA 0
#define SUCESSO 1

// Exibe o menu de opções ao usuário
void menu_de_opcoes();

FILE * Verificacao(char * nome, char * modo);

int verifica_cpf_valido(char * cpf);

int verifica_inteiro(char * numero);

int verifica_matricula_valida(char *numero);

float verifica_float(char * numero);

int verifica_caracter(char * nome);

char * transforma_caracter_padrao(char * nome);


#endif // SYSTEM_H
