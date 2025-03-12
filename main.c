#include "estruturas.h"

#include "input/validacaoEntrada.h"

#include "funcoesOrdenacao.h"
#include "funcoesRegistro.h"

#include "metodos/Quicksort/quickSort.h"

int main(int argc, char **argv)
{
    Dados dados = inicializaDados();

    // Validação dos parâmetros de entrada
    if (!validacaoEntrada(argc, argv, &dados))
        return 0;

    // Gera o arquivo de entrada de acordo com a situação
    gerarArquivoEntrada(&dados);

    // Seleciona o método de ordenação
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
        break;
    default:
        break;
    }

    // Transforma os dados do arquivo binario para o txt
    transformarArquivoBinarioParaTxt_ImprimirDados(&dados);

    // Finalizando a contagem de tempo do programa
    dados.acessos.tempoFim = clock();

    exibirResultados(&dados);

    return 0;
}

Dados inicializaDados()
{
    Dados dados;

    dados.quantidade = 0;
    dados.metodo = 0;
    dados.situacao = 0;
    dados.imprimir = false;
    dados.acessos.num_leituras = 0;
    dados.acessos.num_escritas = 0;
    dados.acessos.num_comparacoes = 0;

    dados.acessos.num_LeituraBinTxt = 0;
    dados.acessos.num_EscritaBinTxt = 0;

    dados.acessos.tempoInicio = clock();

    return dados;
}
