#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "bolsas.h"

#define SUCESSO 1
#define FALHA 0

struct data{
    int dia;
    int mes;
    int ano;
};

struct bolsa{
    char nome_bolsa[100];
    float valor_mensal;
    Data inicio;
    Data termino;
    Bolsista * bolsistas;
    Bolsa * proxima_bolsa;
};

//função para adicionar uma nova bolsa na lista
Bolsa * adiciona_bolsa(char * nome_bolsa, float valor_mensal, Bolsa ** bolsas){

    //aloca a memoria de uma nova bolsa
    Bolsa * nova_bolsa = (Bolsa*)malloc(sizeof(Bolsa));
    if(nova_bolsa ==  NULL){
        printf("Memoria Insuficiente!\n");
        exit(1);
    }
    
    //adiciona as informaçoes na bolsa
    strcpy(nova_bolsa->nome_bolsa, nome_bolsa);
    nova_bolsa->valor_mensal = valor_mensal;
    nova_bolsa->bolsistas = NULL;
    nova_bolsa->proxima_bolsa = NULL;

    // Adiciona datas de início e término da bolsa
    adiciona_data(nova_bolsa);

    //a nova bolsa aponta para a lista existente de bolsas
    nova_bolsa->proxima_bolsa = *bolsas;
    printf("%s Adicionada com sucesso!\n", nome_bolsa);
    //retorna a nova cabeça da lista
    return nova_bolsa;
}


void preenche_bolsa(Bolsa ** bolsas){

    char nome_bolsa[100];
    float valor_mensal;
    printf("Informe o nome da bolsa:\n");
    scanf(" %[^\n]", nome_bolsa);
    printf("Informe o valor mensal:\n");
    scanf("%f", & valor_mensal);

    *bolsas = adiciona_bolsa(nome_bolsa,valor_mensal, bolsas);

   
}

//função para excluir um bolsista de uma bolsa
void excluir_bolsista_por_nome(Bolsa ** bolsas){

    if(*bolsas == NULL){
        printf("Nenhuma Bolsa Cadastrada!\n");
        return;
    }
    char nome_bolsista[100];
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

//função para buscar um bolsista
void menu_busca_bolsista(Bolsa ** bolsas){
    int opcao = 0;
    do{
        printf("1 - Buscar Bolsista por Nome:\n");
        printf("2 - Buscar Bolsista por Matricula:\n");
        printf("3 - Sair..\n");
        scanf("%d", &opcao);
        switch (opcao){
        case 1:
            buscar_bolsista_por_nome(bolsas);
            break;
        case 2:
            //função para buscar bolsista por matricula
            break;
        default:
            printf("Opcao Invalida!");
            break;
        }
    }while(opcao != 3);
    return;
}

//função para buscar um bolsista por nome
void buscar_bolsista_por_nome(Bolsa ** bolsas){
    char nome_bolsista[100];

    //caso nao tenha nenhuma bolsa cadastrada
    if(*bolsas == NULL){
        printf("Nenhuma Bolsa Cadastrada!\n");
        return;
    }

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

//funçao para adicionar datas de incio e termino da bolsa
void adiciona_data(Bolsa * bolsa){
    printf("Informe a data de inicio\nFormato: DD MM AAAA\n");
    scanf("%d %d %d", &bolsa->inicio.dia, &bolsa->inicio.mes, &bolsa->inicio.ano);

    printf("Informe a data de termino\nFormato: DD MM AAAA\n");
    scanf("%d %d %d", &bolsa->termino.dia, &bolsa->termino.mes, &bolsa->termino.ano);
}

Bolsa * busca_bolsa(char * nome_bolsa, Bolsa * bolsas){
    Bolsa * count = bolsas;

    //caso não exista nenhuma bolsa na lista
    if(bolsas == NULL){
        printf("Nao existem bolsas cadastradas!\n");
        return NULL;
    }

    //percorre as bolsas ate encontrar a bolsa pesquisada
    while(count != NULL && strcmp(count->nome_bolsa, nome_bolsa) != 0){
        count = count->proxima_bolsa;
    }

    //caso não exista a bolsa que esta procurando retorna NULL
    if(count == NULL){
        printf("Bolsa nao cadastrada!\n");
        return NULL;
    }
    //caso a bolsa seja encontrada, retorna o nó com as informações da bolsa
    else{
        printf("Bolsa %s encontrada!\n", count->nome_bolsa);
        return count;
    }
}

//funçao para consultar as bolsas disponiveis
void consultar_bolsas_disponiveis(Bolsa * bolsas){

    //caso não exista bolsas cadastradas
    if(bolsas == NULL){
        printf("Nao ha bolsas cadastradas!\n");
        return;
    }
    Bolsa * count = bolsas;
    
    //printa na tela as informações das bolsas
    while(count != NULL){
        printf("Bolsa: %s\n", count->nome_bolsa);
        printf("Valor Mensal: %.1f\n", count->valor_mensal);
        printf("Data de inicio: %02d/%02d/%04d\n", count->inicio.dia, count->inicio.mes, count->inicio.ano);
        printf("Data de Termino:%02d/%02d/%04d\n", count->termino.dia, count->termino.mes, count->termino.ano);
        printf("Quantidade de Bolsistas Cadastrados: %d\n", quantitativo_bolsistas(count->bolsistas));
        printf("\n\n");
        count = count->proxima_bolsa;
    }

}

void auxiliar_listar_bolsistas(Bolsa ** bolsas){
    Bolsa * count = *bolsas;
    int contador_de_bolsas = 1;
    while(count != NULL){
        printf("\n\n%d- Bolsa:\n", contador_de_bolsas);
        printf("Tipo: %s\n", count->nome_bolsa);
        printf("Valor Mensal: %.1f\n", count->valor_mensal);
        printf("Data de Inicio: %02d/%02d/%04d\n", count->inicio.dia, count->inicio.mes, count->inicio.ano);
        printf("Data de Termino: %02d/%02d/%04d\n\n", count->termino.dia, count->termino.mes, count->termino.ano);

        //listar bolsistas da bolsa atual
        listar_bolsistas(count->bolsistas);

        //avancar para proxima bolsa
        count = count->proxima_bolsa;
        contador_de_bolsas++;
    }

    if(contador_de_bolsas == 1){
        printf("Nenhuma bolsa cadastrada!\n");
    }
}

//função para preencher dados de um bolsista
void preenche_bolsista(Bolsa ** bolsas){
    char nome_bolsa[100];
    Bolsa * bolsa_encontrada = NULL;

    printf("Informe a Bolsa que o Aluno vai ser Vinculado:\n");
    scanf(" %[^\n]", nome_bolsa);

    //busca a bolsa que o bolsista vai ser adicionado
    bolsa_encontrada = busca_bolsa(nome_bolsa, *bolsas);

    if(bolsa_encontrada != NULL){
        adiciona_bolsista(&bolsa_encontrada->bolsistas, nome_bolsa);
    }
    else{
        printf("Bolsa '%s' nao encontrada!\n", nome_bolsa);
    }
}

//funçao para escanear todas as bolsas armazenadas no banco de dado
void ler_bolsa_arquivo(FILE ** banco_de_dados, Bolsa ** bolsas){
    char linha[100];
    Bolsa * nova_bolsa = NULL;
    
    while(fgets(linha,sizeof(linha),*banco_de_dados) != NULL){
        //verifica se a linha escaneada contem a palavra Bolsa
        if(strstr(linha, "BOLSA:")){

            nova_bolsa = (Bolsa*)malloc(sizeof(Bolsa));
            if(nova_bolsa == NULL){
                printf("Memoria Insuficiente!\n");
                exit(1);
            }
            nova_bolsa->proxima_bolsa = *bolsas;
            *bolsas = nova_bolsa;
            nova_bolsa->bolsistas = NULL;
        }

        //escaneia todas as informações das bolsas
        else if (nova_bolsa != NULL){
            
            if(strstr(linha, "Tipo:")){
                sscanf(linha,"Tipo: %[^\n]", nova_bolsa->nome_bolsa);
            }
            else if(strstr(linha, "Valor Mensal:")){
                sscanf(linha, "Valor Mensal: %f", &nova_bolsa->valor_mensal);
            }
            else if(strstr(linha, "Data de Inicio:")){
                sscanf(linha, "Data de Inicio: %d/%d/%d", &nova_bolsa->inicio.dia, &nova_bolsa->inicio.mes, &nova_bolsa->inicio.ano);
            }
            else if(strstr(linha, "Data de Termino:")){
                sscanf(linha, "Data de Termino: %d/%d/%d", &nova_bolsa->termino.dia, &nova_bolsa->termino.mes, &nova_bolsa->termino.ano);
            }

            //ler os dados dos bolsistas
            else if(strstr(linha, "BOLSISTAS:")){
                nova_bolsa->bolsistas = ler_bolsista_arquivo(banco_de_dados, nova_bolsa->bolsistas);
            }
        }
    }
}

//funçao para armazenar uma bolsa e seus respectivos campos
void insere_bolsa_arquivo(FILE ** banco_de_dados, Bolsa ** bolsas){
    Bolsa * count = *bolsas;
    if(*bolsas == NULL){
        return;
    }
    //percorre todas as bolsas armazenando suas informações no banco de dados
    while(count != NULL){
        fprintf(*banco_de_dados, "===============================\n");
        fprintf(*banco_de_dados, "BOLSA:\nTipo: %s\n", count->nome_bolsa);
        fprintf(*banco_de_dados, "Valor Mensal: %.1f\n", count->valor_mensal);
        fprintf(*banco_de_dados, "Data de Inicio: %02d/%02d/%04d\n", count->inicio.dia, count->inicio.mes, count->inicio.ano);
        fprintf(*banco_de_dados, "Data de Termino: %02d/%02d/%04d\n\n", count->termino.dia, count->termino.mes, count->termino.ano);

        //insere os bolsistas associados à bolsa no arquivo
        insere_bolsista_arquivo(banco_de_dados,count->bolsistas);

        fprintf(*banco_de_dados, "===============================\n\n");
        count = count->proxima_bolsa;
    }    
}