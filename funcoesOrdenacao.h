#ifndef FUNCOESORDENACAO_H
#define FUNCOESORDENACAO_H

#include "estruturas.h"
#include "funcoesRegistro.h"

#include "funcoesOrdenacao.h"

#include "Quicksort/quickSort.h"
// Função para ordenar o arquivo em ordem ascendente (para gerar o arquivo de entrada)
void ordenarArquivoAscendente(const char *arquivo_entrada, const char *arquivo_saida, int quantidade, Dados *dados);

// Função para ordenar o arquivo em ordem descendente (para gerar o arquivo de entrada)
void ordenarArquivoDescendente(const char *arquivo_entrada, const char *arquivo_saida, int quantidade, Dados *dados);

// Função para clonar parte do arquivo (para gerar o arquivo de entrada)
void clonarArquivoParcial(const char *arquivo_entrada, const char *arquivo_saida, int quantidade, Dados *dados);

// Função para gerar o arquivo de entrada
void gerarArquivoEntrada(const char *arquivo_original, const char *arquivo_entrada, Dados *dados);



#endif