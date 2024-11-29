#include<stdlib.h>
#include<stdio.h>
#include "BiblioMat.h"

int main(){
    MatEsp *m1 = criarMatEsp();
    MatEsp *m2 = criarMatEsp();

    //m1
    inserir(m1, 1, 0, 4);
    inserir(m1, 0, 1, 6);
    inserir(m1, 0, 0, 3);
    inserir(m1, 1, 1, 9);
    inserir(m1, 0, 2, 6);
    inserir(m1, 3, 2, 6);
    inserir(m1, 5, 5, 7);
    printf("\n===Matriz Esparsa m1===\n");
    imprimirMat(m1);

    //m2
    inserir(m2, 1, 0, 9);
    inserir(m2, 0, 0, 7);
    inserir(m2, 0, 1, 3);
    inserir(m2, 1, 1, 1);
    inserir(m2, 2, 0, 5);
    inserir(m2, 3, 4, 6);
    inserir(m2, 5, 5, 6);
    printf("\n===Matriz Esparsa m2===\n");
    imprimirMat(m2);

    //soma
    MatEsp *soma = somaMatriz(m1, m2);
    printf("\n===SOMA DE M1 e M2===\n");
    if(soma == NULL)
        printf("Matrizes de ordem diferente nao ocorre soma\n");
    imprimirMat(soma);

    //procura elementos
    printf("\n===PARA M1===");
    procurarElemento(m1, 5);
    procurarElemento(m1, 4);
  
    //tranposta
    printf("\n===M1 TRANSPOSTA===\n");
    MatEsp *m1t = criaTransposta(m1);
    imprimirMat(m1t);
    printf("\n===M2 TRANSPOSTA===\n");
    MatEsp *m2t = criaTransposta(m2);
    imprimirMat(m2t);

    //multiplicacao
    printf("\n===Multiplicacao m1 e m2===\n");
    MatEsp *multiplicacao = multiplicaMat(m1, m2);
    imprimirMat(multiplicacao);

    //apaga matriz
    printf("\n===Apagando Matrizes===\n");
    if(apagaMatriz(m1))
        printf("Matriz m1 apagada com sucesso\n");
    else
        printf("Erro ao apagar a matriz m1");

    if(apagaMatriz(m2))
        printf("Matriz m2 apagada com sucesso\n");
    else
        printf("Erro ao apagar a matriz m2");
        
    return 0;
}