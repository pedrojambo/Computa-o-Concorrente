#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#define NTHREADS  5

int x = 0;                 //variavel para controlar o disparo da ultima thread
sem_t condt1, condt2;     //semaforos para sincronizar a ordem de execucao das threads


void *um (void *t) {
  sem_wait(&condt2); //espera o restante das threads terminarem
  printf("Volte Sempre!\n");
  pthread_exit(NULL);
}


void *dois (void *t) {
  sem_wait(&condt1); //espera T1 executar
  printf("Fique a vontade.\n");
  x++;                  //incrementa o numero de threads executadas
  if(x==3){  //caso as 3 threads apos a thread cinco tenham executado, sinaliza a segunda condicao
    sem_post(&condt2); //permite que a thread um execute
  }
  sem_post(&condt1);
  pthread_exit(NULL);
}

void *tres (void *t) {
  sem_wait(&condt1); //espera T1 executar
  printf("Sente-se por favor.\n");
  x++;
  if(x==3){  //caso as 3 threads apos a thread cinco tenham executado, sinaliza a segunda condicao
    sem_post(&condt2); //permite que a thread um execute
  }
  sem_post(&condt1);
  pthread_exit(NULL);
}

void *quatro (void *t) {
  sem_wait(&condt1); //espera T1 executar
  printf("Aceita um copo d'água?\n");
  x++;
  if(x==3){  //caso as 3 threads apos a thread cinco tenham executado, sinaliza a segunda condicao
    sem_post(&condt2); //permite que a thread um execute
  }
  sem_post(&condt1);
  pthread_exit(NULL);
}

void *cinco (void *t) {
  printf("Seja bem-vindo!\n");
  sem_post(&condt1); //permite que as threads dois, tres e quatro executem
  pthread_exit(NULL);
}

/* Funcao principal */
int main(int argc, char *argv[]) {
  int i; 
  pthread_t threads[NTHREADS];

  //inicia os semaforos
  sem_init(&condt1, 0, 0);
  sem_init(&condt2, 0, 0);

  /* Cria as threads */
  pthread_create(&threads[0], NULL, cinco, NULL);
  pthread_create(&threads[1], NULL, dois, NULL);
  pthread_create(&threads[2], NULL, tres, NULL);
  pthread_create(&threads[3], NULL, quatro, NULL);
  pthread_create(&threads[4], NULL, um, NULL);

  

  /* Espera todas as threads completarem */
  for (i = 0; i < NTHREADS; i++) {
    pthread_join(threads[i], NULL);
  }

  /* Destroi os semaforos */
  sem_destroy(&condt1);
  sem_destroy(&condt2);
}