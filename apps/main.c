#include <stdio.h>
#include <stdlib.h>
#include "../include/bolsas.h"

void limpar_tela()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main(void)
{
    int opcao;
    Bolsa *bolsas;
    char c_numero[2];
    FILE *arquivo = Verificacao("../banco_de_dados/bolsas.txt", "rt");
    ler_bolsa_arquivo(&arquivo, &bolsas);
    fclose(arquivo);

    do
    {   
        menu_de_opcoes();
        scanf("%s", c_numero);
        opcao = verifica_inteiro(c_numero);
        switch (opcao)
        {
        case 1:
            printf("Adicionando Bolsa...\n");
            insere_bolsa(&bolsas);
            Verificacao("../banco_de_dados/bolsas.txt", "w");
            insere_bolsa_arquivo(&arquivo, &bolsas);
            fclose(arquivo);
            limpar_tela();
            break;
        case 2:
        
            printf("Adicionando Bolsista...\n");
            adiciona_bolsista_na_bolsa(&bolsas);
            Verificacao("../banco_de_dados/bolsas.txt", "w");
            insere_bolsa_arquivo(&arquivo, &bolsas);
            fclose(arquivo);
            limpar_tela();
            break;
        case 3:

            printf("Excluindo Bolsista...\n");
            excluir_bolsista_por_nome(&bolsas);
            Verificacao("../banco_de_dados/bolsas.txt", "w");
            insere_bolsa_arquivo(&arquivo, &bolsas);
            fclose(arquivo);
            limpar_tela();
            break;
        case 4:

            printf("Excluindo bolsa...\n");
            excluir_bolsas(&bolsas);
            Verificacao("../banco_de_dados/bolsas.txt", "w");
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
            menu_busca_bolsista(&bolsas);
            break;
        case 7:

            printf("Editando Dados do Bolsista...\n");
            edita_dados_bolsista(&bolsas);
            Verificacao("../banco_de_dados/bolsas.txt", "w");
            insere_bolsa_arquivo(&arquivo, &bolsas);
            fclose(arquivo);
            break;
        case 8:

            printf("Consultando as Bolsas Disponiveis...\n");
            consultar_bolsas_disponiveis(&bolsas);
            break;
        case 9:
            printf("Saindo...\n");
            exit(1);
            break;

        default:
            printf("Opcao Invalida!\n");
            break;
        }
    } while (opcao != 9);
    return 0;
}