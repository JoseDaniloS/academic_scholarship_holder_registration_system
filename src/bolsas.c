#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../include/bolsas.h"

#define MAX_BOLSA 30

struct data
{
    int dia;
    int mes;
    int ano;
};

struct bolsa
{
    char nome_bolsa[MAX_BOLSA];
    float valor_mensal;
    Data inicio;
    Data termino;
    Bolsista *bolsistas;
    Bolsa *proxima_bolsa;
};

void insere_bolsa(Bolsa **bolsas)
{

    char nome_bolsa[MAX_BOLSA];
    float valor_mensal;
    char c_numero[10];
    int verificador = FALHA, verificador2 = FALHA;
    int verificador_data_inicio = FALHA, verificador_data_termino = FALHA;
    int verifica_data1, verifica_data2, verifica_data2_termino;
    char datas[10];
    Data inicio, termino;

    do
    {

        printf("Informe o nome da bolsa:\n");
        scanf(" %[^\n]", nome_bolsa);
        fflush(stdin);
        if (strlen(nome_bolsa) >= MAX_BOLSA)
        {
            printf("Nome muito grande!Digite Novamente.\n");
            verificador = FALHA;
        }
        else
        {
            verificador = verifica_caracter(nome_bolsa);
            transforma_caracter_padrao(nome_bolsa);
            verificador2 = verifica_bolsa_existente(*bolsas, nome_bolsa);
        }

    } while (verificador == FALHA || verificador2 == FALHA);

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

    do
    {
        
        printf("Informe a data de inicio\nFormato: DD MM AAAA\n");
        scanf(" %[^\n]", datas);
        verifica_data1 = verifica_data(datas);

        if (verifica_data1 == FALHA)
        {
            printf("Data invalida!\n");
            continue;
        }
        sscanf(datas, "%d %d %d", &inicio.dia, &inicio.mes, &inicio.ano);

        do
        {
            printf("Informe a data de termino\nFormato: DD MM AAAA\n");
            scanf(" %[^\n]", datas);
            verifica_data2 = verifica_data(datas);
            if (verifica_data2 == FALHA)
            {
                printf("Data invalida!\n");
                continue;
            }
            sscanf(datas, "%d %d %d", &termino.dia, &termino.mes, &termino.ano);
            verifica_data2_termino = verifica_data_termino(inicio, termino);
            if (verifica_data2_termino == FALHA)
            {
                printf("Data final precisa ser maior que data inicial!\n");
                continue;
            }

        } while (verifica_data2 == FALHA || verifica_data2_termino == FALHA);

    } while (verifica_data1 == FALHA);

    nova_bolsa->inicio = inicio;
    nova_bolsa->termino = termino;
    insere_bolsa_ordenada(bolsas, nova_bolsa);

    printf("%s Adicionada com sucesso!\n", nome_bolsa);
}

int verifica_data_termino(Data inicio, Data termino)
{
    if (inicio.ano > termino.ano)
    {
        return FALHA;
    }
    else if (inicio.ano == termino.ano)
    {
        if (inicio.mes > termino.mes)
        {
            return FALHA;
        }
    }
    else if (inicio.mes == termino.mes)
    {
        if (inicio.dia > termino.dia)
        {
            return FALHA;
        }
    }

    return SUCESSO;
}

void insere_bolsa_ordenada(Bolsa **bolsas, Bolsa *nova_bolsa)
{
    Bolsa *count = *bolsas;
    Bolsa *ant = NULL;

    // Se a lista estiver vazia ou se a nova bolsa deve ser inserida no início
    if (count == NULL || strcmp(nova_bolsa->nome_bolsa, count->nome_bolsa) < 0)
    {
        nova_bolsa->proxima_bolsa = count;
        *bolsas = nova_bolsa;
        return;
    }
    else
    {
        // Percorre a lista até encontrar a posição correta para inserir
        while (count != NULL && strcmp(nova_bolsa->nome_bolsa, count->nome_bolsa) > 0)
        {
            ant = count;
            count = count->proxima_bolsa;
        }

        // Insere a nova bolsa na posição correta
        nova_bolsa->proxima_bolsa = count;
        ant->proxima_bolsa = nova_bolsa;
    }
}

// função para ler as bolsas em ordem correta
void ler_bolsa_no_final(Bolsa **bolsas, Bolsa *nova_bolsa)
{
    Bolsa *count = *bolsas;

    // se lista estiver vazia, a nova bolsa sera a primeira
    if (count == NULL)
    {
        *bolsas = nova_bolsa;
        nova_bolsa->proxima_bolsa = NULL;
        return;
    }
    // percorre a lista ate o final
    while (count->proxima_bolsa != NULL)
    {
        count = count->proxima_bolsa;
    }

    // insere a nova bolsa no final da lista
    if (count->proxima_bolsa == NULL)
    {
        count->proxima_bolsa = nova_bolsa;
        nova_bolsa->proxima_bolsa = NULL;
        return;
    }
}

// função para excluir uma bolsa
void excluir_bolsas(Bolsa **bolsas)
{

    if (bolsa_vazia(*bolsas) == FALHA)
    {
        return;
    }

    int verificador = FALHA;
    char nome_bolsa[MAX_BOLSA];
    Bolsa *count = *bolsas;
    Bolsa *ant = NULL;

    do
    {
        printf("Informe o nome da Bolsa:\n");
        scanf(" %[^\n]", nome_bolsa);
        fflush(stdin);
        if (strlen(nome_bolsa) >= MAX_BOLSA)
        {
            printf("Nome muito grande!Digite Novamente.\n");
            verificador = FALHA;
        }
        else
        {
            verificador = verifica_caracter(nome_bolsa);
        }

    } while (verificador == FALHA);

    transforma_caracter_padrao(nome_bolsa);

    while (count != NULL)
    {

        // se encontrar a bolsa
        if (strcmp(count->nome_bolsa, nome_bolsa) == 0)
        {

            // se a bolsa a ser removida seja a primeira
            if (ant == NULL)
            {
                *bolsas = count->proxima_bolsa;
            }
            // ser a bolsa a ser removida seja apos a primeira
            else
            {
                ant->proxima_bolsa = count->proxima_bolsa;
            }
            printf("Bolsa %s removida com sucesso!\n", nome_bolsa);
            auxiliar_excluir_bolsas(&count->bolsistas);
            free(count);
            return;
        }
        // avança a proxima bolsa
        ant = count;
        count = count->proxima_bolsa;
    }
    printf("Bolsa %s nao encontrada!\n", nome_bolsa);
    return;
}

// função para excluir um bolsista de uma bolsa
void excluir_bolsista_por_nome(Bolsa **bolsas)
{

    // verifica se a bolsa esta vazia
    if (bolsa_vazia(*bolsas) == FALHA)
    {
        return;
    }
    char nome_bolsista[40];
    int verificador = FALHA;
    do
    {
        printf("Informe o nome do bolsista:\n");
        scanf(" %[^\n]", nome_bolsista);
        fflush(stdin);
        if (strlen(nome_bolsista) >= MAX)
        {
            printf("Nome muito grande!Digite novamente.\n");
            verificador = FALHA;
        }
        else
        {
            verificador = verifica_caracter(nome_bolsista);
        }
    } while (verificador == FALHA);

    transforma_caracter_padrao(nome_bolsista);

    Bolsa *count = *bolsas;
    int bolsista_excluido = FALHA;
    // percorrer todas as bolsas ate encontrar o bolsista
    while (count != NULL)
    {

        if (auxiliar_excluir_bolsista_por_nome(&count->bolsistas, nome_bolsista))
        {
            bolsista_excluido = SUCESSO;
        }
        count = count->proxima_bolsa;
    }

    if (bolsista_excluido == FALHA)
    {
        printf("Bolsista '%s' nao encontrado!\n", nome_bolsista);
    }
}
int verifica_bolsa_existente(Bolsa *bolsas, char *nome_bolsa)
{

    Bolsa *count = bolsas;

    while (count != NULL)
    {
        // verifica se a bolsa ja esta cadastrada
        if (strcmp(count->nome_bolsa, nome_bolsa) == 0)
        {

            printf("Bolsa %s ja cadastrada!\n", nome_bolsa);
            return FALHA; // bolsa ja existe
        }

        count = count->proxima_bolsa;
    }

    return SUCESSO; // bolsa nao encontrada
}
// função para buscar um bolsista
void menu_busca_bolsista(Bolsa **bolsas)
{

    if (bolsa_vazia(*bolsas) == FALHA)
    {
        return;
    }

    char c_numero[2];
    int opcao;

    do
    {
        printf("1 - Buscar Bolsista por Nome:\n");
        printf("2 - Buscar Bolsista por Matricula:\n");
        printf("3 - Sair..\n");
        scanf("%s", c_numero);
        opcao = verifica_inteiro(c_numero);

        switch (opcao)
        {
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
    } while (opcao != 3);

    return;
}

// função para buscar um bolsista por nome
void buscar_bolsista_por_nome(Bolsa **bolsas)
{
    // caso nao tenha nenhuma bolsa cadastrada
    if (bolsa_vazia(*bolsas) == FALHA)
    {
        return;
    }

    char nome_bolsista[MAX];
    int verificador = FALHA;
    do
    {
        printf("Informe o nome do Bolsista:\n");
        scanf(" %[^\n]", nome_bolsista);
        fflush(stdin);
        if (strlen(nome_bolsista) >= MAX)
        {
            printf("Nome muito grande!Digite Novamente.\n");
            verificador = FALHA;
        }
        else
        {
            verificador = verifica_caracter(nome_bolsista);
        }
    } while (verificador == FALHA);

    transforma_caracter_padrao(nome_bolsista);

    Bolsa *count = *bolsas;
    Bolsista *bolsista_encontrado = NULL;

    while (count != NULL)
    {
        bolsista_encontrado = auxiliar_buscar_bolsista_por_nome(count->bolsistas, nome_bolsista);
        count = count->proxima_bolsa;
    }
}

void buscar_bolsista_por_matricula(Bolsa **bolsas)
{
    Bolsa *count = *bolsas;

    if (bolsa_vazia(*bolsas) == FALHA)
    {
        printf("Nao há bolsas cadastradas.");
        return;
    }

    long int matricula;
    Bolsista *bolsista_encontrado = NULL;
    printf("Informe a matricula do bolsista: ");
    scanf("%ld", &matricula);

    while (count != NULL)
    {
        bolsista_encontrado = auxiliar_buscar_bolsista_por_matricula(count->bolsistas, matricula);
        count = count->proxima_bolsa;
    }

    return;
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

// função para listar todos os bolsistas cadastrados em todas as bolsas
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
    char nome_bolsa[MAX_BOLSA];
    Bolsa *bolsa_encontrada = NULL;
    int verificador = FALHA;

    do
    {
        printf("Informe a Bolsa que o Aluno vai ser Vinculado:\n");
        scanf(" %[^\n]", nome_bolsa);
        fflush(stdin); // limpa buffer
        if (strlen(nome_bolsa) >= MAX_BOLSA)
        {
            printf("Nome muito grande! Digite Novamente.\n");
            verificador = FALHA;
        }
        else
        {
            verificador = verifica_caracter(nome_bolsa);
        }
    } while (verificador == FALHA);

    transforma_caracter_padrao(nome_bolsa);

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
    char linha[MAX_BOLSA];
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
            nova_bolsa->proxima_bolsa = NULL;
            nova_bolsa->bolsistas = NULL;

            ler_bolsa_no_final(bolsas, nova_bolsa); // adicionar as bolsas em ordem correta
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
    if (bolsa_vazia(*bolsas) == FALHA)
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

// função para verificar se a lista de bolsas está vazia
int bolsa_vazia(Bolsa *bolsas)
{
    if (bolsas == NULL)
    {
        printf("Nao ha bolsas cadastradas!\n");
        return FALHA;
    }
    return SUCESSO;
}

void edita_dados_bolsista(Bolsa **bolsas)
{
    if (bolsa_vazia(*bolsas) == FALHA)
    {
        return;
    }
    char c_numero[2], nome_bolsista[40];
    int opcao, verificador = FALHA;
    Bolsa *count = *bolsas;
    Bolsista *bolsista_encontrado = NULL;
    long int matricula;

    do
    {
        printf("1 - Buscar Bolsista por Nome:\n");
        printf("2 - Buscar Bolsista por Matricula:\n");
        printf("3 - Sair..\n");
        scanf("%s", c_numero);
        opcao = verifica_inteiro(c_numero);

        switch (opcao)
        {
        case 1:

            // Solicita o nome do bolsista e valida
            do
            {
                printf("Informe o nome do Bolsista:\n");
                scanf(" %[^\n]", nome_bolsista);
                fflush(stdin);

                if (strlen(nome_bolsista) >= MAX)
                {
                    printf("Nome muito grande! Digite Novamente.\n");
                    verificador = FALHA;
                }
                else
                {
                    verificador = verifica_caracter(nome_bolsista);
                }
            } while (verificador == FALHA);

            transforma_caracter_padrao(nome_bolsista);

            // Busca pelo bolsista em todas as bolsas
            while (count != NULL)
            {
                bolsista_encontrado = auxiliar_buscar_bolsista_por_nome(count->bolsistas, nome_bolsista);

                // Se o bolsista for encontrado, interrompe a busca
                if (bolsista_encontrado != NULL)
                {
                    break;
                }

                count = count->proxima_bolsa;
            }
            // Se o bolsista for encontrado, chama a função de edição
            if (bolsista_encontrado != NULL)
            {
                auxiliar_editar_bolsista(bolsista_encontrado, count->bolsistas);
            }
            else
            {
                printf("Bolsista %s não encontrado!\n", nome_bolsista);
            }
            break;
        case 2:

            printf("Informe a matricula do bolsista:\n");
            scanf("%ld", &matricula);

            // Busca pelo bolsista em todas as bolsas
            while (count != NULL)
            {
                bolsista_encontrado = auxiliar_buscar_bolsista_por_matricula(count->bolsistas, matricula);

                // Se o bolsista for encontrado, interrompe a busca
                if (bolsista_encontrado != NULL)
                {
                    break;
                }

                count = count->proxima_bolsa;
            }
            // Se o bolsista for encontrado, chama a função de edição
            if (bolsista_encontrado != NULL)
            {
                auxiliar_editar_bolsista(bolsista_encontrado, count->bolsistas);
            }
            else
            {
                printf("Bolsista %s não encontrado!\n", nome_bolsista);
            }
            break;
        case 3:
            printf("Voltando ao menu anterior...\n");
            break;
        default:
            printf("Opcao Invalida! Por favor, escolha entre 1 e 3.\n");
            break;
        }
    } while (opcao != 3);
}
