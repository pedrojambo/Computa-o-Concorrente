#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>
#define NTHREADS 2 

//vetor global que será utilizado
int vector[10000];

//funcao que a thread ira realizar: elevar cada elemento da sua porção do vetor ao quadrado
void * quadrado (void * arg) {
    int ident = * (int *) arg;
    int i = (10000/(ident)) - 1;
    int j = 0;
    while(j != 5000){
        vector[i] = (vector[i]*vector[i]);
        j++;
        i--;
    }
    pthread_exit(NULL);
}

//funcao principal
int main() {
    int c;
    for(c=0; c<10000;c++){
        vector[c] = c;
    }
    pthread_t tid[NTHREADS]; 
    int ident[NTHREADS];
     for(int i=1; i<=NTHREADS; i++) {
       ident[i-1] = i;
       if (pthread_create(&tid[i-1], NULL, quadrado, (void *)&ident[i-1])) 
          printf("ERRO -- pthread_create\n");
    }

    //espera as threads terminarem 
    for(int i=0; i<NTHREADS; i++) {
       if (pthread_join(tid[i], NULL)) 
          printf("ERRO -- pthread_join\n");
    }

    //Testa se cada elemento do vetor foi elevado ao quadrado. Aponta caso ocorra algum erro
    for(int i=0; i<10000; i++) {
       if (vector[i] != (i * i)) {
          printf("ERRO -- quadrado\n");
          break;
       }
    }
    return 0;
}