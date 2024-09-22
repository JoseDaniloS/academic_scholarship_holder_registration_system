#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "bolsistas.h"

struct bolsista{
    char nome_completo[100];
    long int matricula;
    char curso[50];
    char CPF[15];
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
    char nome_bolsista[100], curso[100], CPF[11];
    long int matricula;
    printf("Informe o Nome:\n");
    scanf(" %[^\n]", nome_bolsista);

    printf("Informe o Curso:\n");
    scanf(" %[^\n]", curso);

    printf("Informe a Matricula:\n");
    scanf("%ld", &matricula);

    printf("Informe o CPF:\n");
    scanf(" %[^\n]", CPF);

    //adicionando as informações ao novo bolsista
    strcpy(novo_bolsista->nome_completo, nome_bolsista);
    strcpy(novo_bolsista->curso, curso);
    strcpy(novo_bolsista->bolsa_associada, nome_bolsa);
    strcpy(novo_bolsista->CPF, CPF);
    novo_bolsista->matricula = matricula;

    //vinculando a lista de bolsistas da bolsa
    novo_bolsista->proximo_bolsista = *bolsistas;
    *bolsistas = novo_bolsista;
}

//função para buscar um bolsista em uma bolsa
int auxiliar_buscar_bolsista_por_nome(Bolsista * bolsistas, char * nome_bolsista){

    //caso não exista nenhum bolsista cadastrado na bolsa
    if(bolsistas == NULL){
        return 0;
    }

    //percorre a lista de bolsistas de uma determianda bolsa
    Bolsista * count = bolsistas;
    while(count != NULL){
        if(strcmp(count->nome_completo, nome_bolsista) == 0){

            printf("Bolsista: %s\n", count->nome_completo);
            printf("Matricula: %ld\n",count->matricula);
            printf("Curso: %s\n", count->curso);
            printf("CPF: %s\n", count->CPF);
            printf("Bolsa Associada: %s\n\n", count->bolsa_associada);
            return 1;
        }
        count = count->proximo_bolsista;
    }

    //caso o bolsista não esteja cadastrado na bolsa
        printf("Bolsista %s nao cadastrado em nenhuma bolsa!\n", nome_bolsista);
        return 0;
    
}
int auxiliar_excluir_bolsista_por_nome(Bolsista ** bolsistas, char * nome_bolsista){

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
            return 1;//flag indicando se o bolsista foi excluido
        }
        
        //avança para o proximo bolsista
        ant = contador_de_bolsistas;
        contador_de_bolsistas = contador_de_bolsistas->proximo_bolsista;
    }
    return 0;//flag indicando que o bolsista nao foi encontrado
}

//função para exibir todos os bolsistas de uma determinada bolsa
void listar_bolsistas(Bolsista * bolsistas){
    if(bolsistas == NULL){
        printf("Nenhum bolsista cadastrado!\n\n");
        return;
    }
    Bolsista * count = bolsistas;
    while(count != NULL){
        printf("Bolsista: %s\n", count->nome_completo);
        printf("Matricula: %ld\n",count->matricula);
        printf("Curso: %s\n", count->curso);
        printf("CPF: %s\n", count->CPF);
        printf("Bolsa Associada: %s\n\n", count->bolsa_associada);
        count = count->proximo_bolsista;
    }
}

//função para contar quantos bolsistas estão cadastrados em uma determinada bolsa
int quantitativo_bolsistas(Bolsista * bolsistas){
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

//função para ler os bolsistas armazenados no banco de dado
Bolsista * ler_bolsista_arquivo(FILE ** banco_de_dados, Bolsista * bolsistas){
    char linha[100];
    Bolsista * novo_bolsista = NULL;

    //inicia a leitura dos bolsistas
    while(fgets(linha,sizeof(linha), *banco_de_dados) && strstr(linha, "BOLSISTA:")){

        novo_bolsista = (Bolsista*)malloc(sizeof(Bolsista));
        if(novo_bolsista == NULL){
            printf("Memoria Insuficiente!\n");
            exit(1);
        }
        novo_bolsista->proximo_bolsista = bolsistas;
        bolsistas = novo_bolsista;

        //armazena as informações do bolsista
        sscanf(linha, "Bolsista: %[^\n]", novo_bolsista->nome_completo);
        fgets(linha, sizeof(linha), *banco_de_dados);
        sscanf(linha, "Matricula: %ld", &novo_bolsista->matricula);
        fgets(linha, sizeof(linha), *banco_de_dados);
        sscanf(linha, "Curso: %[^\n]", novo_bolsista->curso);
        fgets(linha, sizeof(linha), *banco_de_dados);
        sscanf(linha, "CPF: %14s", novo_bolsista->CPF);
        fgets(linha, sizeof(linha), *banco_de_dados);
        sscanf(linha, "Bolsa Associada: %[^\n]", novo_bolsista->bolsa_associada);
    }

    return bolsistas;
}


//função para armazenar no arquivo os alunos de uma determinada bolsa
void insere_bolsista_arquivo(FILE ** banco_de_dados, Bolsista * bolsistas){
    Bolsista * count = bolsistas;

    fprintf(*banco_de_dados, "BOLSISTAS:\n");

    //caso não tenha nenhum bolsista cadastrado na bolsa
    if(bolsistas == NULL){
        fprintf(*banco_de_dados,"Nenhum bolsista cadastrado!\n\n");
        return;
    }

    //armazena todos os bolsistas de uma bolsa
    while(count != NULL){
        fprintf(*banco_de_dados, "Bolsista: %s\n", count->nome_completo);
        fprintf(*banco_de_dados, "Matricula: %ld\n", count->matricula);
        fprintf(*banco_de_dados, "Curso: %s\n", count->curso);
        fprintf(*banco_de_dados, "CPF:%s\n", count->CPF);
        fprintf(*banco_de_dados, "Bolsa Associada: %s\n\n", count->bolsa_associada);

        count = count->proximo_bolsista;
    }
}