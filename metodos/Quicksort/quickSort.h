#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include "estruturas.h"
#include "area.h"

void quickSort(Dados * Dados);

void QuicksortExterno(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, int Esq, int Dir, Dados * Dados);

//Le o dado do arquivo superior
void LeSup(FILE **ArqLEs, TipoRegistro *UltLido, int *Ls, short *OndeLer, Dados * Dados);
//Le o dado do arquivo inferior
void LeInf(FILE **ArqLi, TipoRegistro *UltLido, int *Li, short *OndeLer, Dados * Dados);

void InserirArea(TipoArea *Area, TipoRegistro *UltLido, int *NRArea, Dados *);

//Escreve o item no arquivo superior
void EscreveMax(FILE **ArqLEs, TipoRegistro R, int *Es, Dados * Dados);

//Escreve o item no arquivo inferior
void EscreveMin(FILE **ArqEi, TipoRegistro R, int *Ei, Dados * Dados);

//Remove o maior valor do pivo
void RetiraMax(TipoArea *Area, TipoRegistro *R, int *NRArea);

//Remove o menor valor do pivo
void RetiraMin(TipoArea *Area, TipoRegistro *R, int *NRArea);

void Particao(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, TipoArea Area, int Esq, int Dir, int *i, int *j, Dados * Dados);

//HeapSort:

// faz a comparacao para ver se registro1 > registro2
int compare(RegistroSubstituicao registro1, RegistroSubstituicao t2, Dados *Dados);

//QuickSort Interno:

void trocarPosicao(TipoRegistro* registros, int * i, int * j);

void quicksortInterno(TipoRegistro * registros, int inicio, int fim, Dados *Dados);

void quicksortInterno_SelecaoSubstituicao(RegistroSubstituicao * registros, int inicio, int fim, Dados *Dados);

#endif