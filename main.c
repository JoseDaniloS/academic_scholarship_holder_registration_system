#include <stdio.h>
#include <stdlib.h>
#include "./sistema/system.h"

void limpar_tela(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main(void){
    int opcao;
    Bolsa * bolsas;
    FILE * arquivo = Verificacao("./banco_de_dados/bolsas.txt", "rt");
    ler_bolsa_arquivo(&arquivo, &bolsas);
    fclose(arquivo);
    do{
        menu_de_opcoes();
        scanf("%d", &opcao);
        switch (opcao){
        case 1:
            printf("Adicionando Bolsa...\n");
            preenche_bolsa(&bolsas);
            Verificacao("./banco_de_dados/bolsas.txt", "w");
            insere_bolsa_arquivo(&arquivo, &bolsas);
            fclose(arquivo);
            limpar_tela();
            break;
        case 2:

            printf("Adicionando Bolsista...\n");
            preenche_bolsista(&bolsas);
            Verificacao("./banco_de_dados/bolsas.txt", "w");
            insere_bolsa_arquivo(&arquivo, &bolsas);
            fclose(arquivo);
            limpar_tela();
            break;
        case 3:

            printf("Excluindo Bolsista...\n");
            excluir_bolsista_por_nome(&bolsas);
            Verificacao("./banco_de_dados/bolsas.txt", "w");
            insere_bolsa_arquivo(&arquivo, &bolsas);
            fclose(arquivo);
            limpar_tela();
            break;
        case 4:

            printf("Excluindo bolsa...\n");
            Verificacao("./banco_de_dados/bolsas.txt", "w");
            insere_bolsa_arquivo(&arquivo, &bolsas);
            fclose(arquivo);
            limpar_tela();
            break;
        case 5:

            printf("Listando todos os bolsistas cadastrados...\n");
            auxiliar_listar_bolsistas(&bolsas);
            break;
        case 6:

            printf("Buscando Bolsista...\n");
            buscar_bolsista_por_nome(&bolsas);
            break;
        case 7:

            printf("Editando Dados do Bolsista...\n");
            //funçao para editar aqui
            Verificacao("./banco_de_dados/bolsas.txt", "w");
            insere_bolsa_arquivo(&arquivo, &bolsas);
            fclose(arquivo);
            break;
        case 8:

            printf("Consultando as Bolsas Disponiveis...\n");
            consultar_bolsas_disponiveis(bolsas);
            break;
        case 9:
            printf("Saindo...\n");
            exit(1);
            break;
        
        default:
        printf("Opcao Invalida!\n");
            break;
        }
    }while(opcao != 9);
    return 0;
}