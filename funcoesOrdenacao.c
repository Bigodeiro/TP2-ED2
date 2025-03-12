#include "funcoesOrdenacao.h"


// Função para ordenar o arquivo em ordem ascendente (para gerar o arquivo de entrada)

void ordenarArquivoAscendente(const char *arquivo_entrada, const char *arquivo_saida, int quantidade, Dados *dados)
{
    // Abre o arquivo de entrada
    FILE *entrada = fopen(arquivo_entrada, "r");
    if (entrada == NULL)
    {
        printf("Erro ao abrir O arquivo de entrada.\n");
        exit(1);
    }

    // Lê os registros do arquivo de entrada
    TipoRegistro *registros = (TipoRegistro *)malloc(quantidade * sizeof(TipoRegistro));
    if (registros == NULL)
    {
        printf("Erro de alocação de memória.\n");
        fclose(entrada);
        exit(1);
    }

    for (int i = 0; i < quantidade; i++)
    {
        if (!lerRegistro(entrada, &registros[i], &dados->acessos))
        {
            printf("Erro ao ler registro %d.\n", i + 1);
            free(registros);
            fclose(entrada);
            exit(1);
        }
    }

    fclose(entrada);

    // trocar pela nossa funcao do quicksort
    // Ordena os registros em ordem ascendente
    quicksortInterno(registros, 0, quantidade - 1, dados);

    // Escreve os registros ordenados no arquivo de saída
    FILE *saida = fopen(arquivo_saida, "w");
    if (!saida)
    {
        printf("Erro ao abrir arquivo de saída.\n");
        free(registros);
        exit(1);
    }

    for (int i = 0; i < quantidade; i++)
    {
        escreverRegistro(saida, &registros[i], &dados->acessos);
    }

    fclose(saida);
    free(registros);
}

// Função para ordenar o arquivo em ordem descendente (para gerar o arquivo de entrada)
void ordenarArquivoDescendente(const char *arquivo_entrada, const char *arquivo_saida, int quantidade, Dados *dados)
{
    FILE *entrada = fopen(arquivo_entrada, "r");
    if (entrada == NULL)
    {
        printf("Erro ao abrir o arquivo de entrada.\n");
        exit(1);
    }

    // Lê os registros do arquivo de entrada
    TipoRegistro *registros = (TipoRegistro *)malloc(quantidade * sizeof(TipoRegistro));
    if (registros == NULL)
    {
        printf("Erro de alocação de memória.\n");
        fclose(entrada);
        exit(1);
    }

    for (int i = 0; i < quantidade; i++)
    {
        if (!lerRegistro(entrada, &registros[i], &dados->acessos))
        {
            printf("Erro ao ler registro %d.\n", i + 1);
            free(registros);
            fclose(entrada);
            exit(1);
        }
    }

    fclose(entrada);

    // Ordena os registros em ordem descendente (invertendo a comparação)
    for (int i = 0; i < quantidade - 1; i++)
    {
        for (int j = i + 1; j < quantidade; j++)
        {
            dados->acessos.num_comparacoes++;

            if (registros[i].nota < registros[j].nota)
            {
                TipoRegistro temp = registros[i];
                registros[i] = registros[j];
                registros[j] = temp;
            }
        }
    }

    // Escreve os registros ordenados no arquivo de saída
    FILE *saida = fopen(arquivo_saida, "w");
    if (saida == NULL)
    {
        printf("Erro ao abrir arquivo de saída.\n");
        free(registros);
        exit(1);
    }

    for (int i = 0; i < quantidade; i++)
    {
        escreverRegistro(saida, &registros[i], &dados->acessos);
    }

    fclose(saida);
    free(registros);
}

// Função para clonar parte do arquivo (para gerar o arquivo de entrada)
void clonarArquivoParcial(const char *arquivo_entrada, const char *arquivo_saida, int quantidade, Dados *dados)
{
    FILE *entrada = fopen(arquivo_entrada, "r");
    if (entrada == NULL)
    {
        printf("Erro ao abrir arquivo de entrada.\n");
        exit(1);
    }

    FILE *saida = fopen(arquivo_saida, "w");
    if (saida == NULL)
    {
        printf("Erro ao abrir arquivo de saída.\n");
        fclose(entrada);
        exit(1);
    }

    TipoRegistro reg;
    for (int i = 0; i < quantidade; i++)
    {
        if (!lerRegistro(entrada, &reg, &dados->acessos))
        {
            break;
        }
        escreverRegistro(saida, &reg, &dados->acessos);
    }

    fclose(entrada);
    fclose(saida);
}

// Função para gerar o arquivo de entrada
void gerarArquivoEntrada(const char *arquivo_original, const char *arquivo_entrada,Dados *dados)
{
    // Primeiro, gera um arquivo temporário com a quantidade de registros desejada
    char arquivo_temp[100];
    sprintf(arquivo_temp, "temp_%d.txt", dados->quantidade);
    clonarArquivoParcial(arquivo_original, arquivo_temp, dados->quantidade, dados);

    // Depois, ordena conforme a situação
    switch (dados->situacao)
    {
    case 1: // Ascendente
        ordenarArquivoAscendente(arquivo_temp, arquivo_entrada, dados->quantidade, dados);
        break;
    case 2: // Descendente
        ordenarArquivoDescendente(arquivo_temp, arquivo_entrada, dados->quantidade, dados);
        break;
    case 3: // Aleatório (já está assim no original)
        rename(arquivo_temp, arquivo_entrada);
        return;
    default:
        exit(1);
    }

    remove(arquivo_temp);
}
