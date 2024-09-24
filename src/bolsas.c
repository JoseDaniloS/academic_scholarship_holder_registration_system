#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../include/bolsas.h"

#define SUCESSO 1
#define FALHA 0
#define MAX 100

struct data
{
    int dia;
    int mes;
    int ano;
};

struct bolsa
{
    char nome_bolsa[MAX];
    float valor_mensal;
    Data inicio;
    Data termino;
    Bolsista *bolsistas;
    Bolsa *proxima_bolsa;
};


void insere_bolsa(Bolsa **bolsas)
{

    char nome_bolsa[30];
    float valor_mensal;
    char c_numero[10];

    printf("Informe o nome da bolsa:\n");
    scanf(" %[^\n]", nome_bolsa);

    // verifica se o valor mensal está no formato correto
    do
    {
        printf("Informe o valor mensal(Entre 100 - 700):\n");
        scanf("%s", c_numero);
        valor_mensal = verifica_float(c_numero);
        if (valor_mensal == FALHA)
        {
            printf("Valor Invalido! Digite novamente.\n");
        }
    } while (valor_mensal == FALHA || valor_mensal < 100 || valor_mensal > 700);

    // aloca a memoria de uma nova bolsa
    Bolsa *nova_bolsa = (Bolsa *)malloc(sizeof(Bolsa));
    if (nova_bolsa == NULL)
    {
        printf("Memoria Insuficiente!\n");
        exit(1);
    }

    // adiciona as informaçoes na bolsa
    strcpy(nova_bolsa->nome_bolsa, nome_bolsa);
    nova_bolsa->valor_mensal = valor_mensal;
    nova_bolsa->bolsistas = NULL;
    nova_bolsa->proxima_bolsa = NULL;

    // Adiciona datas de início e término da bolsa
    printf("Informe a data de inicio\nFormato: DD MM AAAA\n");
    scanf("%d %d %d", &nova_bolsa->inicio.dia, &nova_bolsa->inicio.mes, &nova_bolsa->inicio.ano);

    printf("Informe a data de termino\nFormato: DD MM AAAA\n");
    scanf("%d %d %d", &nova_bolsa->termino.dia, &nova_bolsa->termino.mes, &nova_bolsa->termino.ano);

    // a nova bolsa aponta para a lista existente de bolsas
    nova_bolsa->proxima_bolsa = *bolsas;
    printf("%s Adicionada com sucesso!\n", nome_bolsa);
    // retorna a nova cabeça da lista
    *bolsas = nova_bolsa;
}
// função para excluir um bolsista de uma bolsa
void excluir_bolsista_por_nome(Bolsa ** bolsas){

    if(bolsa_vazia(*bolsas) == FALHA){
        return;
    }
    char nome_bolsista[40];
    printf("Informe o nome do bolsista:\n");
    scanf(" %[^\n]", nome_bolsista);

    Bolsa * count = *bolsas;
    int bolsista_excluido = FALHA;
    //percorrer todas as bolsas ate encontrar o bolsista
    while(count != NULL){

        if(auxiliar_excluir_bolsista_por_nome(&count->bolsistas, nome_bolsista)){
            bolsista_excluido = SUCESSO;
        }
        count = count->proxima_bolsa;
    }

    if(bolsista_excluido == FALHA){
         printf("Bolsista '%s' nao encontrado!\n", nome_bolsista);
    }
}


// função para buscar um bolsista
void menu_busca_bolsista(Bolsa ** bolsas){

    if(bolsa_vazia(*bolsas) == FALHA){
        return;
    }

    char c_numero[2];
    int opcao = 0;

    do{
        printf("1 - Buscar Bolsista por Nome:\n");
        printf("2 - Buscar Bolsista por Matricula:\n");
        printf("3 - Sair..\n");
        scanf("%s", c_numero);
        opcao = verifica_inteiro(c_numero);

        switch (opcao){
        case 1:
            buscar_bolsista_por_nome(bolsas);
            break;
        case 2:
            buscar_bolsista_por_matricula(bolsas);
            break;
        case 3:
            printf("Voltando ao menu anterior...\n");
            break;
        default:
            printf("Opcao Invalida! Por favor, escolha entre 1 e 3.\n");
            break;
        }
    }while(opcao != 3);

    return;
}

// função para buscar um bolsista por nome
void buscar_bolsista_por_nome(Bolsa ** bolsas){

    //caso nao tenha nenhuma bolsa cadastrada
    if(bolsa_vazia(*bolsas) == FALHA){
        return;
    }

    char nome_bolsista[40];

    printf("Informe o nome do Bolsista:\n");
    scanf(" %[^\n]", nome_bolsista);

    Bolsa * count = *bolsas;
    int verificador = FALHA;

    while(count != NULL){
        verificador = auxiliar_buscar_bolsista_por_nome(count->bolsistas, nome_bolsista);
        count = count->proxima_bolsa;
    }
    //caso nao encontre o bolsista
    if(verificador == FALHA){
        printf("Bolsista nao encontrado!\n");
        return;
    }
    //caso encontre retorna para o menu
    else{
        return;
    }    
}

void buscar_bolsista_por_matricula(Bolsa **bolsas)
{
    long int matricula;
    if (*bolsas == NULL)
    {
        printf("Nao há bolsas cadastradas.");
        return;
    }

    printf("Informe a matricula do bolsista: ");
    scanf("%ld", &matricula);
    Bolsa *count = *bolsas;
    int verificador = FALHA;
    while (count != NULL)
    {
        verificador = auxiliar_buscar_bolsista_por_matricula(count->bolsistas, matricula);
        count = count->proxima_bolsa;
    }
    if (verificador == FALHA)
    {
        printf("Bolsista nao encontrado");
        return;
    }
    else
    {
        return;
    }
}



Bolsa *busca_bolsa(char *nome_bolsa, Bolsa *bolsas)
{
    Bolsa *count = bolsas;

    // caso não exista nenhuma bolsa na lista
    if (bolsas == NULL)
    {
        printf("Nao existem bolsas cadastradas!\n");
        return NULL;
    }

    // percorre as bolsas ate encontrar a bolsa pesquisada
    while (count != NULL && strcmp(count->nome_bolsa, nome_bolsa) != 0)
    {
        count = count->proxima_bolsa;
    }

    // caso não exista a bolsa que esta procurando retorna NULL
    if (count == NULL)
    {
        printf("Bolsa nao cadastrada!\n");
        return NULL;
    }
    // caso a bolsa seja encontrada, retorna o nó com as informações da bolsa
    else
    {
        printf("Bolsa %s encontrada!\n", count->nome_bolsa);
        return count;
    }
}

// funçao para consultar as bolsas disponiveis
void consultar_bolsas_disponiveis(Bolsa **bolsas)
{

    // caso não exista bolsas cadastradas
    if (*bolsas == NULL)
    {
        printf("Nao ha bolsas cadastradas!\n");
        return;
    }
    Bolsa *count = *bolsas;

    // printa na tela as informações das bolsas
    while (count != NULL)
    {
        printf("Bolsa: %s\n", count->nome_bolsa);
        printf("Valor Mensal: %.1f\n", count->valor_mensal);
        printf("Data de inicio: %02d/%02d/%04d\n", count->inicio.dia, count->inicio.mes, count->inicio.ano);
        printf("Data de Termino:%02d/%02d/%04d\n", count->termino.dia, count->termino.mes, count->termino.ano);
        printf("Quantidade de Bolsistas Cadastrados: %d\n", quantitativo_bolsistas(count->bolsistas));
        printf("\n\n");
        count = count->proxima_bolsa;
    }
}

void auxiliar_listar_bolsistas(Bolsa **bolsas)
{
    Bolsa *count = *bolsas;
    int contador_de_bolsas = 1;
    while (count != NULL)
    {
        printf("\n\n%d- Bolsa:\n", contador_de_bolsas);
        printf("Tipo: %s\n", count->nome_bolsa);
        printf("Valor Mensal: %.1f\n", count->valor_mensal);
        printf("Data de Inicio: %02d/%02d/%04d\n", count->inicio.dia, count->inicio.mes, count->inicio.ano);
        printf("Data de Termino: %02d/%02d/%04d\n\n", count->termino.dia, count->termino.mes, count->termino.ano);

        // listar bolsistas da bolsa atual
        listar_bolsistas(count->bolsistas);

        // avancar para proxima bolsa
        count = count->proxima_bolsa;
        contador_de_bolsas++;
    }

    if (contador_de_bolsas == 1)
    {
        printf("Nenhuma bolsa cadastrada!\n");
    }
}

// função para preencher dados de um bolsista
void adiciona_bolsista_na_bolsa(Bolsa **bolsas)
{
    char nome_bolsa[MAX];
    Bolsa *bolsa_encontrada = NULL;

    printf("Informe a Bolsa que o Aluno vai ser Vinculado:\n");
    scanf(" %[^\n]", nome_bolsa);

    // busca a bolsa que o bolsista vai ser adicionado
    bolsa_encontrada = busca_bolsa(nome_bolsa, *bolsas);

    if (bolsa_encontrada != NULL)
    {
        adiciona_bolsista(&bolsa_encontrada->bolsistas, nome_bolsa);
    }
    else
    {
        printf("Bolsa '%s' nao encontrada!\n", nome_bolsa);
    }
}

// funçao para escanear todas as bolsas armazenadas no banco de dado
void ler_bolsa_arquivo(FILE **banco_de_dados, Bolsa **bolsas)
{
    char linha[MAX];
    Bolsa *nova_bolsa = NULL;

    while (fgets(linha, sizeof(linha), *banco_de_dados) != NULL)
    {
        // verifica se a linha escaneada contem a palavra Bolsa
        if (strstr(linha, "BOLSA:"))
        {

            nova_bolsa = (Bolsa *)malloc(sizeof(Bolsa));
            if (nova_bolsa == NULL)
            {
                printf("Memoria Insuficiente!\n");
                exit(1);
            }
            nova_bolsa->proxima_bolsa = *bolsas;
            *bolsas = nova_bolsa;
            nova_bolsa->bolsistas = NULL;
        }

        // escaneia todas as informações das bolsas
        else if (nova_bolsa != NULL)
        {

            if (strstr(linha, "Tipo:"))
            {
                sscanf(linha, "Tipo: %[^\n]", nova_bolsa->nome_bolsa);
            }
            else if (strstr(linha, "Valor Mensal:"))
            {
                sscanf(linha, "Valor Mensal: %f", &nova_bolsa->valor_mensal);
            }
            else if (strstr(linha, "Data de Inicio:"))
            {
                sscanf(linha, "Data de Inicio: %d/%d/%d", &nova_bolsa->inicio.dia, &nova_bolsa->inicio.mes, &nova_bolsa->inicio.ano);
            }
            else if (strstr(linha, "Data de Termino:"))
            {
                sscanf(linha, "Data de Termino: %d/%d/%d", &nova_bolsa->termino.dia, &nova_bolsa->termino.mes, &nova_bolsa->termino.ano);
            }

            // ler os dados dos bolsistas
            else if (strstr(linha, "BOLSISTAS:"))
            {
                nova_bolsa->bolsistas = ler_bolsista_arquivo(banco_de_dados, nova_bolsa->bolsistas);
            }
        }
    }
}

// funçao para armazenar uma bolsa e seus respectivos campos
void insere_bolsa_arquivo(FILE **banco_de_dados, Bolsa **bolsas)
{
    Bolsa *count = *bolsas;
    if (*bolsas == NULL)
    {
        return;
    }
    // percorre todas as bolsas armazenando suas informações no banco de dados
    while (count != NULL)
    {
        fprintf(*banco_de_dados, "===============================\n");
        fprintf(*banco_de_dados, "BOLSA:\nTipo: %s\n", count->nome_bolsa);
        fprintf(*banco_de_dados, "Valor Mensal: %.1f\n", count->valor_mensal);
        fprintf(*banco_de_dados, "Data de Inicio: %02d/%02d/%04d\n", count->inicio.dia, count->inicio.mes, count->inicio.ano);
        fprintf(*banco_de_dados, "Data de Termino: %02d/%02d/%04d\n\n", count->termino.dia, count->termino.mes, count->termino.ano);

        // insere os bolsistas associados à bolsa no arquivo
        insere_bolsista_arquivo(banco_de_dados, count->bolsistas);

        fprintf(*banco_de_dados, "===============================\n\n");
        count = count->proxima_bolsa;
    }
}

// terminar função de editar os dados, adiconando a opção de editar por nome ou matricula
// corrigir o erro do arquivo, possível problema: caminho não encontrado
void edita_dados_bolsista(Bolsa **bolsas)
{
    char nome_bolsista[MAX];
    Bolsa *bolsista_encontrado;
    printf("Digite o nome do bolsista que deseja editar: ");
    scanf("%[^\n]", nome_bolsista);
    // buscar_bolsista_por_nome(*bolsas);
    if (bolsista_encontrado != NULL)
    {
    }
}

//função para verificar se a lista de bolsas está vazia
int bolsa_vazia(Bolsa * bolsas){
    if(bolsas == NULL){
        printf("Nao ha bolsas cadastradas!\n");
        return FALHA;
    }
    return SUCESSO;
}
