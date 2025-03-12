#include "funcoesOrdenacao.h"

// Função para gerar o arquivo de entrada
void gerarArquivoEntrada(Dados *dados)
{
    // Criação do arquivo de entrada
    FILE *arquivoEntrada;

    char ordenacao[20];

    // Ordena conforme a situação
    switch (dados->situacao)
    {
    case 1: // Ascendente
        arquivoEntrada = fopen("provaoC.bin", "rb");
        strcpy(ordenacao, "crescente");
        break;
    case 2: // Descendente
        arquivoEntrada = fopen("provaoD.bin", "rb");
        strcpy(ordenacao, "decrescente");
        break;
    case 3: // Aleatório
        arquivoEntrada = fopen("provaoA.bin", "rb");
        strcpy(ordenacao, "aleatorio");
        return;
    default:
        exit(1);
    }

    char metodo[20];

    switch (dados->metodo)
    {
    case 1:
        strcpy(metodo, "2f_fitas");
        break;
    case 2:
        strcpy(metodo, "f+1_fitas");
        break;
    case 3:
        strcpy(metodo, "Quicksort");
        break;

    default:
        break;
    }

    // Lendo os n primeiros dados do arquivo de origem
    TipoRegistro *registros = malloc(dados->quantidade * sizeof(TipoRegistro));
    fread(registros, sizeof(TipoRegistro), dados->quantidade, arquivoEntrada);
    dados->acessos.num_leituras += 1;

    // Gerando o nome do arquivo de destino
    char arquivoDestino[50];
    sprintf(arquivoDestino, "%s-%s-%d.bin", metodo, ordenacao, dados->quantidade);

    printf("Arquivo de destino: %s\n", arquivoDestino);
    strcpy(dados->nomeArquivo, arquivoDestino);

    // Escrevendo os n primeiros dados no arquivo de destino
    FILE *novoArquivo = fopen(arquivoDestino, "wb+");
    fwrite(registros, sizeof(TipoRegistro), dados->quantidade, novoArquivo);
    dados->acessos.num_escritas += 1;

    fclose(arquivoEntrada);
    fclose(novoArquivo);
    free(registros);
}

void transformarArquivoBinarioParaTxt_ImprimirDados(Dados *dados)
{
    FILE *arquivoDeOrigem = fopen(dados->nomeArquivo, "rb");

    // Criando e abrindo o arquivo de saida
    char nomeArquivoDeDestino[100];
    sprintf(nomeArquivoDeDestino, "%s.txt", dados->nomeArquivo);

    FILE *arquivoDeDestino = fopen(nomeArquivoDeDestino, "w");

    // Lendo os dados do binario e escrevendo no txt

    TipoRegistro buffer[20];
    size_t itensLidos;

    if (!dados->imprimir)
    {
        while ((itensLidos = fread(buffer, sizeof(TipoRegistro), 20, arquivoDeOrigem)) > 0)
        {
            dados->acessos.num_LeituraBinTxt += 1;

            for (int i = 0; i < itensLidos; i++)
            {
                fprintf(arquivoDeDestino, "%-8ld %-5.2f %-2s %-50s %-30s\n", buffer[i].inscricao, buffer[i].nota, buffer[i].estado, buffer[i].cidade, buffer[i].curso);

                dados->acessos.num_EscritaBinTxt += 1;
            }
        }
    }
    else
    {
        printf("\n");
        while ((itensLidos = fread(buffer, sizeof(TipoRegistro), 20, arquivoDeOrigem)) > 0)
        {
            dados->acessos.num_LeituraBinTxt += 1;

            for (int i = 0; i < itensLidos; i++)
            {
                printf("%-8ld %-5.2f %-2s %-50s %-30s\n", buffer[i].inscricao, buffer[i].nota, buffer[i].estado, buffer[i].cidade, buffer[i].curso);
                fprintf(arquivoDeDestino, "%-8ld %-5.2f %-2s %-50s %-30s\n", buffer[i].inscricao, buffer[i].nota, buffer[i].estado, buffer[i].cidade, buffer[i].curso);

                dados->acessos.num_EscritaBinTxt += 1;
            }
        }
        printf("\n");
    }

    fclose(arquivoDeDestino);
    fclose(arquivoDeOrigem);
}

void exibirResultados(Dados *dados)
{
    printf("Quantidade de leitura:                                    %7d\n", dados->acessos.num_leituras);

    if (dados->metodo != 3)
        printf("Quantidade de leitura na geração de blocos:               %7d\n", dados->acessos.num_LeituraGeracaoBlocos);

    printf("Quantidade de leitura na transformação de .bin para .txt: %7d\n", dados->acessos.num_LeituraBinTxt);

    int qtdLeituraTotal = dados->acessos.num_leituras + dados->acessos.num_LeituraGeracaoBlocos + dados->acessos.num_LeituraBinTxt;

    printf("Quantidade de leituras totais:                            %7d\n\n", qtdLeituraTotal);

    printf("Quantidade de escrita:                                    %7d\n", dados->acessos.num_escritas);

    if (dados->metodo != 3)
        printf("Quantidade de escrita na geração de blocos:               %7d\n", dados->acessos.num_EscritaGeracaoBlocos);

    printf("Quantidade de escrita na transformação de .bin para .txt: %7d\n", dados->acessos.num_EscritaBinTxt);
    
    int qtdEscritaTotal = dados->acessos.num_escritas + dados->acessos.num_EscritaGeracaoBlocos + dados->acessos.num_EscritaBinTxt;

    printf("Quantidade de escritas totais:                            %7d\n\n", qtdEscritaTotal);

    printf("Quantidade de comparações entre notas: %d\n", dados->acessos.comparacoesNotas);

    double tempoExecucao = ((double)(dados->acessos.tempoFim - dados->acessos.tempoInicio)) / CLOCKS_PER_SEC;

    printf("Tempo de execução: %lfs.\n", tempoExecucao);
}
