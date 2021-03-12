//
// Created by Victor on 02/02/2018.
//

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "ILS.h"
#include "solucaogulosa.h"

using namespace std;

int main(){
    char nomeArquivoTXT[30] = "binpack0.txt";
    int n, p;
    float *vetor_pesos;
    int *s;
    int fo;
    float tamPart;

    srand(time(NULL));
    copiaArquivo(nomeArquivoTXT, &n, &p, &tamPart, &vetor_pesos);
    cout << "Numero de itens: " << n << " Numero de particoes: " << p << endl;

    s = new int [n];
    inicializa_vetor_int(s, n);
    constroi_solucao_gulosa(s, vetor_pesos, n, p, &fo);

    cout << "Solucao inicial: " << fo << endl;
    fo = ILS(n, s, vetor_pesos, 20, 10, p, tamPart);

    cout << "Solucao final: " << fo << endl;
    return 0;
}