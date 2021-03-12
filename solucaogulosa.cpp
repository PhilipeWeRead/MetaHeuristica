//
// Created by Victor on 23/01/2018.
//

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "solucaogulosa.h"

using namespace std;

void copiaArquivo(char nomeArq[], int *n, int *p, float *tamPart, float **vetor_pesos) {
    FILE *Arq;
    int nItens;
    int nParticoes;
    float tamanhoPart;
    float *teste;

    if ((Arq = fopen(nomeArq,"r")) == NULL) {
        cout << "Erro ao abrir arquivo " << nomeArq << "." << endl;
        exit(1);
    }

    // recebe a quantidade de itens que serão lidos, o número de partições e o seu tamanho
    fscanf (Arq, "%d", &nItens);
    fscanf (Arq, "%d", &nParticoes);
    fscanf (Arq, "%f", &tamanhoPart);

    teste = cria_vetor(nItens);

    inicializa_vetor(teste, nItens);

    float aux;
    int i=0;
    // retira os pesos dos itens do arquivo e os insere no vetor
    while(!feof(Arq)){
        fscanf(Arq, "%f\n", &aux);
        teste[i++] = aux;
    }

    *tamPart = tamanhoPart;
    *n = nItens;
    *p = nParticoes;
    *vetor_pesos = teste;

    fclose(Arq);
}

void constroi_solucao_gulosa(int *s, float *vetor_peso, int m, int p, int *fo) {
    float soma_particao[p];
    Itens list[m];
    int i, min_part;
    inicializa_vetor(soma_particao, p);

    for(i = 0; i < m; i++) {
        list[i].peso = vetor_peso[i];
        list[i].id_item = i;
    }

/* Funcao que ordena usando o metodo quicksort */
    // ordena
    qsort(list, m, sizeof(Itens), compare); // tem a funcao compare em Util.h

    for(i = 0; i < m; i++) {
        min_part = min_valor_vetor(soma_particao, p);
        soma_particao[min_part] = soma_particao[min_part] + list[i].peso;
        s[list[i].id_item] = min_part;
    }

    int aux=0;

    // Verifica quantas partições (bins) foram usados
    for(i=0; i<p; i++){
        cout << "particao " << i+1 << ": " << soma_particao[i] << endl;
        if(soma_particao[i] > 0)
            aux++;
    }
    *fo = aux;
}

