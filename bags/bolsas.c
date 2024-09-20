#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "bolsas.h"

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

Bolsa * adiciona_bolsa(char * nome_bolsa, float valor_mensal, Bolsa * bolsas){
    Bolsa * nova_bolsa = (Bolsa*)malloc(sizeof(Bolsa));
    if(nova_bolsa ==  NULL){
        printf("Memoria Insuficiente!\n");
        exit(1);
    }
    
    strcpy(nova_bolsa->nome_bolsa, nome_bolsa);
    nova_bolsa->valor_mensal = valor_mensal;
    nova_bolsa->bolsistas = NULL;

    //Adiciona datas de inicio e termino da bolsa
    adiciona_data(nova_bolsa);

    //a nova bolsa aponta para a lista existente de bolsas
    nova_bolsa->proxima_bolsa = bolsas;

    //retorna a nova cabeça da lista
    return nova_bolsa;
}

//funçao para adicionar datas de incio e termino da bolsa
void adiciona_data(Bolsa * bolsa){
    printf("Informe a data de inicio\nFormato: DD MM AAAA\n");
    scanf("%d %d %d", &bolsa->inicio.dia, &bolsa->inicio.mes, &bolsa->inicio.ano);

    printf("Informe a data de termino\n Formato: DD MM AAAA\n");
    scanf("%d %d %d", &bolsa->termino.dia, &bolsa->termino.mes, &bolsa->termino.ano);
}

Bolsa * busca_bolsa(char * nome_bolsa, Bolsa * bolsas){
    Bolsa * count = bolsas;

    //caso não exista nenhuma bolsa na lista
    if(bolsas == NULL){
        printf("Nao existem bolsas cadastradas!\n");
        return NULL;
    }

    //percorre as bolsas ate encontrar a bolsa pesquisada
    while(count != NULL && strcmp(count->nome_bolsa, nome_bolsa) != 0){
        count = count->proxima_bolsa;
    }

    //caso não exista a bolsa que esta procurando retorna NULL
    if(count == NULL){
        printf("Bolsa nao cadastrada!\n");
        return NULL;
    }
    //caso a bolsa seja encontrada, retorna o nó com as informações da bolsa
    else{
        printf("Bolsa %s encontrada!\n", count->nome_bolsa);
        return count;
    }
}

void consultar_bolsas_disponiveis(Bolsa * bolsas){

    //caso não exista bolsas cadastradas
    if(bolsas == NULL){
        printf("Nao ha bolsas cadastradas!\n");
        return;
    }
    Bolsa * count = bolsas;
    
    //printa na tela as informações das bolsas
    while(count != NULL){
        printf("Bolsa: %s\n", count->nome_bolsa);
        printf("Valor Mensal: %.1f\n", count->valor_mensal);
        printf("Data de inicio: %d/%d/%d\n", count->inicio.dia, count->inicio.mes, count->inicio.ano);
        printf("Data de Termino:%d/%d/%d\n", count->termino.dia, count->termino.mes, count->termino.ano);
        printf("Quantidade de Bolsistas Cadastrados: %d\n", quantitativo_bolsistas(count->bolsistas));
        printf("\n\n");
        count = count->proxima_bolsa;
    }

}
