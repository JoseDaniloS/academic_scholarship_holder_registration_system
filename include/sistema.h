#ifndef SISTEMA_H
#define SISTEMA_H

#include <stdio.h>
#define TAMANHO_CPF 11
#define FALHA 0
#define SUCESSO 1

/*Função que exibe o menu de opções ao usuário*/
void menu_de_opcoes();

/*Função que verifica se o arquivo foi aberto da forma correta*/
FILE * Verificacao(char * nome, char * modo);

/*Função que verifica se o CPF digitado é válido ou não dentro das condições:
    - se o CPF está no formato 000.000.000-00
    - se os numeros são inteiros
    - se contém 11 digitos 
Recebe como parâmetro uma string contendo o CPF digitado*/
int verifica_cpf_valido(char * cpf);

/*Função que verifica se a string digitada é um numero inteiro ou não
Recebe como parâmetro uma string contendo o numero digitado*/
int verifica_inteiro(char * numero);

/*Função que verifica se a string digitada está dentro das condições:
    - se é um numero inteiro E se há espaço em i[2] e i[5]
    - se está no formato DD/MM/AAAA
Recebe como parâmetro uma string contendo a data digitado*/
int verifica_data(char *data);

/*Função que verifica se a string digitada está dentro das condições:
    - se é um número inteiro 
    - se tem 8 digitos
Recebe como parâmetro uma string contendo a data digitado*/
int verifica_matricula_valida(char *numero);

/*Função que verifica se a string digitada é um float ou não
Recebe como parâmetro uma string contendo o numero digitado*/
float verifica_float(char * numero);

/*Funçõa que verifica se a string está dentro das condições:
    - se não é um caracter E se não é um espaço
Recebe como parâmetro uma string contendo o nome digitado*/
int verifica_caracter(char * nome);

/*Função que transforma os caracteres:
    - primeira letra do nome será maiúscula
    - primeira letra apos o espaço também será maiúscula
    - restante das letras serão minúsculas
Recebe como parâmetro uma string contendo o nome digitado*/
char * transforma_caracter_padrao(char * nome);

/*Função para limpar buffer de entrada*/
void limparBuffer();

#endif // SYSTEM_H
