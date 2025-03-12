#ifndef FUNCOESREGISTRO_H
#define FUNCOESREGISTRO_H

#include "estruturas.h"

// Função para ler um registro do arquivo
bool lerRegistro(FILE *arquivo, TipoRegistro *reg, AcessoArquivo *acessos);

// Função para escrever um registro no arquivo
void escreverRegistro(FILE *arquivo, TipoRegistro *reg, AcessoArquivo *acessos);

// Função para imprimir um registro na tela
void imprimirRegistro(TipoRegistro *reg);

// Função para comparar dois registros (pela nota)
int compararRegistros(TipoRegistro *a, TipoRegistro *b, AcessoArquivo *acessos);

#endif