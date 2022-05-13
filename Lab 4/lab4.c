#include <stdio.h> 
#include <stdlib.h>  
#include <pthread.h> 
#include "timer.h" 
#include <math.h> 
 
long long int dim;       //tamanho do vetor de entrada 
int varGlobal; 
int* vetor;              //vetor de entrada 
float* vetor_S;          //vetor a ser preenchido pelo programa sequencial 
float* vetor_C;          //vetor a ser preenchido pelo programa concorrente 
int NTHREADS;            //numero de threads 
pthread_mutex_t mutex;   //variavel de lock para exclusao mutua 
 
int ehPrimo(int n) { 
    if (n<=1) return 0; 
    if (n==2) return 1; 
    if (n%2==0) return 0; 
    for (int i=3; i<sqrt(n)+1; i+=2){ 
        if(n%i==0) return 0; 
    } 
    return 1; 
    } 
 
void *tarefa(void* arg){  
    float* vetorThreads = (float *) arg;  
    int i = 0;  
     
    while(i < dim){  
  
        pthread_mutex_lock(&mutex);  
        i = varGlobal++;  
        pthread_mutex_unlock(&mutex);  
  
        if (ehPrimo(vetor[i]))  
            vetorThreads[i] = sqrt(vetor[i]);  
        else  
            vetorThreads[i] = vetor[i];  
  
    }  
    pthread_exit(NULL);  
} 
 
int main(int argc, char *argv[]) { 
  if(argc < 3) { 
       fprintf(stderr, "Digite: %s <numero de elementos do vetor> <numero threads>\n", argv[0]); 
       return 1;  
   } 
  dim = atoll(argv[1]); 
  NTHREADS = atoi(argv[2]); 
  pthread_t *tid; 
  double ini, fim; 
 
  //aloca os vetores 
   vetor_S = (float*) malloc(sizeof(float)*dim); 
   if(vetor_S == NULL) { 
      fprintf(stderr, "ERRO--malloc\n"); 
      return 2; 
   } 
   vetor_C = (float*) malloc(sizeof(float)*dim); 
   if(vetor_C == NULL) { 
      fprintf(stderr, "ERRO--malloc\n"); 
      return 2; 
   } 
   vetor = (int*) malloc(sizeof(int)*dim); 
   if(vetor == NULL) { 
      fprintf(stderr, "ERRO--malloc\n"); 
      return 2; 
   } 
   tid = (pthread_t *)malloc(sizeof(pthread_t) * NTHREADS); 
    if (tid == NULL){ 
        fprintf(stderr, "ERRO--malloc 4\n"); 
        exit(-1); 
    } 
 
   //preenche os vetores sequencial e concorrente 
   srand(time(NULL));  
   for(long long int i=0; i<dim; i++){ 
      int rand1 = rand()%10000000; 
      vetor[i] = rand1;      
   } 
 
  //programa sequencial 
  GET_TIME(ini); 
  for(long long int i=0; i<dim; i++) { 
    if (ehPrimo(vetor[i])) 
      vetor_S[i] = sqrt(vetor[i]); 
    else 
      vetor_S[i] = vetor[i]; 
    } 
   
  GET_TIME(fim); 
  printf("Tempo sequencial: %lf\n", fim-ini); 
 
   
  GET_TIME(ini); 
   
  //--inicilaiza o mutex (lock de exclusao mutua) 
  pthread_mutex_init(&mutex, NULL); 
  //cria as threads 
  for (long int i = 0; i < NTHREADS; i++){ 
        if (pthread_create(tid + i, NULL, tarefa, (void *)vetor_C)){ 
            fprintf(stderr, "ERRO--pthread_create\n"); 
            return 3; 
        } 
    } 
 
    for (long int i = 0; i < NTHREADS; i++){ 
        if (pthread_join(*(tid + i), NULL)){ 
            fprintf(stderr, "ERRO--pthread_create\n"); 
            return 3; 
        } 
    } 
   
  GET_TIME(fim); 
  printf("Tempo Concorrente: %lf\n", fim-ini); 
  pthread_exit(NULL); 
 
  //teste de corretude 
  for(long long int i=0; i<dim; i++){ 
    if(vetor_C[i]!=vetor_S[i]){ 
      printf("Erro--vetores nao sao iguais"); 
      break; 
    } 
  } 
}
