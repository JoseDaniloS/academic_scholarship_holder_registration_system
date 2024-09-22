#ifndef SYSTEM_H
#define SYSTEM_H

#include "../bolsas/bolsas.h"// Inclui o arquivo que contém a estrutura e as funções relacionadas a 'Bolsa'
#include <stdio.h>

// Exibe o menu de opções ao usuário
void menu_de_opcoes();

FILE * Verificacao(char * nome, char * modo);

#endif // SYSTEM_H
