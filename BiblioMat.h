#include<stdlib.h>
#include<stdio.h>

typedef struct tipo_elemento{
    int valor;
    int linha;
    struct tipo_elemento *proximo;
}tipo_elemento;

typedef struct tipo_linha{
    int ID_Coluna;
    struct tipo_linha *proximo;
    struct tipo_elemento *inicio;
}tipo_linha;

typedef struct MatEsp{
    int qtd_linhas;
    int qtd_colunas;
    struct tipo_linha *inicio;
}MatEsp;

MatEsp* criarMatEsp(){
    MatEsp *me = (MatEsp*)calloc(sizeof(MatEsp), 1);

    me->qtd_linhas = 0;
    me->qtd_colunas = 0;

    me->inicio = NULL;

    return me;
}

void inserir(MatEsp *me, int l, int c, int valor){
    if(me==NULL || valor==0)
        return;

    if(l>=me->qtd_linhas)
        me->qtd_linhas = l+1;
    if(c>=me->qtd_colunas)
        me->qtd_colunas = c+1;

    tipo_linha *colunaAtual = me->inicio;
    tipo_linha *anterior = NULL;

    while(colunaAtual!=NULL && colunaAtual->ID_Coluna<c){
        anterior = colunaAtual;
        colunaAtual = colunaAtual->proximo;
    }

    if(colunaAtual==NULL || colunaAtual->ID_Coluna != c){
        tipo_linha *novaColuna = (tipo_linha*)calloc(sizeof(tipo_linha), 1); 
        
        novaColuna->ID_Coluna = c;
        novaColuna->proximo = colunaAtual;
        novaColuna->inicio = NULL;

        if(anterior == NULL)
            me->inicio = novaColuna;
        else
            anterior->proximo = novaColuna;

        colunaAtual = novaColuna;
    }

    tipo_elemento *aux = colunaAtual->inicio;
    tipo_elemento *previous = NULL;

    while(aux!=NULL && aux->linha<l){
        previous = aux;
        aux = aux->proximo;
    }
    
    if(aux==NULL || aux->linha!=l){
        tipo_elemento *e = (tipo_elemento*)calloc(sizeof(tipo_elemento), 1);

        e->linha = l;
        e->valor = valor;
        e->proximo = aux;

        if(previous==NULL)
            colunaAtual->inicio = e;
        else 
            previous->proximo = e;
    }else
        aux->valor = valor;
}

void procurarElemento(MatEsp *me, int key){
    if(me==NULL || key==0)
        return;
    
    tipo_linha *atual = me->inicio;
    int encontrado = 0;

    while(atual != NULL){
        tipo_elemento *aux = atual->inicio;

        while(aux!=NULL){
            if(aux->valor == key){
                printf("\nElemento %d encontrado na linha %d e coluna %d\n", key ,aux->linha, atual->ID_Coluna);
                encontrado = 1;
            }
            aux = aux->proximo;
        }
        atual = atual->proximo;
    }
    if(!encontrado)
        printf("\nElemento %d nao encontrado\n", key);
}

int consultaElemento(MatEsp *me, int l, int c){
    if(me == NULL)
        return 0;

    tipo_linha *atual = me->inicio;

    while(atual != NULL){
        if(atual->ID_Coluna==c){
            tipo_elemento *aux = atual->inicio;

            while(aux!=NULL && aux->linha<l)
                aux = aux->proximo;

            if(aux != NULL && aux->linha==l)
                return aux->valor;
        }
        atual = atual->proximo;
    }
    return 0;
}

void imprimirMat(MatEsp *me){
    if(me == NULL)
        return;
        
    for(int i=0; i<me->qtd_linhas; i++){
        for(int j=0; j<me->qtd_colunas; j++){
            int valor = consultaElemento(me, i, j);
            printf("%3d  ", valor);
        }
        printf("\n");
    }
}

MatEsp* somaMatriz(MatEsp *m1, MatEsp *m2){
    if(m1 == NULL)
        return m2;
    else if(m2 == NULL)
        return m1;
    else if(m1 == NULL && m2 ==NULL)
        return NULL;
    
    MatEsp *resultado = criarMatEsp();

    if(m1->qtd_linhas == m2->qtd_linhas && m1->qtd_colunas == m2->qtd_colunas){
        for(int i=0; i<m1->qtd_linhas; i++){
            for(int j=0; j<m1->qtd_colunas; j++){
                int v1 = consultaElemento(m1, i, j);
                int v2 = consultaElemento(m2, i, j);
                int soma = v1 + v2;
                
                if(soma != 0)
                    inserir(resultado, i, j, soma);
            }
        }
    }else 
        return NULL;

    return resultado;
}

MatEsp* criaTransposta(MatEsp *me){
    if(me == NULL)  
        return NULL;

    MatEsp *transposta = criarMatEsp();

    for(int i=0; i<me->qtd_linhas; i++){
        for(int j=0; j<me->qtd_colunas; j++){
            int valor = consultaElemento(me, i, j);
            
            if(valor != 0)
                inserir(transposta, j, i, valor);
        }
    }
    return transposta;
}

MatEsp* multiplicaMat(MatEsp *m1, MatEsp *m2){
    if(m1 == NULL)
        return m2;
    else if(m2 == NULL)
        return m1;
    else if(m1 == NULL && m2 ==NULL)
        return NULL;

    if(m1->qtd_colunas!=m2->qtd_linhas)
        return NULL;
    
    MatEsp *resultado = criarMatEsp();

    int soma;
    int i, j, k;
    
    for(i=0; i<m1->qtd_linhas; i++){
        for(j=0; j<m2->qtd_colunas; j++){
            soma=0;
            for(k=0; k<m2->qtd_linhas; k++)
                soma += consultaElemento(m1, i, k)*consultaElemento(m2, k, j);
            
            if(soma!=0)
                inserir(resultado, i, j, soma);
        }
    }

    return resultado;
}

int apagaMatriz(MatEsp *me){
    if(me!=NULL){
        tipo_linha *auxLinha = me->inicio;
        tipo_linha *liberarLinha = NULL;

        while(auxLinha!=NULL){
            tipo_elemento *auxElem = auxLinha->inicio;
            tipo_elemento *liberarElem = NULL;

            while(auxElem!=NULL){
                liberarElem = auxElem;
                auxElem = auxElem->proximo;
                free(liberarElem);
            }

            liberarLinha = auxLinha;
            auxLinha = auxLinha->proximo;
            free(liberarLinha);
        }
        free(me);

        return 1;
    }
    return 0;
}