#include <stdio.h>
#include <cstdlib>


typedef struct noA{
    char info;
    struct noA *esq;
    struct noA *dir;
} TNoA;

TNoA *criaNo(char ch) {
    TNoA *novo;
    novo = (TNoA *) malloc(sizeof(TNoA));
    novo->info = ch;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}



//pré-fixado pré em ordem
//Préfixo faz a leitura da raiz antes de fazer a leitura dos filhos
void prefixa(TNoA *raiz) {
    if (raiz != NULL) {
        if(raiz->esq == NULL && raiz->dir == NULL){ //Pegar as folhas
            printf("%c", raiz->info);
        }
        prefixa(raiz->esq);
        prefixa(raiz->dir);
    }
}

//Central em Ordem
//Infixa faz a leitura do filho esquerdo, depois da raiz e depois do filho direito
void infixa(TNoA *raiz) {
    if (raiz != NULL) {
        infixa(raiz->esq);
        printf("%c", raiz->info);
        infixa(raiz->dir);
    }
}


//pós fixa faz a leitura dos filhos antes de fazer a leitura da raiz
void posfixa(TNoA *raiz) {
    if (raiz != NULL) {
        posfixa(raiz->esq);
        posfixa(raiz->dir);
        printf("%c", raiz->info);
    }
}


int main(void) { 

    TNoA *raiz;
    raiz = criaNo('A');
    raiz->esq = criaNo('B');
    raiz->dir = criaNo('C');
    raiz->dir->esq = criaNo('D');
    raiz->dir->dir = criaNo('E');

    prefixa(raiz);

};