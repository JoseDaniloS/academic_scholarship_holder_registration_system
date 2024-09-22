#include "system.h"
#include <stdlib.h>
#include <stdio.h>

//funçao que exibe o menu de opçoes
void menu_de_opcoes(){
    printf("====SISTEMA DE CADASTRO DE BOLSISTAS ACADEMICOS====\n");
    printf("[ 1 ] - Adicionar Bolsa.\n");
    printf("[ 2 ] - Adicionar Bolsista.\n");
    printf("[ 3 ] - Excluir Bolsista.\n");
    printf("[ 4 ] - Excluir Bolsa.\n");
    printf("[ 5 ] - Listar Bolsistas.\n");
    printf("[ 6 ] - Buscar Bolsista.\n");
    printf("[ 7 ] - Editar Dados do Bolsista.\n");
    printf("[ 8 ] - Consultar Bolsas Disponiveis.\n");
    printf("[ 9 ] - Sair.\n\n");
    printf("Informe a Opcao:\n");
}

//Função para abrir/criar arquivo e retornar este arquivo
FILE * Verificacao(char * nome, char * modo){
    FILE * arquivo = fopen(nome, modo);
    if(arquivo == NULL){
        printf("Can't open the file\n");
        exit(1);
    }
    else{
        printf("File open!\n");
    }

    return arquivo;
}