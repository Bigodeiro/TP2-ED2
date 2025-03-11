#ifndef AREA_H
#define AREA_H

#define TAMAREA  20

#include <stdio.h>
#include <stdlib.h>
#include "estruturas.h"

typedef struct TipoArea{
    TipoRegistro area [TAMAREA];
    int n;
}TipoArea;

TipoArea inicializaArea();

void InsereItem(TipoRegistro UltLido, TipoArea *Area, Dados*);

int ObterNumCelOcupadas(TipoArea * area);

void RetiraUltimo(TipoArea * area, TipoRegistro * R);

void RetiraPrimeiro(TipoArea * area, TipoRegistro * R);

// void ordenaArea(TipoRegistro * registros, int inicio, int fim);

// void trocaPosicao(TipoRegistro* registros, int * i, int * j);

#endif