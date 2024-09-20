#include "system.h"
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
    printf("[ 8 ] - Consultar Dados do Bolsista.\n");
    printf("[ 9 ] - Consultar Bolsas Disponiveis.\n");
    printf("[ 10 ] - Sair.\n\n");
    printf("Informe a Opcao:\n");
}

void preenche_bolsa(Bolsa ** bolsas){

    char nome_bolsa[100];
    float valor_mensal;
    printf("Informe o nome da bolsa:\n");
    scanf(" %[^\n]", nome_bolsa);
    printf("Infomre o valor mensal:\n");
    scanf("%f", & valor_mensal);

    *bolsas = adiciona_bolsa(nome_bolsa,valor_mensal, *bolsas);

   
}

void preenche_bolsista(Bolsa ** bolsas){
    char nome_bolsista[100], nome_bolsa[100], curso[100];
    long int matricula, CPF;
    printf("Informe o Nome:\n");
    scanf(" %[^\n]", nome_bolsista);

    printf("Informe a Bolsa que o Aluno vai ser Vinculado:\n");
    scanf(" %[^\n]", nome_bolsa);

    printf("Informe o Curso:\n");
    scanf(" %[^\n]", curso);

    printf("Informe a Matricula:\n");
    scanf("%ld", &matricula);

    printf("Informe o CPF:\n");
    scanf("%ld", &CPF);
    adiciona_bolsista(*bolsas, nome_bolsa, nome_bolsista, matricula, curso, CPF);
}

void auxiliar_excluir_bolsista_por_nome(Bolsa ** bolsas){
    char nome_bolsista[100];
    printf("Informe o nome do bolsista:\n");
    scanf(" %[^\n]", nome_bolsista);

    excluir_bolsista_por_nome(*bolsas, nome_bolsista);
}

void auxiliar_listar_bolsistas(Bolsa ** bolsas){
    Bolsa * count = *bolsas;
    int contador_de_bolsas = 1;
    while(count != NULL){
        printf("\n\n%d- Bolsa:\n", contador_de_bolsas);
        printf("Tipo: %s\n", count->nome_bolsa);
        printf("Valor Mensal: %.1f\n", count->valor_mensal);
        printf("Data de Inicio: %d/%d/%d\n", count->inicio.dia, count->inicio.mes, count->inicio.ano);
        printf("Data de Termino: %d/%d/%d\n\n", count->termino.dia, count->termino.mes, count->termino.ano);

        //listar bolsistas da bolsa atual
        listar_bolsistas(count->bolsistas);

        //avancar para proxima bolsa
        count = count->proxima_bolsa;
        contador_de_bolsas++;
    }

    if(contador_de_bolsas == 1){
        printf("Nenhuma bolsa cadastrada!\n");
    }
}