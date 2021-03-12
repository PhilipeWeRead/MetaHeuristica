#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "Util.h"
#include "ILS.h"

using namespace std;

void atualiza_vetor(int *a, int *b, int n){
    for(int i=0; i<n; i++)
        a[i] = b[i];
}

void libera_vetor(int *a){
    delete []a;
}

int ILS(int n, int *s, float *d, int vezesSemMelhora, int nNivelSemMelhora, int p, float tamP){

	int i, j, lvl;
	int iter, MelhorIter;
	int *sL;
	int fo, foL;
    int tipo_mov;
	float somaP[p];
	inicializa_vetor(somaP, p);

	sL = new int[n];
	fo = descida(s, d, n, p, &tipo_mov, tamP);
	iter = MelhorIter = 0;
	lvl = 1;

	while(iter - MelhorIter < nNivelSemMelhora){
		iter++;
		
		atualiza_vetor(sL,s,n);
		int vezes = 0;
        inicializa_soma_particao(somaP, s, n, d);
		
		while (vezes < vezesSemMelhora){
			int ntrocasmax = lvl + 1;
			int ntrocas = 0;
			
			atualiza_vetor(sL,s,n);

			tipo_mov = rand() % 2+1;
			foL = fo;
			while (ntrocas < ntrocasmax) {
				ntrocas++;
				if(tipo_mov == 1){
					i = rand() % n;
					do {
						j = rand() % p;
					} while (sL[i] == j && somaP[j] + d[i] > tamP);
					sL[i] = j;
				}

				if(tipo_mov == 2){
					i = rand() % n;
					do {
						j = rand() % n;
					} while (i == j && somaP[sL[i]] + d[j] - d[i] <= tamP && somaP[sL[j]] + d[i] - d[j] <= tamP);
					int aux;
					aux = sL[i];
					sL[i] = sL[j];
					sL[j] = aux;
					
				}
			} // fim while que faz numero de trocas maximo
			foL = descida(sL, d, n, p, &tipo_mov, tamP);

			if (foL < fo){

				fo = foL;
				atualiza_vetor(s,sL,n);
				vezes = 0;
				lvl = 1;
				MelhorIter = iter;
				printf("fo = %d \n", fo);

				}
				vezes++;
			} 
			lvl++;
			printf("Aumentando o nivel perturbacao para %2d \n",lvl);
	}

	libera_vetor(sL);
	return fo;
}

int descida(int *s, float *vetor_peso, int n, int p, int *tipo_mov, float tamP){

    int aux, melhor_i, melhor_j;
    float somaP[p];
    int foMelhorV, fo;
    bool melhorou;

    inicializa_vetor(somaP, p);
    inicializa_soma_particao(somaP, s, n, vetor_peso);
    aux = 0;

    for(int i=0; i<p; i++){
        if (somaP[i] > 0)
            aux++;
    }
    fo = foMelhorV = aux;

    do{
        melhorou = false;
		
		foMelhorV = melhor_vizinho(n, p, s, somaP, vetor_peso, fo, &melhor_i, &melhor_j, tamP);

        if (foMelhorV < fo) {
            // movimento do tipo mudanca de uma bin para outra particao
			*tipo_mov = 1;
            atualiza_soma_particao(somaP, s, melhor_i, melhor_j, *tipo_mov, vetor_peso);
            s[melhor_i] = melhor_j;
            fo = foMelhorV;
            melhorou = true;
			continue;
        }
    } while (melhorou == true);
    return fo;
}
void inicializa_soma_particao(float *somaP, int *s, int n, float *vetor_peso){
    int i;
    for(i=0; i < n; i++){
        somaP[s[i]] = somaP[s[i]] + vetor_peso[i];
    }

}

int melhor_vizinho(int n, int p, int *s, float *somaP, float *vetor_peso, int fo, int *melhor_i,
                     int *melhor_j, float tamP){

    int aux, part_i;
    int foMelhorV = fo;
	float somaPart[p];
	inicializa_vetor(somaPart, p);
	inicializa_soma_particao(somaPart, s, n, vetor_peso);
    //fazendo a vizinhanca do movimento mudanca de uma bin para outra particao

        for (int i = 0; i < n - 1; i++) { 
            part_i = s[i];
            for (int j = 0; j < p; j++) { //percorre as particoes(conteiners)
                if (j != part_i) {
                    atualiza_soma_particao(somaPart, s, i, j, 1, vetor_peso);
                    int aux2 = s[i];
					
                    bool teste = true;
                    for (int x = 0; x < p; x++) {
                        if (somaPart[x] > tamP) {
                            teste = false;
                            atualiza_soma_particao(somaPart, s, i, aux2, 1, vetor_peso);
                        }
                    }

                    if (teste) {
						int delta = 0; //delta eh a fo deste vizinho
                    for (int x = 0; x < p; x++) {
                        if (somaPart[x] > 0) {
                            delta++;
                        }
                    }

                    //faz o movimento
                    aux = s[i];
                    s[i] = j;

                    if (delta < foMelhorV) {
                        *melhor_i = i;
                        *melhor_j = j;
                        foMelhorV = delta;
                    }
                    //desfaz o movimento
                    atualiza_soma_particao(somaPart, s, i, aux, 1, vetor_peso);
                    s[i] = aux;
                }
            }
        }
    }

    return foMelhorV;
}

void atualiza_soma_particao(float *somaP, int *s_anterior, int melhor_i, int melhor_j, int tipo_mov, float *vetor_peso){
    int aux;
    if(tipo_mov==1){ 
        aux = s_anterior[melhor_i]; 
        somaP[aux] = somaP[aux] - vetor_peso[melhor_i];
        somaP[melhor_j] = somaP[melhor_j] + vetor_peso[melhor_i];
    }else{
        
        somaP[s_anterior[melhor_i]] = somaP[s_anterior[melhor_i]] -
                                      vetor_peso[melhor_i] + vetor_peso[melhor_j];
        somaP[s_anterior[melhor_j]] = somaP[s_anterior[melhor_j]] - vetor_peso[melhor_j] + vetor_peso[melhor_i];
    }
}