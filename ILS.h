#ifndef ILS_H_
#define ILS_H_

void atualiza_vetor(float *a, float *b, int n);
void libera_vetor(float *a);
int ILS(int n, int *s, float *d, int vezesSemMelhora, int nNivelSemMelhora, int p, float tamP);
int descida(int *s, float *vetor_peso, int n, int p, int *tipo_mov, float tamP);
void inicializa_soma_particao(float *somaP, int *s, int n, float *vetor_peso);
int melhor_vizinho(int n, int p, int *s, float *somaP, float *vetor_peso, int fo, int *melhor_i,
                     int *melhor_j, float tamP);
void atualiza_soma_particao(float *somaP, int *s_anterior, int melhor_i, int melhor_j, int tipo_mov, float *vetor_peso);

#endif