#include "../include/sistema.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

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
    printf("[ 8 ] - Consultar Bolsas Disponiveis.\n");
    printf("[ 9 ] - Sair.\n\n");
    printf("Informe a Opcao:\n");
}

//Função para abrir/criar arquivo e retornar este arquivo
FILE * Verificacao(char * nome, char * modo){
    FILE * arquivo = fopen(nome, modo);
    if(arquivo == NULL){
        printf("Can't open the file\n");
        exit(1);
    }
    else{
        printf("File open!\n");
    }

    return arquivo;
}

int verifica_cpf_valido(char * cpf){

    //verifica se o cpf está no formato 000.000.000-00
    if (strlen(cpf) != 14 || 
        !isdigit(cpf[0]) || !isdigit(cpf[1]) || !isdigit(cpf[2]) || cpf[3] != '.' ||
        !isdigit(cpf[4]) || !isdigit(cpf[5]) || !isdigit(cpf[6]) || cpf[7] != '.' ||
        !isdigit(cpf[8]) || !isdigit(cpf[9]) || !isdigit(cpf[10]) || cpf[11] != '-' ||
        !isdigit(cpf[12]) || !isdigit(cpf[13])) {
        
        printf("CPF deve estar no formato 000.000.000-00.\nDigite Novamente.\n");
        return FALHA;
    }

    char cpf_sem_formato[TAMANHO_CPF + 1]; // Array para CPF sem formatação
    int j = 0;

    // Remove formatações
    for(int i = 0; cpf[i] != '\0'; i++){
        if(isdigit(cpf[i])){
            cpf_sem_formato[j++] = cpf[i];
        }
    }
    cpf_sem_formato[j] = '\0'; //termina a string

    // Verifica o tamanho e se contém apenas números
    if(strlen(cpf_sem_formato) != TAMANHO_CPF){
        printf("CPF deve conter exatamente 11 digitos.\nDigite Novamente.\n");
        return FALHA;
    }

    return SUCESSO;
}

int verifica_inteiro(char * numero){
    
    //verifica se a string está vazia
    if(numero[0] == '\0'){
        return FALHA;
    }
    
    //verifica cada caractere da string se é um digito
    for(int i = 0; numero[i] != '\0'; i++){
        if(!isdigit(numero[i])){
            return FALHA;
        }
    }
    //converte o numero para inteiro entre 0 e 10
    long numero_convertido = strtol(numero, NULL, 10);
    return(numero_convertido);
}

float verifica_float(char * numero) {
    int ponto_encontrado = 0;

    // Verifica se a string está vazia
    if (numero[0] == '\0') {
        return FALHA; // Retorna falha se a string estiver vazia
    }

    // Verifica cada caractere da string
    for (int i = 0; numero[i] != '\0'; i++) {
        if (isdigit(numero[i])) {
            continue; // Se é um dígito, continua
        }
        if (numero[i] == '.') {
            if (ponto_encontrado) {
                return FALHA; // Retorna falha se já encontramos um ponto
            }
            ponto_encontrado = 1; // Marca que encontramos um ponto
            continue;
        }
        return FALHA; // Retorna falha se encontrar um caractere inválido
    }

    // Conversão da string para float
    char *endptr; // Ponteiro para indicar onde a conversão parou
    float resultado = strtof(numero, &endptr);
    
    // Verifica se a conversão foi bem-sucedida
    if (endptr == numero || resultado < 100 || resultado > 700) {
        return FALHA; // Nenhum dígito foi convertido ou fora dos limites
    }

    return resultado; // Retorna o valor convertido
}
//função para verificar um caracter é do tipo alfabeto ou se é um espaço
int verifica_caracter(char * nome){
    
    int i = 0;

    while(i < strlen(nome)){

        if(!isalpha(nome[i]) && !isspace(nome[i])){//se nao for um caracter nem um espaço

            printf("Caracter Invalido!\n");
            return FALHA;
        }
        i++;
    }
    return SUCESSO;
}

//função que corrige o nome para o padrao correto
char * transforma_caracter_padrao(char * nome){

    nome[0] = toupper(nome[0]);//transfomra primeiro caracter em maiusculo

    int i = 1;
    while(nome[i] != '\0'){

        if(isspace(nome[i-1])){
            nome[i] = toupper(nome[i]);//transforma todos os caracteres após o espaço em maiusculo
        }

        else{
            nome[i] = tolower(nome[i]);//transforma todos os caracteres apos a primeira letra maiuscula em minusculo
        }
        i++;
    }

    return nome;
}