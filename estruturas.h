// Jordan Assunção Santos Mendonça || Nº Matrícula: 23.2.4070
// Filipe Hermenegildo da Cunha || Nº Matrícula: 23.2.4123

#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição das constantes
#define MAX_FITAS_2F 20 // 10 entrada + 10 saída
#define MAX_FITAS_F1 20 // 19 entrada + 1 saída

#define TAM_BUFFER_2F 10 // Tamanho do buffer para o método 1
#define TAM_BUFFER_F1 19 // Tamanho do buffer para o método 2
#define TAM_BUFFER_QS 10 // Tamanho do buffer para o método 3

#define MAX_REG_LINHA 200 // Tamanho máximo de uma linha do arquivo

// Estrutura para armazenar os dados de um registro (aluno)
typedef struct
{
	long int inscricao;
	double nota;
	char estado[3];
	char cidade[51];
	char curso[31];
} TipoRegistro;

// Estrutura para armazenar os dados de acesso ao arquivo
typedef struct
{
	int num_leituras;
	int num_escritas;
	int num_comparacoes;

	int num_LeituraBinTxt;
	int num_EscritaBinTxt;

	int num_LeituraGeracaoBlocos;
	int num_EscritaGeracaoBlocos;

	int num_ComparacaoGeracaoBlocos;

	int comparacoesNotas;

	clock_t tempoInicio;
	clock_t tempoFim;
} AcessoArquivo;
typedef struct
{
	AcessoArquivo acessos;
	int quantidade;
	int metodo;
	int situacao;
	bool imprimir;
	char nomeArquivo[50];
} Dados;

Dados inicializaDados();

#endif