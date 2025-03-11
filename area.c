#include "Quicksort/area.h"
#include "Quicksort/quickSort.h" 


TipoArea inicializaArea(){
    TipoArea area;
    area.n = 0;
    return area;
}

void InsereItem(TipoRegistro UltLido, TipoArea *Area, Dados* Dados){
    Area -> area[Area->n] = UltLido;
    Area -> n ++;
    quicksortInterno(Area->area, 0, Area->n - 1, Dados);
}

int ObterNumCelOcupadas(TipoArea * area){
    return area->n;
}

void RetiraUltimo(TipoArea * area, TipoRegistro * R){
    *R = area->area[area->n-1];
    area->n --;
}

void RetiraPrimeiro(TipoArea * area, TipoRegistro * R){
    *R = area->area[0];

    for(int i = 0; i < area->n; i++)
        area->area[i] = area->area[i+1];

    area->n--;
}