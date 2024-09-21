#ifndef BOLSISTA_H
#define BOLSISTA_H


typedef struct bolsista Bolsista;

void adiciona_bolsista(Bolsista **bolsistas, char *nome_bolsa);

Bolsista *busca_bolsista_por_nome(Bolsista *bolsistas, char *nome_bolsista);

void auxiliar_excluir_bolsista_por_nome(Bolsista **bolsistas, char *nome_bolsista);

void listar_bolsistas(Bolsista *bolsistas);

int quantitativo_bolsistas(Bolsista *bolsistas);

#endif //BOLSISTA_H