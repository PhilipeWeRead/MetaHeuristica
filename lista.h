//
// Created by Victor on 23/01/2018.
//

#ifndef TP_LISTA_H
#define TP_LISTA_H

typedef struct itens Itens;

struct itens {
    int id_item;
    double peso;
};

float *cria_vetor(int m);
void inicializa_vetor(float *vetor, int tam);
void inicializa_vetor_int(int *vetor, int tam);
Itens *cria_vetor_itens(int m);
void preenche_lista(char Nome_Arq, int m);
void preenche_vetor_pesos(Itens *itens, double *vetor_pesos, int m);
void cria_vetor_particoes(int p);

#endif //TP_LISTA_H
