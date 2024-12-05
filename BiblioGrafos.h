#include<stdlib.h>
#include<stdio.h>

typedef struct tipo_elemento{
    int id_Adj;
    struct tipo_elemento *proximo;
}tipo_elemento;

typedef struct tipo_vertice{
    int idv;
    struct tipo_vertice *proximo;
    struct tipo_elemento *inicio;
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

    tipo_elemento *eAtual = atual->inicio;
    while (eAtual != NULL) {
        if (eAtual->id_Adj == vProx) {
            printf("Aresta de %d para %d ja existe\n", vAnt, vProx);
            return;
        }
        eAtual = eAtual->proximo;
    }

    tipo_elemento *novaAresta = (tipo_elemento*) calloc(1, sizeof(tipo_elemento));
    novaAresta->id_Adj = vProx;
    novaAresta->proximo = atual->inicio;
    atual->inicio = novaAresta;

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

        tipo_elemento *e = v->inicio;
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

    tipo_elemento *eAtual = vAtual->inicio;
    tipo_elemento *eAnterior = NULL;
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

    tipo_elemento *eAtual2 = vAtual2->inicio;
    tipo_elemento *eAnterior2 = NULL;
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


//rever esse lixo
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
        tipo_elemento *auxE = auxV->inicio;

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