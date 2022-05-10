/* Disciplina: Computacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Codigo: Comunicação entre threads usando variável compartilhada e exclusao mutua com bloqueio */

#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>
#include "timer.h"
#include <math.h>


long long int dim; //tamanho do vetor de entrada


int s = 0; //variavel compartilhada entre as threads
pthread_mutex_t mutex; //variavel de lock para exclusao mutua

int ehPrimo(long long int n) {
    if (n<=1) return 0;
    if (n==2) return 1;
    if (n%2==0) return 0;
    for (int i=3; i<sqrt(n)+1; i+=2)
        if(n%i==0) return 0;
    return 1;

//funcao executada pelas threads
void *ExecutaTarefa (void *threadid) {
  int i, tid = *(int*) threadid;
  printf("Thread : %d esta executando...\n", tid+1);
  for (i=0; i<1000000; i++) {
     //--entrada na SC
     pthread_mutex_lock(&mutex);
     //--SC
     s++; //incrementa o contador de tarefas realizadas 
     //--saida da SC
     pthread_mutex_unlock(&mutex);
  }
  printf("Thread : %d terminou!\n", tid+1);
  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  if(argc < 3) {
       fprintf(stderr, "Digite: %s <numero de elementos do vetor> <numero threads>\n", argv[0]);
       return 1; 
   }
  dim = atoll(argv[1]);
  NTHREADS = atoi(argv[2]);
  pthread_t tid[NTHREADS];
  int t, id[NTHREADS];
  double ini, fim;


  //programa sequencial
  GET_TIME(ini);
  void processaPrimos(int vetorEntrada[], float vetorSaida[], int dim) {
    for(int i=0; i<dim, i++) {
        if (ehPrimo(vetorEntrada[i])
        vetorSaida[i] = sqrt(vetorEntrada[i]);
    else
        vetorSaida[i] = vetorEntrada[i];
    }
  }
  GET_TIME(fim);
  double tempoSequencial = fim-ini;

  
  GET_TIME(ini);

  //--inicilaiza o mutex (lock de exclusao mutua)
  pthread_mutex_init(&mutex, NULL);

  for(t=0; t<NTHREADS; t++) {
    id[t]=t;
    if (pthread_create(&tid[t], NULL, ExecutaTarefa, (void *) &id[t])) {
      printf("--ERRO: pthread_create()\n"); exit(-1);
    }
  }
  //--espera todas as threads terminarem
  for (t=0; t<NTHREADS; t++) {
    if (pthread_join(tid[t], NULL)) {
         printf("--ERRO: pthread_join() \n"); exit(-1); 
    } 
  } 
  pthread_mutex_destroy(&mutex);

  GET_TIME(fim);

  printf("Valor de s = %d\n", s);
  printf("Tempo = %lf\n", fim-ini);
  pthread_exit(NULL);
}
