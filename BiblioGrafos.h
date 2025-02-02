#include<stdlib.h>
#include<stdio.h>
#include "BiblioMat.h"

typedef struct tipo_adjacente{
    int id_Adj;
    struct tipo_adjacente *proximo;
}tipo_adjacente;

typedef struct tipo_vertice{
    int idv;
    struct tipo_vertice *proximo;
    struct tipo_adjacente *inicio;
}tipo_vertice;

typedef struct Grafo{
    int qtd_vertices;
    struct tipo_vertice *inicio;
}Grafo;

Grafo* criarGrafo(){
    Grafo *me = (Grafo*)calloc(sizeof(Grafo), 1);

    me->qtd_vertices = 0;

    me->inicio = NULL;

    return me;
}

void inserirVertice(Grafo *me, int id){
    if(me==NULL)
        return;

    tipo_vertice *atual = me->inicio;
    tipo_vertice *anterior = NULL;

    while(atual!=NULL && atual->idv<id){
        anterior = atual;
        atual = atual->proximo;
    }

    if(atual!=NULL && atual->idv == id){
        printf("\nVertice %d ja existe", id);
        return;
    }

    if(atual==NULL || atual->idv!=id){
        tipo_vertice *novoV = (tipo_vertice*)calloc(sizeof(tipo_vertice), 1); 
        
        novoV->idv = id;
        novoV->proximo = atual;
        novoV->inicio = NULL;

        if(anterior == NULL)
            me->inicio = novoV;
        else
            anterior->proximo = novoV;

        atual = novoV;
    }

    me->qtd_vertices++;
    printf("Vertice %d inserido com sucesso\n", id);
}

void inserirAresta(Grafo *me, int vAnt, int vProx){
    if(me==NULL)
        return;
    
    if(vAnt == vProx){
        printf("Vertice de origem igual ao vertice de destino\n");
        return;
    }

    tipo_vertice *atual = me->inicio;
    while(atual!=NULL && atual->idv!=vAnt)
        atual = atual->proximo;

    if(atual == NULL){
        printf("Vertice %d nao encontrado\n", vAnt);
        return;
    }

    tipo_vertice *proximo = me->inicio;
    while(proximo!=NULL && proximo->idv!=vProx)
        proximo = proximo->proximo;

    if(proximo == NULL){
        printf("Vertice %d nao encontrado\n", vProx);
        return;
    }

    tipo_adjacente *eAtual = atual->inicio;
    while (eAtual != NULL) {
        if (eAtual->id_Adj == vProx) {
            printf("Aresta de %d para %d ja existe\n", vAnt, vProx);
            return;
        }
        eAtual = eAtual->proximo;
    }

    tipo_adjacente *novaAresta = (tipo_adjacente*) calloc(1, sizeof(tipo_adjacente));
    novaAresta->id_Adj = vProx;
    novaAresta->proximo = atual->inicio;
    atual->inicio = novaAresta;

    tipo_vertice *atual2 = me->inicio;
    while(atual2!=NULL && atual2->idv!=vProx)
        atual2 = atual2->proximo;

    tipo_adjacente *novaAresta2 = (tipo_adjacente*) calloc(1, sizeof(tipo_adjacente));
    novaAresta2->id_Adj = vAnt;
    novaAresta2->proximo = atual2->inicio;
    atual2->inicio = novaAresta2;


    printf("Aresta de %d para %d inserida com sucesso\n", vAnt, vProx);
}

void imprimirGrafo(Grafo *me){
    if(me == NULL || me->inicio==NULL){
        printf("Grafo Vazio\n");
        return;
    }
    tipo_vertice *v = me->inicio;

    printf("\n");
    while(v!=NULL){
        printf("%d ", v->idv);

        tipo_adjacente *e = v->inicio;
        while(e!=NULL){
            printf("-> %d ", e->id_Adj);
            e = e->proximo;
        }
        printf("\n");
        v = v->proximo;
    }    
}

void removerAresta(Grafo *gf, int vAnt, int vProx){
    if(gf==NULL || gf->inicio==NULL){
        printf("\nGrafo Vazio");
        return;
    }

    tipo_vertice *vAtual = gf->inicio;
    while(vAtual!=NULL && vAtual->idv!=vAnt)
        vAtual = vAtual->proximo;
    
    if(vAtual==NULL){
        printf("Vertice %d nao encontrado\n", vAnt);
        return;
    }

    tipo_adjacente *eAtual = vAtual->inicio;
    tipo_adjacente *eAnterior = NULL;
    while(eAtual!=NULL && eAtual->id_Adj!=vProx){
        eAnterior = eAtual;
        eAtual = eAtual->proximo;
    }

    if(eAtual==NULL){
        printf("Aresta de %d para %d nao encontrada\n", vAnt, vProx);
        return;
    }

    if(eAnterior==NULL)
        vAtual->inicio=eAtual->proximo;
    else
        eAnterior->proximo = eAtual->proximo;

    free(eAtual);
    printf("Aresta de %d para %d removida com sucesso\n", vAnt, vProx);


    tipo_vertice *vAtual2 = gf->inicio;
    while(vAtual2!=NULL && vAtual2->idv!=vProx)
        vAtual2 = vAtual2->proximo;
    
    if(vAtual2==NULL)
        return;

    tipo_adjacente *eAtual2 = vAtual2->inicio;
    tipo_adjacente *eAnterior2 = NULL;
    while(eAtual2!=NULL && eAtual2->id_Adj!=vAnt){
        eAnterior2 = eAtual2;
        eAtual2 = eAtual2->proximo;
    }

    if(eAtual2==NULL)
        return;
    
    if(eAnterior2==NULL)
        vAtual2->inicio=eAtual2->proximo;
    else
        eAnterior2->proximo = eAtual2->proximo;

    free(eAtual2);
    printf("Aresta de %d para %d removida com sucesso\n", vProx, vAnt);
}


void removerVertice(Grafo *gf, int id){
    if(gf == NULL){
        printf("\nGrafo Vazio");
        return;
    }

    tipo_vertice *vAtual = gf->inicio;
    tipo_vertice *vAnterior = NULL;
    while(vAtual!=NULL && vAtual->idv!=id){
        vAnterior = vAtual;
        vAtual = vAtual->proximo;
    }

    if(vAtual==NULL){
        printf("Vertice %d nao existe\n", id);
        return;
    }

    while(vAtual->inicio!=NULL)
        removerAresta(gf, vAtual->idv, vAtual->inicio->id_Adj);
    

    if(vAnterior==NULL)
        gf->inicio = vAtual->proximo;
    else
        vAnterior->proximo = vAtual->proximo;
    
    free(vAtual);

    tipo_vertice *auxV = gf->inicio;
    while(auxV!=NULL){
        tipo_adjacente *auxE = auxV->inicio;

        while(auxE!=NULL){
            if(auxE->id_Adj==id){
                removerAresta(gf, auxV->idv, id);
                break;
            }
            auxE = auxE->proximo;
        }
        auxV = auxV->proximo;
    }

    gf->qtd_vertices--;
    printf("Vertice %d removido com sucesso\n", id);
}

void grauVertice(Grafo *g, int v){
    if(g == NULL){
        printf("\nGrafo Vazio");
        return;
    }

    tipo_vertice *vAtual = g->inicio;
    while(vAtual!=NULL && vAtual->idv!=v)
        vAtual = vAtual->proximo;

    if(vAtual==NULL){
        printf("Vertice %d nao existe\n", v);
        return;
    }

    int grau=0;
    tipo_adjacente *vAdj = vAtual->inicio;
    while(vAdj!=NULL){
        grau++;
        vAdj = vAdj->proximo;
    }

    printf("\nGrau do vertice %d eh %d\n", v, grau);
}

void buscaProf(tipo_vertice *v, int *visitado){
    visitado[v->idv] = 1;
    tipo_adjacente *e = v->inicio;

    while(e!=NULL){
        if(!visitado[e->id_Adj]){
            tipo_vertice *vizinho = v;

            while(vizinho!=NULL && vizinho->idv!=e->id_Adj)
                vizinho = vizinho->proximo;

            if(vizinho!=NULL)
                buscaProf(vizinho, visitado);
        }
        e = e->proximo;
    }
}

int ehConexo(Grafo *gf){
    if(gf==NULL || gf->inicio == NULL){
        printf("Grafo Vazio\n");
        return 0;
    }
    
    int visitado[gf->qtd_vertices];
    for (int i=0; i<gf->qtd_vertices; i++)
        visitado[i] = 0;
    
    buscaProf(gf->inicio, visitado);
    
    tipo_vertice *v = gf->inicio;
    while(v!=NULL){
        if(!visitado[v->idv]){
            printf("\nO grafo nao eh conexo\n");
            return 0;
        }
        v = v->proximo;
    }
    printf("\nO grafo eh conexo\n");
    return 1;
}

void matAdjacencia(Grafo *gf){
    if(gf == NULL){
        printf("\nGrafo Vazio");
        return;
    }

    MatEsp *mat = criarMatEsp();
    mat->qtd_colunas = gf->qtd_vertices;
    mat->qtd_linhas = gf->qtd_vertices;

    tipo_vertice *v = gf->inicio;

    while(v!=NULL){
        tipo_adjacente *adj = v->inicio;

        while(adj!=NULL){
            for(int i=0; i<gf->qtd_vertices; i++){
                if(adj->id_Adj == i){
                    inserir(mat, v->idv, i, 1);
                }
            }

            adj = adj->proximo;
        }
        
        v = v->proximo;
    }

    imprimirMat(mat);
}