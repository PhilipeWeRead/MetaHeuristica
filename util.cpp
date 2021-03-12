//
// Created by Victor on 26/01/2018.
//

#include "util.h"

int compare (const void * a, const void * b)
{

    Itens *item_pesoA = (Itens *)a;
    Itens *item_pesoB = (Itens *)b;
    if (item_pesoA->peso == item_pesoB->peso) return 0;
    return (item_pesoA->peso > item_pesoB->peso) ? -1 : 1;

}

int min_valor_vetor(float *vetor, int p) {

    float min = vetor[0];
    int pos = 0;

    for(int i = 1; i<p; i++)
    {
        if(vetor[i] < min){
            min = vetor[i];
            pos = i;
        }
    }
    return pos;
}
int max_valor_vetor(float *vetor, int p){

    int max = vetor[0];
    int pos = 0;

    for(int i = 1; i<p; i++)
    {
        if(vetor[i] > max){
            max = vetor[i];
            pos = i;
        }
    }
    return pos;
}
