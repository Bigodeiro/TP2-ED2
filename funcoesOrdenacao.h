#ifndef FUNCOESORDENACAO_H
#define FUNCOESORDENACAO_H

#include "estruturas.h"
#include "funcoesRegistro.h"

#include "funcoesOrdenacao.h"

#include "Quicksort/quickSort.h"

// Função para gerar o arquivo de entrada
void gerarArquivoEntrada( Dados *dados);

void transformarArquivoBinarioParaTxt_ImprimirDados(Dados *dados);

void exibirResultados(Dados *dados);

#endif