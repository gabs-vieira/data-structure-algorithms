#include <stdio.h>
#include <stdlib.h>

typedef struct tree{
    char[20] word;
    struct tree *esq;
    struct tree *dir;
}TREE;

typedef struct nodo{
    char c;
    struct nodo *prox;
    TREE *seed;
}NODO;

void addWord(NODO **ini, char[20] key){
    int i;
    NODO *new;
    new = (NODO*)malloc(sizeof(NODO));
    new->c = key[0];
    new->prox = null;
    new->seed = null;
    if(*ini == null){
        *ini = new;
    }
    else{
        for(i = 0; i < )
    }
}

int main(){
    NODO *ini;
    ini = null;
    addWord(&ini,"Palmeira");
}

