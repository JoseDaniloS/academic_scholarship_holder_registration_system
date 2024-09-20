#include "system.h"
#include <stdio.h>

//funçao que exibe o menu de opçoes
void menu_de_opcoes(){
    printf("====SISTEMA DE CADASTRO DE BOLSISTAS ACADEMICOS====\n");
    printf("[ 1 ] - Adicionar Bolsa.\n");
    printf("[ 2 ] - Adicionar Bolsista.\n");
    printf("[ 3 ] - Excluir Bolsista.\n");
    printf("[ 4 ] - Listar Bolsistas.\n");
    printf("[ 5 ] - Buscar Bolsista.\n");
    printf("[ 6 ] - Editar Dados do Bolsista.\n");
    printf("[ 7 ] - Consultar Dados do Bolsista.\n");
    printf("[ 8 ] - Consultar Bolsas Disponiveis.\n");
    printf("[ 9 ] - Sair.\n\n");
    printf("Informe a Opcao:\n");
}

void preenche_bolsa(Bolsa ** bolsas){

    char nome_bolsa[100];
    float valor_mensal;
    printf("Informe o nome da bolsa:\n");
    scanf(" %[^\n]", nome_bolsa);
    printf("Infomre o valor mensal:\n");
    scanf("%f", & valor_mensal);

    bolsas = adiciona_bolsa(nome_bolsa,valor_mensal, *bolsas);

    return bolsas;
}