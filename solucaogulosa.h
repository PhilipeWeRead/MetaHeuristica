//
// Created by Victor on 23/01/2018.
//

#ifndef TP_SOLUCAOGULOSA_H
#define TP_SOLUCAOGULOSA_H

#include"lista.h"
#include"util.h"

void copiaArquivo(char nomeArq[], int *n, int *p, float *tamPart, float **vetor_pesos);
void constroi_solucao_gulosa(int *s, float *vetor_peso, int m, int p, int *fo);


#endif //TP_SOLUCAOGULOSA_H
