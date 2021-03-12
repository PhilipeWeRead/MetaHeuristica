//
// Created by Victor on 23/01/2018.
//
#include<iostream>
#include<cstdio>
#include<cstring>
#include "lista.h"

float *cria_vetor(int n){
    float *aux = new float [n];
    return aux;
}

void inicializa_vetor(float *vetor, int tam){
    for (int j=0; j<tam; j++) vetor[j] = 0;
}

void inicializa_vetor_int(int *vetor, int tam){
    for (int j=0; j<tam; j++) vetor[j] = 0;
}

Itens *cria_vetor_itens(int m){
    Itens *itens = new Itens [m];
    return itens;
}

void preenche_lista(char Nome_Arq, int m) {

}


void preenche_vetor_pesos(Itens *itens, double *vetor_pesos, int m){
    for(int i=0; i<m; i++){
        vetor_pesos[i] = itens[i].peso;
    }
}

void inicia_vetor_particoes(int *vetor_part, int p){
    for(int i=0; i<p; i++){
        vetor_part[i] = 0;
    }
}