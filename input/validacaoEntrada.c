// Jordan Assunção Santos Mendonça || Nº Matrícula: 23.2.4070
// Filipe Hermenegildo da Cunha || Nº Matrícula: 23.2.4123

#include "validacaoEntrada.h"

int validacaoEntrada(int argc, char **argv, Dados * Dados)
{

    int dadosValidados = 0;

    if (argc < 4)
    {
        printf("ERRO: Quantidade inválida de argumentos na entrada!\n\n");
        printf("Uso: %s <metodo> <quantidade> <situacao> [-P]\n", argv[0]);
        printf("Onde:\n");
        printf("  <metodo>: 1, 2 ou 3\n");
        printf("  <quantidade>: número de registros a serem ordenados\n");
        printf("  <situacao>: 1 (asc), 2 (desc) ou 3 (aleatório)\n");
        printf("  [-P]: opcional para imprimir os dados\n"); 
    }

    int metodo = atoi(argv[1]);
    int quantidade = atoi(argv[2]);
    int situacao = atoi(argv[3]);
    bool imprimir = false;

    if (argc > 4 && (strcmp(argv[4], "-P") == 0 || strcmp(argv[4], "-p") == 0))
    {
        imprimir = true;
        dadosValidados = 1;
    }

    // Verificação dos parâmetros

    if (metodo < 1 || metodo > 3)
    {
        printf("ERRO: Método inválido!\n Use 1 (2f fitas), 2 (f+1 fitas) ou 3 (Quicksort Externo).\n");
        dadosValidados = 0;
    }
    else{
        dadosValidados = 1;
    }

    if (quantidade != 100 && quantidade != 200 && quantidade != 2000 &&
        quantidade != 20000 && quantidade != 200000 && quantidade != 471705)
    {
        printf("ERRO: Quantidade inválida!\n Use 100, 200, 2000, 20000, 200000 ou 471705.\n");
        dadosValidados = 0;
    }
    else{
        dadosValidados = 1;
    }

    if (situacao < 1 || situacao > 3)
    {
        printf("Situação inválida. Use 1 (asc), 2 (desc) ou 3 (aleatório).\n");
        dadosValidados = 0;
    } else{
        dadosValidados = 1;
    }

    Dados->quantidade = quantidade;
    Dados->metodo = metodo;
    Dados->situacao = situacao;
    Dados->imprimir = imprimir;
    // DadosnomeArquivo = "saida.txt";
    // Dados->acessos = acessos;

    return dadosValidados;
}
