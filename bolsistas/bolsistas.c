#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "bolsistas.h"

struct bolsista{
    char nome_completo[100];
    long int matricula;
    char curso[50];
    long int CPF;
    char bolsa_associada[100];
    struct bolsista * proximo_bolsista;
};

//função para adicionar um bolsista em uma bolsa disponivel
void adiciona_bolsista(Bolsista ** bolsistas, char * nome_bolsa){

    Bolsista * novo_bolsista = (Bolsista*)malloc(sizeof(Bolsista));
    if(novo_bolsista == NULL){
        printf("Memoria Insuficiente!\n");
        exit(1);
    }
    char nome_bolsista[100], curso[100];
    long int matricula, CPF;
    printf("Informe o Nome:\n");
    scanf(" %[^\n]", nome_bolsista);

    printf("Informe o Curso:\n");
    scanf(" %[^\n]", curso);

    printf("Informe a Matricula:\n");
    scanf("%ld", &matricula);

    printf("Informe o CPF:\n");
    scanf("%ld", &CPF);

    //adicionando as informações ao novo bolsista
    strcpy(novo_bolsista->nome_completo, nome_bolsista);
    strcpy(novo_bolsista->curso, curso);
    strcpy(novo_bolsista->bolsa_associada, nome_bolsa);
    novo_bolsista->matricula = matricula;
    novo_bolsista->CPF = CPF;

    //vinculando a lista de bolsistas da bolsa
    novo_bolsista->proximo_bolsista = *bolsistas;
    *bolsistas = novo_bolsista;
}

//função para buscar um bolsista em uma bolsa
Bolsista * busca_bolsista_por_nome(Bolsista * bolsistas, char * nome_bolsista){

    //caso não exista nenhum bolsista cadastrado na bolsa
    if(bolsistas == NULL){
        return bolsistas;
    }

    //percorre a lista de bolsistas de uma determianda bolsa
    Bolsista * count = bolsistas;
    while(count != NULL && strcmp(count->nome_completo, nome_bolsista) != 0){
        count = count->proximo_bolsista;
    }
    
    //caso o bolsista esteja cadastrado na bolsa
    if(strcmp(count->nome_completo, nome_bolsista) == 0){
        return count;
    }

    //caso o bolsista não esteja cadastrado na bolsa
    else{
        printf("Bolsista %s nao cadastrado em nenhuma bolsa!\n", nome_bolsista);
        return NULL;
    }
}
void auxiliar_excluir_bolsista_por_nome(Bolsista ** bolsistas, char * nome_bolsista){

    Bolsista * contador_de_bolsistas = *bolsistas;
    Bolsista * ant = NULL;
    while(contador_de_bolsistas != NULL){

         //encontrou o bolsista para remover
        if(strcmp(contador_de_bolsistas->nome_completo, nome_bolsista) == 0){

            //caso seja o primeiro bolsista
            if(ant == NULL){
                *bolsistas = contador_de_bolsistas->proximo_bolsista;
            }
            //caso seja algum bolsista apos o primeiro
            else{
                ant->proximo_bolsista = contador_de_bolsistas->proximo_bolsista;
            }
            printf("Bolsista '%s' removido com sucesso!\n", nome_bolsista);
            free(contador_de_bolsistas);
            return;
        }
        
        //avança para o proximo bolsista
        ant = contador_de_bolsistas;
        contador_de_bolsistas = contador_de_bolsistas->proximo_bolsista;
    }
}

void listar_bolsistas(Bolsista * bolsistas){
    if(bolsistas == NULL){
        printf("Nenhum bolsista cadastrado!\n");
        return;
    }
    Bolsista * count = bolsistas;
    while(count != NULL){
        printf("Bolsista: %s\n", count->nome_completo);
        printf("Matricula: %ld\n",count->matricula);
        printf("Curso: %s\n", count->curso);
        printf("CPF: %ld\n", count->CPF);
        count = count->proximo_bolsista;
    }
}

//função para contar quantos bolsistas estão cadastrados em uma determinada bolsa
int quantitativo_bolsistas(Bolsista * bolsistas){

    //caso nao exista nenhum bolsista cadastrado na bolsa
    if(bolsistas == NULL){
        return 0;
    }
    int quantidade = 0;
    Bolsista * count = bolsistas;
    //conta quantos bolsistas estao cadastrados na bolsa
    while(count != NULL){
        count = count->proximo_bolsista;
        quantidade++;
    }

    //retorna a quantidade de bolsistas cadastrados na bolsa
    return quantidade;
}