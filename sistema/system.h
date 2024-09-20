#ifndef SYSTEM_H
#define SYSTEM_H

#include "./bags/bolsas.h"// Inclui o arquivo que contém a estrutura e as funções relacionadas a 'Bolsa'
#include "./scholarship_holders/bolsistas.h"// Inclui o arquivo que contém a estrutura e as funções relacionadas a 'Bolsista'

// Exibe o menu de opções ao usuário
void menu_de_opcoes();

// Adiciona uma nova bolsa ao sistema
void preenche_bolsa(Bolsa ** bolsas);

// Adiciona um bolsista a uma bolsa existente
void preenche_bolsista(Bolsa ** bolsas);

// Remove um bolsista do sistema, baseado no nome
void auxiliar_excluir_bolsista_por_nome(Bolsa ** bolsas);

// Lista todas as bolsas e os bolsistas associados a cada bolsa
void auxiliar_listar_bolsistas(Bolsa ** bolsas);

#endif // SYSTEM_H
