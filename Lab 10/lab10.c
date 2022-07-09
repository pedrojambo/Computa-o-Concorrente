#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>

#define L 4 //numero de threads leitoras
#define E 2 //numero de threads escritoras

sem_t em_e, em_l, escr, leit; //semaforos
int e=0, l=0;                 //globais


//thread leitora
void * leitor (void * arg) {
  int *id = (int *) arg;
  while(1) {
    printf("L[%d] quer ler\n", *id);
    sem_wait(&leit);
    sem_wait(&em_l); l++;
    if(l==1) sem_wait(&escr);
    sem_post(&em_l);
    sem_post(&leit);
    printf("L[%d] lendo\n", *id);
    sleep(1);
    printf("L[%d] terminou de ler\n", *id);
    sem_wait(&em_l); l--;
    if(l==0) sem_post(&escr);
    sem_post(&em_l);
    }
  free(arg);
  pthread_exit(NULL);
}

//thread escritora
void * escritor (void * arg) {
  int *id = (int *) arg;
  while(1) {
    printf("E[%d] quer escrever\n", *id);
    sem_wait(&em_e); e++;
    if(e==1) sem_wait(&leit);
    sem_post(&em_e);
    sem_wait(&escr);
    printf("E[%d] escrevendo\n", *id);
    sem_post(&escr);
    printf("E[%d] terminou de escrever\n", *id);
    sem_wait(&em_e); e--;
    if(e==0) sem_post(&leit);
    sem_post(&em_e);
    sleep(1);
    }
  free(arg);
  pthread_exit(NULL);
}

//funcao principal
int main(void) {
  //identificadores das threads
  pthread_t tid[L+E];
  int id[L+E];

  //inicializa semáforos
  sem_init(&em_e, 0, 1);
  sem_init(&em_l, 0, 1);
  sem_init(&escr, 0, 1);
  sem_init(&leit, 0, 1);

  //cria as threads leitoras
  for(int i=0; i<L; i++) {
    id[i] = i+1;
    if(pthread_create(&tid[i], NULL, leitor, (void *) &id[i])) exit(-1);
  } 
  
  //cria as threads escritoras
  for(int i=0; i<E; i++) {
    id[i+L] = i+1;
    if(pthread_create(&tid[i+L], NULL, escritor, (void *) &id[i+L])) exit(-1);
  } 

  // aguardas as threads terminarem
  for (int i = 0; i < (L+E); i++) {
    pthread_join(tid[i], NULL);
  }

  pthread_exit(NULL);
  return 0;
}