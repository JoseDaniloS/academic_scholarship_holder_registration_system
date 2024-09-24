#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../include/bolsistas.h"

#define FALHA 0
#define SUCESSO 1

struct bolsista
{
    char nome_completo[MAX];
    long int matricula;
    char curso[50];
    char CPF[15];
    char bolsa_associada[MAX];
    struct bolsista *proximo_bolsista;
};

// função para adicionar um bolsista em uma bolsa disponivel
void adiciona_bolsista(Bolsista ** bolsistas, char * nome_bolsa){

    Bolsista * novo_bolsista = (Bolsista*)malloc(sizeof(Bolsista));
    if(novo_bolsista == NULL){
        printf("Memoria Insuficiente!\n");
        exit(1);
    }
    char nome_bolsista[70], curso[50], CPF[12];
    long int matricula;
    printf("Informe o Nome:\n");
    scanf(" %[^\n]", nome_bolsista);

    printf("Informe o Curso:\n");
    scanf(" %[^\n]", curso);

    printf("Informe a Matricula:\n");
    scanf("%ld", &matricula);

    do{
        printf("Informe o CPF(11 digitos):\n");
        scanf(" %[^\n]", CPF);
    }while(verifica_cpf_existente(CPF, *bolsistas) == FALHA || verifica_cpf_valido(CPF) == FALHA);

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
// função para buscar um bolsista em uma bolsa
Bolsista * auxiliar_buscar_bolsista_por_nome(Bolsista * bolsistas, char * nome_bolsista){

    //caso não exista nenhum bolsista cadastrado na bolsa
    if(bolsistas == NULL){
        return bolsistas;
    }

    //percorre a lista de bolsistas de uma determianda bolsa
    Bolsista * count = bolsistas;
    while(count != NULL){
        if(strcmp(count->nome_completo, nome_bolsista) == 0){

            printf("\nBolsista: %s\n", count->nome_completo);
            printf("Matricula: %ld\n",count->matricula);
            printf("Curso: %s\n", count->curso);
            printf("CPF: %s\n", count->CPF);
            printf("Bolsa Associada: %s\n\n", count->bolsa_associada);
            return count;
        }
        count = count->proximo_bolsista;
    }

    //caso o bolsista não esteja cadastrado na bolsa
        printf("Bolsista %s nao cadastrado em nenhuma bolsa!\n", nome_bolsista);
        return bolsistas;
    
}

int auxiliar_buscar_bolsista_por_matricula(Bolsista *bolsistas, long int matricula)
{
    if (bolsistas == NULL)
    {
        return FALHA;
    }
    Bolsista *count = bolsistas;
    while (count != NULL)
    {
        if (count->matricula == matricula)
        {
            printf("\nBolsista: %s\n", count->nome_completo);
            printf("Matricula: %ld\n", count->matricula);
            printf("Curso: %s\n", count->curso);
            printf("CPF: %s\n", count->CPF);
            printf("Bolsa Associada: %s\n\n", count->bolsa_associada);
            return SUCESSO;
        }
        count = count->proximo_bolsista;
    }
    printf("Bolsista com matricula %ld nao esta cadastrado em nenhuma bolsa!");
    return FALHA;
}

int auxiliar_excluir_bolsista_por_nome(Bolsista **bolsistas, char *nome_bolsista)
{

    Bolsista *contador_de_bolsistas = *bolsistas;
    Bolsista *ant = NULL;
    while (contador_de_bolsistas != NULL)
    {

        // encontrou o bolsista para remover
        if (strcmp(contador_de_bolsistas->nome_completo, nome_bolsista) == 0)
        {

            // caso seja o primeiro bolsista
            if (ant == NULL)
            {
                *bolsistas = contador_de_bolsistas->proximo_bolsista;
            }
            // caso seja algum bolsista apos o primeiro
            else
            {
                ant->proximo_bolsista = contador_de_bolsistas->proximo_bolsista;
            }
            printf("Bolsista '%s' removido com sucesso!\n", nome_bolsista);
            free(contador_de_bolsistas);
            return SUCESSO; // flag indicando se o bolsista foi excluido
        }

        // avança para o proximo bolsista
        ant = contador_de_bolsistas;
        contador_de_bolsistas = contador_de_bolsistas->proximo_bolsista;
    }
    return FALHA;
}

// função para exibir todos os bolsistas de uma determinada bolsa
void listar_bolsistas(Bolsista *bolsistas)
{
    if (bolsistas == NULL)
    {
        printf("Nenhum bolsista cadastrado!\n\n");
        return;
    }
    Bolsista *count = bolsistas;
    while (count != NULL)
    {
        printf("Bolsista: %s\n", count->nome_completo);
        printf("Matricula: %ld\n", count->matricula);
        printf("Curso: %s\n", count->curso);
        printf("CPF: %s\n", count->CPF);
        printf("Bolsa Associada: %s\n\n", count->bolsa_associada);
        count = count->proximo_bolsista;
    }
}

//função para verificar se o cpf ja existe na bolsa
int verifica_cpf_existente(char * CPF, Bolsista * bolsistas){
    Bolsista * count = bolsistas;

    while(count != NULL){
        
        if(strcmp(count->CPF, CPF) == 0){
            printf("CPF ja esta cadastrado.\n");
            return FALHA; //cpf ja existe no banco de dados
        }

        count = count->proximo_bolsista;
    }

    //cpf ainda nao cadastrado
    return SUCESSO;
}

// função para contar quantos bolsistas estão cadastrados em uma determinada bolsa
int quantitativo_bolsistas(Bolsista *bolsistas)
{
    int quantidade = 0;
    Bolsista *count = bolsistas;

    // conta quantos bolsistas estao cadastrados na bolsa
    while (count != NULL)
    {
        count = count->proximo_bolsista;
        quantidade++;
    }

    // retorna a quantidade de bolsistas cadastrados na bolsa
    return quantidade;
}

// função para ler os bolsistas armazenados no banco de dado
Bolsista *ler_bolsista_arquivo(FILE **banco_de_dados, Bolsista *bolsistas)
{
    char linha[100];
    Bolsista *novo_bolsista = NULL;

    // inicia a leitura dos bolsistas
    while (fgets(linha, sizeof(linha), *banco_de_dados) != NULL && !strstr(linha, "==============================="))
    {

        if (strstr(linha, "Bolsista:"))
        {

            novo_bolsista = (Bolsista *)malloc(sizeof(Bolsista));
            if (novo_bolsista == NULL)
            {
                printf("Memoria Insuficiente!\n");
                exit(1);
            }

            // armazena as informações do bolsista
            sscanf(linha, "Bolsista: %[^\n]", novo_bolsista->nome_completo);
            fgets(linha, sizeof(linha), *banco_de_dados);
            sscanf(linha, "Matricula: %ld", &novo_bolsista->matricula);
            fgets(linha, sizeof(linha), *banco_de_dados);
            sscanf(linha, "Curso: %[^\n]", novo_bolsista->curso);
            fgets(linha, sizeof(linha), *banco_de_dados);
            sscanf(linha, "CPF: %14s", novo_bolsista->CPF);
            fgets(linha, sizeof(linha), *banco_de_dados);
            sscanf(linha, "Bolsa Associada: %[^\n]", novo_bolsista->bolsa_associada);

            // adiciona o novo bolsista ao final da lista
            novo_bolsista->proximo_bolsista = NULL;
            if (bolsistas == NULL)
            {
                bolsistas = novo_bolsista;
            }
            else
            {
                Bolsista *aux = bolsistas;
                while (aux->proximo_bolsista != NULL)
                {
                    aux = aux->proximo_bolsista;
                }
                aux->proximo_bolsista = novo_bolsista;
            }
            novo_bolsista = NULL;
        }
    }

    return bolsistas;
}

// função para armazenar no arquivo os alunos de uma determinada bolsa
void insere_bolsista_arquivo(FILE **banco_de_dados, Bolsista *bolsistas)
{
    Bolsista *count = bolsistas;

    fprintf(*banco_de_dados, "BOLSISTAS:\n");

    // caso não tenha nenhum bolsista cadastrado na bolsa
    if (bolsistas == NULL)
    {
        fprintf(*banco_de_dados, "Nenhum bolsista cadastrado!\n\n");
        return;
    }

    // armazena todos os bolsistas de uma bolsa
    while (count != NULL)
    {
        fprintf(*banco_de_dados, "Bolsista: %s\n", count->nome_completo);
        fprintf(*banco_de_dados, "Matricula: %ld\n", count->matricula);
        fprintf(*banco_de_dados, "Curso: %s\n", count->curso);
        fprintf(*banco_de_dados, "CPF:%s\n", count->CPF);
        fprintf(*banco_de_dados, "Bolsa Associada: %s\n\n", count->bolsa_associada);

        count = count->proximo_bolsista;
    }
}