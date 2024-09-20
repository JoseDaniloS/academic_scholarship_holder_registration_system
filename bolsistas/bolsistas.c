#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "bolsistas.h"

//função para adicionar um bolsista em uma bolsa disponivel
void adiciona_bolsista(Bolsa * bolsas ,char * nome_bolsa, char * nome_bolsista, long int matricula, char * curso, long int CPF){
    //busca pela bolsa na lista de bolsas cadastradas
    Bolsa * bolsa_encontrada = busca_bolsa(nome_bolsa, bolsas);
    if(bolsa_encontrada == NULL){
        printf("Bolsa nao encontrada!\n");
        return;
    }
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

    novo_bolsista->bolsa_associada = bolsa_encontrada;  // relaciona a bolsa ao bolsista
    novo_bolsista->proximo_bolsista = bolsa_encontrada->bolsistas;
    bolsa_encontrada->bolsistas = novo_bolsista;  // atualiza a lista de bolsistas na bolsa

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
void excluir_Bolsista_por_nome(Bolsa * bolsas, char * nome_bolsista){
    if(bolsas == NULL){
        printf("Nenhuma Bolsa Cadastrada!\n");
        return;
    }

    Bolsa * count = bolsas;
    Bolsista * contador_de_bolsistas = NULL;
    Bolsista * ant = NULL;
    //percorrer todas as bolsas ate encontrar o bolsista
    while(count != NULL){

        contador_de_bolsistas = count->bolsistas;
        ant = NULL;

        //percorre todos os bolsistas ate encontrar o que vai excluir
        while(contador_de_bolsistas != NULL){

            //encontrou o bolsista para remover
            if(strcmp(contador_de_bolsistas->nome_completo, nome_bolsista) == 0){

                //caso seja o primeiro bolsista
                if(ant == NULL){
                    count->bolsistas = contador_de_bolsistas->proximo_bolsista;
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
        
        //avança para proxima bolsa
        count = count->proxima_bolsa;
    }

    printf("Bolsista '%s' nao encontrado!\n", nome_bolsista);
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