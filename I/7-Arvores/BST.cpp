

typedef struct noA{
    char info;
    struct noA *esq;
    struct noA *dir;
} TNoA;

void posOrdem(TNoA* a){
    if (a!= NULL){
        posOrdem(a->esq);
        posOrdem(a->dir);
        printf("%c\n",a->info);
    }
}

void central(TNoA* a){
    if (a!= NULL){
        central(a->esq);
        printf("%c\n",a->info);
        central(a->dir);
    }
}

void preordem(TNoA* a){
    if (a!= NULL){
        printf("%c\n",a->info);
        preordem(a->esq);
        preordem(a->dir);
    }
}


TNoA *criaNo(char ch) {
    TNoA *novo;
    novo = (TNoA *) malloc(sizeof(TNoA));
    novo->info = ch;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

int main(void) {
    TNoA *raiz;
    raiz = criaNo('A');
    raiz->esq = criaNo('B');
    raiz->dir = criaNo('C');
    raiz->dir->esq = criaNo('D');
    raiz->dir->dir = criaNo('E');
};