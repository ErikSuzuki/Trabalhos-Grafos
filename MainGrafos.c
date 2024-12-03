#include<stdlib.h>
#include<stdio.h>
#include"BiblioGrafos.h"

int main(){
    Grafo *g = criarGrafo();

    int op=0;

    while(op!=6){
        printf("\nEscolha uma das opcoes: \n");
        printf("1 - Inserir Vertice\n");
        printf("2 - Inserir Arestaz\n");
        printf("3 - Visualizar grafo\n");
        printf("4 - Remover Vertice\n");
        printf("5 - Remover Aresta\n");
        printf("6 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &op);

        int id, ant, prox;

        switch(op){
            case 1:
                printf("Id do vertice: ");
                scanf("%d", &id);

                inserirVertice(g, id);

                break;
            
            case 2: 
                printf("Id do vertice anterior e do proximo respectivamente: ");
                scanf("%d %d", &ant, &prox);

                inserirAresta(g, ant, prox);

                break;
            
            case 3:
                imprimirGrafo(g);
                break;
            
            case 4: 
                printf("Id do vertice que deseja remover: ");
                scanf("%d", &id);

                removerVertice(g, id);

                break;
            
            case 5: 
                printf("Id do vertice anterior e do proximo respectivamente: ");
                scanf("%d %d", &ant, &prox);

                removerAresta(g, ant, prox);

                break;
            
            case 6: 
                printf("Encerrando o Programa\n");
                break;

            default:
                printf("Opcao Invalida!\n");
                break;
        }
    }

   /*inserir_vertice(g, 0);
    inserir_vertice(g, 1);
    inserir_vertice(g, 2);
    inserir_vertice(g, 3);
    inserir_vertice(g, 4);

    inserir_aresta(g, 0, 2);
    inserir_aresta(g, 0, 1);

    inserir_aresta(g, 1, 3);
    inserir_aresta(g, 1, 2);
    inserir_aresta(g, 1, 0);

    inserir_aresta(g, 2, 4);
    inserir_aresta(g, 2, 3);
    inserir_aresta(g, 2, 1);
    inserir_aresta(g, 2, 0);

    inserir_aresta(g, 3, 4);
    inserir_aresta(g, 3, 2);
    inserir_aresta(g, 3, 1);

    inserir_aresta(g, 4, 3);
    inserir_aresta(g, 4, 2);

    imprimirGrafo(g);

    removerAresta(g, 1, 0);

    imprimirGrafo(g);

    removerVertice(g, 2);

    imprimirGrafo(g);*/

    return 0;
}