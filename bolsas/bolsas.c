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

//função para adicionar uma nova bolsa na lista
Bolsa * adiciona_bolsa(char * nome_bolsa, float valor_mensal, Bolsa * bolsas){

    //aloca a memoria de uma nova bolsa
    Bolsa * nova_bolsa = (Bolsa*)malloc(sizeof(Bolsa));
    if(nova_bolsa ==  NULL){
        printf("Memoria Insuficiente!\n");
        exit(1);
    }
    
    //adiciona as informaçoes na bolsa
    strcpy(nova_bolsa->nome_bolsa, nome_bolsa);
    nova_bolsa->valor_mensal = valor_mensal;
    nova_bolsa->bolsistas = NULL;

    //Adiciona datas de inicio e termino da bolsa
    adiciona_data(nova_bolsa);

    //a nova bolsa aponta para a lista existente de bolsas
    nova_bolsa->proxima_bolsa = bolsas;
    printf("%s Adicionada com sucesso!\n", nome_bolsa);
    //retorna a nova cabeça da lista
    return nova_bolsa;
}

//função para excluir um bolsista de uma bolsa
void excluir_bolsista_por_nome(Bolsa ** bolsas){
    if(*bolsas == NULL){
        printf("Nenhuma Bolsa Cadastrada!\n");
        return;
    }
    char nome_bolsista[100];
    printf("Informe o nome do bolsista:\n");
    scanf(" %[^\n]", nome_bolsista);
    Bolsa * count = *bolsas;
    //percorrer todas as bolsas ate encontrar o bolsista
    while(count != NULL){

        auxiliar_excluir_bolsista_por_nome(&count->bolsistas, nome_bolsista);
        count = count->proxima_bolsa;
    }

    printf("Bolsista '%s' nao encontrado!\n", nome_bolsista);
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

//funçao para consultar as bolsas disponiveis
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

void preenche_bolsista(Bolsa ** bolsas){
    char nome_bolsa[100];
    Bolsa * bolsa_encontrada = NULL;

    printf("Informe a Bolsa que o Aluno vai ser Vinculado:\n");
    scanf(" %[^\n]", nome_bolsa);

    //busca a bolsa que o bolsista vai ser adicionado
    bolsa_encontrada = busca_bolsa(nome_bolsa, *bolsas);

    if(bolsa_encontrada != NULL){
        adiciona_bolsista(&bolsa_encontrada->bolsistas, nome_bolsa);
    }
    else{
        printf("Bolsa '%s' nao encontrada!\n", nome_bolsa);
    }
}