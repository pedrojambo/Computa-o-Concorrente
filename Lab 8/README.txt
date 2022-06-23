O arquivo "lab8.java" contém a apliação referente ao laboratório 8 de computação concorrente. Nele, temos 3 tipos de threads diferentes:

T1: Entra e sai como uma thread "escritora", incrementando o valor da variável x em 1.

T2: Entra e sai como uma thread "leitora", lendo e imprimindo o valor da variável x e informando se o valor é par ou ímpar.

T3: Entra e sai primeiro como uma thread "leitora", lendo e imprimindo o valor da variável x e, depois de um loop "bobo", entra e sai como uma thread "escritora", alterando o valor da variável x pelo seu id.

Testes:

Com 4 threads T1, 3 threads T2 e 3 threads T3, na grande maioria dos testes, o valor da variável x não se eleva muito, ficando entre 1 e 8. Com 5 threads T1, 1 thread T2 e 1 thread T2, verificamos que as threads T1 conseguem elevar bastante o valor de x, incrementando a variável x até valores acima de 20 em alguns testes. Enquanto houver uma thread T3, o valor da variável x sempre voltará a ser 1. 

Características do código:

Temos uma classe S que é a estrutura na qual o recurso compartilhado entre as threads está presente(no caso, a variável x). Temos na estrutura as funções que as threads necessitam para realizar as tarefas propostas. Na classe S, não temos o uso de sentenças "synchronized", visto que a exclusão mútua é garantida pelo monitor LE presente no programa (seguindo o padrão Leitor/Escritor).