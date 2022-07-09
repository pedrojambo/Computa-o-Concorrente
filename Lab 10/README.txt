(a) Para que o algoritmo funcione corretamente, o valor inicial dos semáforos (em_e, em_l, escr, leit) deve ser 1.

(b) É possível utilizar menos variáveis de sincronização caso implemente a solução sem a utilização de semáforos.

(c) Programa implementado nesse repositório. Segue alguns exemplos de execuções:

Threads leitoras:   4
Threads escritoras: 2 

L[1] quer ler
L[1] lendo
L[2] quer ler
L[2] lendo
L[3] quer ler
L[3] lendo
L[4] quer ler
L[4] lendo
E[1] quer escrever
E[2] quer escrever
L[1] terminou de ler
L[1] quer ler
L[2] terminou de ler
L[2] quer ler
L[3] terminou de ler
L[3] quer ler
L[4] terminou de ler
L[4] quer ler
E[1] escrevendo
E[1] terminou de escrever
E[2] escrevendo
E[2] terminou de escrever
L[1] lendo
L[2] lendo
L[3] lendo
L[4] lendo
E[1] quer escrever
E[2] quer escrever
L[1] terminou de ler
L[1] quer ler
L[2] terminou de ler
L[2] quer ler
L[3] terminou de ler
L[3] quer ler
L[4] terminou de ler
L[4] quer ler
E[1] escrevendo
E[1] terminou de escrever
E[2] escrevendo
E[2] terminou de escrever
L[1] lendo
L[3] lendo
L[4] lendo
L[2] lendo
E[1] quer escrever
E[2] quer escrever
L[4] terminou de ler
L[4] quer ler
L[3] terminou de ler
L[3] quer ler
L[2] terminou de ler
L[2] quer ler
L[1] terminou de ler
L[1] quer ler
E[1] escrevendo
E[1] terminou de escrever
E[2] escrevendo
E[2] terminou de escrever
L[4] lendo
L[3] lendo
L[2] lendo
L[1] lendo
E[1] quer escrever
E[2] quer escrever
L[4] terminou de ler
L[4] quer ler
L[3] terminou de ler
L[3] quer ler
L[2] terminou de ler
L[2] quer ler
L[1] terminou de ler
L[1] quer ler
E[1] escrevendo
E[1] terminou de escrever
E[2] escrevendo
E[2] terminou de escrever
L[4] lendo
L[3] lendo
L[2] lendo
L[1] lendo


Threads leitoras:   3
Threads escritoras: 3


L[1] quer ler
E[1] quer escrever
L[3] quer ler
L[1] lendo
E[2] quer escrever
E[3] quer escrever
L[2] quer ler
L[1] terminou de ler
L[1] quer ler
E[1] escrevendo
E[1] terminou de escrever
E[2] escrevendo
E[2] terminou de escrever
E[3] escrevendo
E[3] terminou de escrever
L[3] lendo
L[2] lendo
L[1] lendo
E[1] quer escrever
E[2] quer escrever
E[3] quer escrever
L[3] terminou de ler
L[3] quer ler
L[2] terminou de ler
L[2] quer ler
L[1] terminou de ler
L[1] quer ler
E[1] escrevendo
E[2] escrevendo
E[2] terminou de escrever
E[3] escrevendo
E[3] terminou de escrever
E[1] terminou de escrever
L[3] lendo
L[2] lendo
L[1] lendo
E[2] quer escrever
E[3] quer escrever
L[1] terminou de ler
L[1] quer ler
L[2] terminou de ler
L[2] quer ler
L[3] terminou de ler
L[3] quer ler
E[2] escrevendo
E[2] terminou de escrever
E[3] escrevendo
E[3] terminou de escrever
E[1] quer escrever
L[1] lendo
E[3] quer escrever
E[2] quer escrever
L[1] terminou de ler
L[1] quer ler
E[1] escrevendo
E[1] terminou de escrever
E[3] escrevendo
E[3] terminou de escrever
E[2] escrevendo
E[2] terminou de escrever
L[3] lendo
L[2] lendo
L[1] lendo



Threads leitoras:   2
Threads escritoras: 4


L[1] quer ler
E[1] quer escrever
E[1] escrevendo
E[1] terminou de escrever
L[1] lendo
L[2] quer ler
L[2] lendo
E[4] quer escrever
E[3] quer escrever
E[2] quer escrever
E[1] quer escrever
L[1] terminou de ler
L[1] quer ler
L[2] terminou de ler
L[2] quer ler
E[4] escrevendo
E[4] terminou de escrever
E[3] escrevendo
E[3] terminou de escrever
E[2] escrevendo
E[2] terminou de escrever
E[1] escrevendo
E[1] terminou de escrever
L[1] lendo
L[2] lendo
E[4] quer escrever
E[3] quer escrever
E[2] quer escrever
E[1] quer escrever
L[1] terminou de ler
L[1] quer ler
L[2] terminou de ler
L[2] quer ler
E[4] escrevendo
E[4] terminou de escrever
E[3] escrevendo
E[3] terminou de escrever
E[2] escrevendo
E[2] terminou de escrever
E[1] escrevendo
E[1] terminou de escrever
L[1] lendo
L[2] lendo
E[4] quer escrever
E[3] quer escrever
E[2] quer escrever
E[1] quer escrever
L[1] terminou de ler
L[1] quer ler
L[2] terminou de ler
L[2] quer ler
E[4] escrevendo
E[4] terminou de escrever
E[3] escrevendo
E[3] terminou de escrever
E[2] escrevendo
E[2] terminou de escrever
E[1] escrevendo
E[1] terminou de escrever
L[1] lendo
L[2] lendo
E[4] quer escrever
E[3] quer escrever
E[2] quer escrever
E[1] quer escrever
L[2] terminou de ler
L[2] quer ler
L[1] terminou de ler
L[1] quer ler
E[4] escrevendo
E[4] terminou de escrever
E[3] escrevendo
E[3] terminou de escrever
E[2] escrevendo
E[2] terminou de escrever
E[1] escrevendo
E[1] terminou de escrever
L[2] lendo
L[1] lendo
^AE[4] quer escrever
E[3] quer escrever
E[2] quer escrever
L[1] terminou de ler
L[1] quer ler
E[1] quer escrever
L[2] terminou de ler
L[2] quer ler
E[4] escrevendo
E[4] terminou de escrever
E[3] escrevendo
E[3] terminou de escrever
E[2] escrevendo
E[2] terminou de escrever
E[1] escrevendo
E[1] terminou de escrever
L[1] lendo
L[2] lendo


