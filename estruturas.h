// Jordan Assunção Santos Mendonça || Nº Matrícula: 23.2.4070
// Filipe Hermenegildo da Cunha || Nº Matrícula: 23.2.4123
#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H


#include <stddef.h>
#include <time.h>
#include <stdbool.h>

typedef struct{
	long int inscricao;
	double nota;
	char estado[3];
	char cidade[51];
	char curso[31];
}TipoRegistro;

// Registro que irá ser utilizado no quicksort interno
typedef struct {
    TipoRegistro registro;
    bool substituir; // Indica se o registro foi marcado para ser substituido
} RegistroSubstituicao;

typedef struct{
	int qtdLeitura;
	int qtdEscrita;

	int comparacoesChave;

	int movimentacoesInterna;
	int movimentacoesExterna;

	clock_t tempoInicio;
    clock_t tempoFim;
}Acessos;

typedef struct{
	Acessos acessos;
	int quantidade;
    int metodo;
    int situacao;
   	bool imprimir;
   	char nomeArquivo[50];
} Dados;

Dados inicializaDados();
void gerarArquivoCopia(Dados * Dados);
void binarioParaTXT_printarDados(Dados * Dados);

#endif