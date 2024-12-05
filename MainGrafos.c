#include<stdlib.h>
#include<stdio.h>
#include"BiblioGrafos.h"

int main(){
    Grafo *g = criarGrafo();

    int op=0;

    while(op!=6){
        printf("\nEscolha uma das opcoes: \n");
        printf("1 - Inserir Vertice\n");
        printf("2 - Inserir Aresta\n");
        printf("3 - Visualizar grafo\n");
        printf("4 - Remover Vertice\n");
        printf("5 - Remover Aresta\n");
        printf("6 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &op);

        int n, i;
        int id, ant, prox;

        switch(op){
            case 1:
                printf("\nQuantidade de Vertices que deseja inserir: ");
                scanf("%d", &n);

                for(i=1; i<=n; i++){
                    printf("\nId do vertice %d: ", g->qtd_vertices+1);
                    scanf("%d", &id);

                    inserirVertice(g, id);
                }

                break;
            
            case 2: 
                printf("\nQuantidade de arestas que deseja inserir: ");
                scanf("%d", &n);

                for(i=1; i<=n; i++){
                    printf("\nId do vertice anterior e do proximo respectivamente: ");
                    scanf("%d %d", &ant, &prox);

                    inserirAresta(g, ant, prox);
                }

                break;
            
            case 3:
                imprimirGrafo(g);
                break;
            
            case 4: 
                printf("\nId do vertice que deseja remover: ");
                scanf("%d", &id);

                removerVertice(g, id);

                break;
            
            case 5: 
                printf("\nId do vertice anterior e do proximo respectivamente: ");
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

    return 0;
}