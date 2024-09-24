#include "../include/sistema.h"
#include <stdlib.h>
#include <stdio.h>

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

//função para verificar se o cpf é valido
int verifica_cpf_valido(char * cpf){

    if(strlen(cpf) != TAMANHO_CPF){
        printf("CPF deve conter exatamente 11 digitos.\nDigite Novamente.\n");
        return FALHA;
    }
    
    for(int i = 0; i < TAMANHO_CPF; i++){
        if(!isdigit(cpf[i])){
            printf("CPF deve conter apenas numeros.\nDigite Novamente.\n");
            return FALHA;
        }
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