#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "System/system.h"

struct bolsista{
    char nome_completo[100];
    long int matricula;
    char curso[50];
    long int CPF;
    Bolsa * bolsa_associada;
    Bolsista * proximo_bolsista;
};

//função para adicionar um bolsista em uma bolsa disponivel
void adiciona_bolsista(char * nome_bolsa, char * nome_bolsista, long int matricula, char * curso, long int CPF){
    //aloca a memoria para um novo bolsista
    Bolsista * novo_bolsista = (Bolsista*)malloc(sizeof(Bolsista));
    if(novo_bolsista == NULL){
        printf("Memoria Indisponivel!\n");
        exit(1);
    }
    
    //informações do bolsista
    strcpy(novo_bolsista->nome_completo, nome_bolsista);
    strcpy(novo_bolsista->curso, curso);
    novo_bolsista->CPF = CPF;
    novo_bolsista->matricula = matricula;

    

    printf("Bolsista '%s' adicionado a bolsa '%s' com sucesso!\n", nome_bolsista, nome_bolsa);
    
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

//função para excluir um bolsista de uma bolsa
void excluir_Bolsista_por_nome(Bolsista * bolsistas, char * nome_bolsista){
    if(bolsistas == NULL){
        printf("Nenhum bolsista cadastrado com esse nome!\n");
        return;
    }

    Bolsista * count = bolsistas;
    Bolsista * ant = NULL;
    while(count != NULL && strcmp(count->nome_completo, nome_bolsista) != 0){
        ant = count;
        count = count->proximo_bolsista;
    }

    //caso não encontre o bolsista
    if(count == NULL){
        printf("Bolsista '%s' nao encontrado!\n", nome_bolsista);
        return;
    }
    //caso o bolsista seja o primeiro da lista
    if(ant == NULL){
        bolsistas = count->proximo_bolsista;
    }
    //atualiza a cabeça da lista
    else{
        ant->proximo_bolsista = count->proximo_bolsista;
    }
    //libera a memoria do bolsista
    free(count);
    printf("Bolsista '%s' excluido com sucesso!\n", nome_bolsista);
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