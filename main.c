// Jordan Assunção Santos Mendonça || Nº Matrícula: 23.2.4070
// Filipe Hermenegildo da Cunha || Nº Matrícula: 23.2.4123

#include <stdbool.h>
#include "input/validacaoEntrada.h"
#include "estruturas.h"

#include "funcoesOrdenacao.h"
#include "funcoesRegistro.h"

#include "metodos/Quicksort/quickSort.h"

int main(int argc, char **argv)
{
    Dados dados = inicializaDados();

    // Validação dos parâmetros de entrada
    if (!validacaoEntrada(argc, argv, &dados))
        return 0;

    // Define os nomes dos arquivos
    const char *arquivo_original = "PROVAO.TXT";
    char arquivo_entrada[100];
    sprintf(arquivo_entrada, "entrada_%d_%d.txt", dados.quantidade, dados.situacao);
    strcpy(dados.nomeArquivo, arquivo_entrada);

    char arquivo_saida[100];
    sprintf(arquivo_saida, "saida_%d_%d_%d.txt", dados.metodo, dados.quantidade, dados.situacao);

    // gerarArquivoCopia(&dados);

    // Gera o arquivo de entrada de acordo com a situação
    gerarArquivoEntrada(arquivo_original, arquivo_entrada, &dados);

    // Reinicia os contadores
    dados.acessos.num_leituras = 0;
    dados.acessos.num_escritas = 0;
    dados.acessos.num_comparacoes = 0;

    // Inicializando a contagem de tempo do programa
    dados.acessos.tempoInicio = clock();

    switch (dados.metodo)
    {
    case 1:
        // Método de 2 fitas
        // doisF(*p_qtd, *p_sit, *p_print);
        break;
    case 2:
        // Método de f+1 fitas
        // fMaisUm(*p_qtd, *p_sit, *p_print);
        break;
    case 3:
        // Método de Quicksort Externo
        quickSort(&dados);
        printf("Quicksort Externo\n");
        break;
    default:
        break;
    }

    // // Transformando os dados do arquivo binario para o txt
    // binarioParaTXT_printarDados(&dados);

    

    // Finalizando a contagem de tempo do programa
    dados.acessos.tempoFim = clock();

    double tempo_execucao = (double)(dados.acessos.tempoFim - dados.acessos.tempoInicio) / CLOCKS_PER_SEC;

    if(dados.imprimir){
        // imprime os dados
    }

    // Imprime os resultados
    printf("\nResultados da ordenação:\n");
    printf("Método: %d\n",dados. metodo);
    printf("Quantidade: %d\n", dados.quantidade);
    printf("Situação: %d\n", dados.situacao);
    printf("Leituras: %ld\n",dados.acessos.num_leituras);
    printf("Escritas: %ld\n", dados.acessos.num_escritas);
    printf("Comparações: %ld\n", dados.acessos.num_comparacoes);
    printf("Tempo de execução: %.6f segundos\n", tempo_execucao);

    // Printa os dados da ordenacao
    // exibirInformacoesOrdenacao(dados);

    remove(arquivo_entrada);

    return 0;
}

Dados inicializaDados()
{
    Dados dados;

    dados.quantidade = 0;
    dados.metodo = 0;
    dados.situacao = 0;
    dados.imprimir = false;
    dados.nomeArquivo[0] = '\0';
    dados.acessos.num_leituras = 0;
    dados.acessos.num_escritas = 0;
    dados.acessos.num_comparacoes = 0;

    return dados;
}

// void gerarArquivoCopia(Dados *Dados)
// {
//     FILE *arq;
//     char ordenacao[20];
//     if (Dados->situacao == 1)
//     {
//         arq = fopen("provaoCrescente.bin", "rb");
//         strcpy(ordenacao, "crescente");
//     }
//     else if (Dados->situacao == 2)
//     {
//         arq = fopen("provaoDecrescente.bin", "rb");
//         strcpy(ordenacao, "decrescente");
//     }
//     else
//     {
//         arq = fopen("provaoAleatorio.bin", "rb");

//         strcpy(ordenacao, "aleatorio");
//     }

//     char metodo[20];
//     // if(Dados->metodo == BALANCEADA_BLOCO_OI) strcpy(metodo, "Bloco_ord_interna");
//     // else if(Dados->metodo == BALANCEADA_HEAP) strcpy(metodo, "Bloco_heap");
//     // else strcpy(metodo, "QuickSort");

//     strcpy(metodo, "QuickSort");

//     // Lendo os n primeiros dados do arquivo de origem
//     TipoRegistro *registros = malloc(Dados->quantidade * sizeof(TipoRegistro));
//     fread(registros, sizeof(TipoRegistro), Dados->quantidade, arq);
//     Dados->acessos.qtdLeitura += 1;

//     // Gerando o nome do arquivo de destino
//     char arquivoDestino[50];
//     sprintf(arquivoDestino, "%s-%s-%d.bin", metodo, ordenacao, Dados->quantidade);
//     strcpy(Dados->nomeArquivo, arquivoDestino);

//     // Escrevendo os n primeiros dados no arquivo de destino
//     FILE *novoArq = fopen(arquivoDestino, "wb+");
//     fwrite(registros, sizeof(TipoRegistro), Dados->quantidade, novoArq);
//     Dados->acessos.qtdEscrita += 1;

//     fclose(arq);
//     fclose(novoArq);
//     free(registros);
// }

// void binarioParaTXT_printarDados(Dados *Dados)
// {

//     FILE *arqOrigem = fopen(Dados->nomeArquivo, "rb");

//     // Criando e abrindo o arquivo de saida
//     char nomeArqDestino[100];
//     strcpy(nomeArqDestino, Dados->nomeArquivo);
//     int tamNomeArquivo = strlen(nomeArqDestino);
//     nomeArqDestino[tamNomeArquivo - 1] = 't';
//     nomeArqDestino[tamNomeArquivo - 2] = 'x';
//     nomeArqDestino[tamNomeArquivo - 3] = 't';

//     FILE *arqDestino = fopen(nomeArqDestino, "w");

//     // Lendo os dados do binario e escrevendo no txt
//     TipoRegistro buffer[20];
//     size_t itensLidos;

//     if (!Dados->imprimir)
//     {
//         while ((itensLidos = fread(buffer, sizeof(TipoRegistro), 20, arqOrigem)) > 0)
//         {
//             // Dados->acessos.qtdLeituraBinTxt += 1;
//             for (int i = 0; i < itensLidos; i++)
//             {
//                 fprintf(arqDestino, "%-8d %-5.2f %-2s %-50s %-30s\n", buffer[i].inscricao, buffer[i].nota, buffer[i].estado, buffer[i].cidade, buffer[i].curso);
//                 // Dados->acessos.qtdEscritaBinTxt += 1;
//             }
//         }
//     }
//     else
//     {
//         printf("\n");
//         while ((itensLidos = fread(buffer, sizeof(TipoRegistro), 20, arqOrigem)) > 0)
//         {
//             // Dados->acessos.qtdLeituraBinTxt += 1;
//             for (int i = 0; i < itensLidos; i++)
//             {
//                 printf("%-8d %-5.2f %-2s %-50s %-30s\n", buffer[i].inscricao, buffer[i].nota, buffer[i].estado, buffer[i].cidade, buffer[i].curso);
//                 fprintf(arqDestino, "%-8d %-5.2f %-2s %-50s %-30s\n", buffer[i].inscricao, buffer[i].nota, buffer[i].estado, buffer[i].cidade, buffer[i].curso);
//                 // Dados->acessos.qtdEscritaBinTxt += 1;
//             }
//         }
//         printf("\n");
//     }

//     fclose(arqDestino);
//     fclose(arqOrigem);
// }

// void exibirInformacoesOrdenacao(Dados dados)
// {
//     printf("Quantidade de leitura:                                    %7d\n", dados.acessos.qtdLeitura);

//     // quicksort
//     // if(dados.metodo != 3) printf("Quantidade de leitura na geração de blocos:               %7d\n", dados.acessos.qtdLeituraGeracaoBlocos);

//     printf("Quantidade de leitura na transformação de .bin para .txt: %7d\n", dados.acessos.qtdLeituraBinTxt);
//     int qtdLeituraTotal = dados.acessos.qtdLeitura + dados.acessos.qtdLeituraGeracaoBlocos + dados.acessos.qtdLeituraBinTxt;
//     printf("Quantidade de leituras totais:                            %7d\n\n", qtdLeituraTotal);

//     printf("Quantidade de escrita:                                    %7d\n", dados.acessos.qtdEscrita);
//     if (dados.metodo != QUICKSORT)
//         printf("Quantidade de escrita na geração de blocos:               %7d\n", dados.acessos.qtdEscritaGeracaoBlocos);
//     printf("Quantidade de escrita na transformação de .bin para .txt: %7d\n", dados.acessos.qtdEscritaBinTxt);
//     int qtdEscritaTotal = dados.acessos.qtdEscrita + dados.acessos.qtdEscritaGeracaoBlocos + dados.acessos.qtdEscritaBinTxt;
//     printf("Quantidade de escritas totais:                            %7d\n\n", qtdEscritaTotal);

//     printf("Quantidade de comparações entre notas: %d\n", dados.acessos.comparacoesChave);

//     double tempoExecucao = ((double)(dados.acessos.horarioFim - dados.acessos.horarioInicio)) / CLOCKS_PER_SEC;

//     printf("Tempo de execução: %lfs.\n", tempoExecucao);
// }