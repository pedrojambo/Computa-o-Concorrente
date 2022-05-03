//encontra o maior e o menor valor de um vetor de numeros reais
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include "timer.h"

long long int N; //tamanho do vetor de entrada
int nthreads; //numero de threads
double *vetor; //vetor de entrada com tamanho N 
double maiorSequencial = 0; //maior valor do programa sequencial
double menorSequencial = 0; //menor valor do programa sequencial
double maiorConcorrente = 0; //maior valor do programa concorrente
double menorConcorrente = 0; //menor valor do programa conorrente


//fluxo das threads
void * tarefa(void * arg) {
   long int id = (long int) arg; //identificador da thread
   long int tamBloco = N/nthreads;  //tamanho do bloco de cada thread 
   long int ini = id * tamBloco; //elemento inicial do bloco da thread
   long int fim; //elemento final(nao processado) do bloco da thread
   if(id == nthreads-1) fim = N;
   else fim = ini + tamBloco; //trata o resto se houver
   //atualiza a variavel maiorConcorrente e menorConcorrente quando necessario
   for(long int i=ini; i<fim; i++){
      if(vetor[i]>maiorConcorrente) maiorConcorrente = vetor[i];
      if(vetor[i]<menorConcorrente) menorConcorrente = vetor[i];
    }
   pthread_exit(NULL); 
}

//fluxo principal
int main(int argc, char *argv[]) {
   double ini, fim; //tomada de tempo
   pthread_t *tid; //identificadores das threads no sistema

   //recebe e valida os parametros de entrada (tamanho do vetor, numero de threads)
   if(argc < 3) {
       fprintf(stderr, "Digite: %s <numero de elementos do vetor> <numero threads>\n", argv[0]);
       return 1; 
   }
   N = atoll(argv[1]);
   nthreads = atoi(argv[2]);
   //aloca o vetor de entrada
   vetor = (double*) malloc(sizeof(double)*N);
   if(vetor == NULL) {
      fprintf(stderr, "ERRO--malloc\n");
      return 2;
   }
   //preenche o vetor de entrada
   srand(time(NULL)); 
   for(long int i=0; i<N; i++){
      float rand1 = rand();
      vetor[i] = rand1;
    }

   //maior e menor sequencial
   GET_TIME(ini);
   for(long int i=0; i<N; i++){
      if(vetor[i]>maiorSequencial) maiorSequencial = vetor[i];
      if(vetor[i]<menorSequencial) menorSequencial = vetor[i];
    }
   GET_TIME(fim);
   printf("\nTempo sequencial:  %lf\n", fim-ini);

   //soma concorrente dos elementos
   GET_TIME(ini);
   tid = (pthread_t *) malloc(sizeof(pthread_t) * nthreads);
   if(tid==NULL) {
      fprintf(stderr, "ERRO--malloc\n");
      return 2;
   }
   //criar as threads
   for(long int i=0; i<nthreads; i++) {
      if(pthread_create(tid+i, NULL, tarefa, (void*) i)){
         fprintf(stderr, "ERRO--pthread_create\n");
         return 3;
      }
   }
   //aguardar o termino das threads
   for(int i=0; i<nthreads; i++) {
      pthread_join(*(tid+i), NULL);
   }
   
   GET_TIME(fim);
   printf("Tempo concorrente:  %lf\n\n", fim-ini);

   //exibir os resultados
   //printf("Maior Sequencial:  %.12lf\nMenor Sequencial:  %.12lf\n", maiorSequencial, menorSequencial);
   //printf("Maior Concorrente:  %.12lf\nMenor Concorrente:  %.12lf\n", maiorConcorrente, menorConcorrente);

   //verificacao de corretude
   if(maiorSequencial != maiorConcorrente || menorSequencial != menorConcorrente){
       fprintf(stderr, "ERRO--resultados sequencial e concorrente diferentes");
   }


   //libera as areas de memoria alocadas
   free(vetor);
   free(tid);

   return 0;
}
