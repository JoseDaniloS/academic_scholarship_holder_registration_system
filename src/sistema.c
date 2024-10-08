#include "../include/sistema.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void menu_de_opcoes()
{
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

FILE *Verificacao(char *nome, char *modo)
{
    FILE *arquivo = fopen(nome, modo);
    if (arquivo == NULL)
    {
        printf("Can't open the file\n");
        exit(1);
    }
    else
    {
        printf("File open!\n");
    }

    return arquivo;
}

int verifica_cpf_valido(char *cpf)
{

    if (strlen(cpf) != 14 ||
        !isdigit(cpf[0]) || !isdigit(cpf[1]) || !isdigit(cpf[2]) || cpf[3] != '.' ||
        !isdigit(cpf[4]) || !isdigit(cpf[5]) || !isdigit(cpf[6]) || cpf[7] != '.' ||
        !isdigit(cpf[8]) || !isdigit(cpf[9]) || !isdigit(cpf[10]) || cpf[11] != '-' ||
        !isdigit(cpf[12]) || !isdigit(cpf[13]))
    {

        printf("CPF deve estar no formato 000.000.000-00.\nDigite Novamente.\n");
        return FALHA;
    }

    char cpf_sem_formato[TAMANHO_CPF + 1];
    int j = 0;

    for (int i = 0; cpf[i] != '\0'; i++)
    {
        if (isdigit(cpf[i]))
        {
            cpf_sem_formato[j++] = cpf[i];
        }
    }
    cpf_sem_formato[j] = '\0';

    if (strlen(cpf_sem_formato) != TAMANHO_CPF)
    {
        printf("CPF deve conter exatamente 11 digitos.\nDigite Novamente.\n");
        return FALHA;
    }

    return SUCESSO;
}

int verifica_inteiro(char *numero)
{

    if (numero[0] == '\0')
    {
        return FALHA;
    }

    for (int i = 0; numero[i] != '\0'; i++)
    {
        if (!isdigit(numero[i]))
        {
            return FALHA;
        }
    }

    long numero_convertido = strtol(numero, NULL, 10);
    return (numero_convertido);
}

int verifica_data(char *data)
{

    if (data[0] == '\0')
    {
        return FALHA;
    }

    for (int i = 0; data[i] != '\0'; i++)
    {
        if (!isdigit(data[i]) && (i != 2 && i != 5))
        {
            return FALHA;
        }
    }
    if (data[2] != ' ' || data[5] != ' ')
    {
        return FALHA;
    }

    int dia, mes, ano;
    sscanf(data, "%d %d %d", &dia, &mes, &ano);
    if (dia < 0 || dia > 31)
    {
        return FALHA;
    }
    if (mes < 0 || mes > 12)
    {
        return FALHA;
    }
    if (ano < 2024 || ano > 2030)
    {
        return FALHA;
    }

    return SUCESSO;
}

int verifica_matricula_valida(char *numero)
{
    if (numero[0] == '\0')
    {
        return FALHA;
    }

    for (int i = 0; numero[i] != '\0'; i++)
    {
        if (!isdigit(numero[i]))
        {
            return FALHA;
        }
    }
    long numero_convertido = strtol(numero, NULL, 10);

    if (numero_convertido < 10000000 || numero_convertido > 99999999)
    {
        return FALHA;
    }

    return SUCESSO;
}

float verifica_float(char *numero)
{
    int ponto_encontrado = 0;

    if (numero[0] == '\0')
    {
        return FALHA;
    }

    for (int i = 0; numero[i] != '\0'; i++)
    {
        if (isdigit(numero[i]))
        {
            continue;
        }
        if (numero[i] == '.')
        {
            if (ponto_encontrado)
            {
                return FALHA;
            }
            ponto_encontrado = 1;
            continue;
        }
        return FALHA;
    }

    char *endptr;
    float resultado = strtof(numero, &endptr);

    if (endptr == numero || resultado < 100 || resultado > 700)
    {
        return FALHA;
    }

    return resultado;
}

int verifica_caracter(char *nome)
{

    int i = 0;

    while (i < strlen(nome))
    {

        if (!isalpha(nome[i]) && !isspace(nome[i]))
        {

            printf("Caracter Invalido!\n");
            return FALHA;
        }
        i++;
    }
    return SUCESSO;
}

char *transforma_caracter_padrao(char *nome)
{

    nome[0] = toupper(nome[0]);

    int i = 1;
    while (nome[i] != '\0')
    {

        if (isspace(nome[i - 1]))
        {
            nome[i] = toupper(nome[i]);
        }

        else
        {
            nome[i] = tolower(nome[i]);
        }
        i++;
    }

    return nome;
}

void limpaBuffer(void){
    int a;
    while((a = getchar()) != '\n' && a != EOF);
}