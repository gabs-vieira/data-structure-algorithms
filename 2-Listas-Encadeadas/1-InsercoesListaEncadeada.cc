#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int info;
    struct node *next;
} ELEMENTO;

ELEMENTO *inicio = NULL;

void inserePrimeiro(int valor){
    ELEMENTO *novo;
    novo = (ELEMENTO *) malloc(sizeof(ELEMENTO));
    novo->info = valor;
    novo->next = NULL;

    if(inicio == NULL){
        inicio = novo;
    }else{
        novo->next = inicio;
        inicio = novo;
    }
}


void escrevaLista(){
    ELEMENTO *aux = inicio;
    while(aux != NULL){
        printf("%d %p\n", aux->info, aux);
        aux = aux->next;
    }

}

void insereUltimo(int valor){
    ELEMENTO *novo, *aux;
    novo = (ELEMENTO *) malloc(sizeof(ELEMENTO));
    novo->info = valor;
    novo->next = NULL;

    if(inicio == NULL){
        inicio = novo; //Inserção do primeiro elemento
    }else{
        //Percorrer a lista até o último elemento
        aux = inicio;
        while(aux->next != NULL){
            aux = aux->next;
        }
        aux->next = novo;
    }
}


void insereMeio(int valor){
    ELEMENTO *novo, *aux=inicio, *anterior=inicio;
    novo = (ELEMENTO *) malloc(sizeof(ELEMENTO));
    novo->info = valor;
    novo->next = NULL;

    //Percorrer a lista até encontrar a posição de inserção
    while (aux != NULL && aux->info < novo->info){
        //Procurar a posição de inserção
        // Encontra o valor anterior ao novo
        //aux != NULL -> Se a lista não estiver vazia
        // aux->info < novo->info -> Se o valor do elemento atual é menor que o valor do novo elemento
        anterior = aux;
        aux = aux->next;
    }

    anterior->next = novo;
    novo->next = aux;
}

void insereOrdenado( int valor){
    ELEMENTO *novo, *aux, *anterior;
    novo = (ELEMENTO *) malloc(sizeof(ELEMENTO));
    novo->info = valor;
    novo->next = NULL;

    if(inicio == NULL){
        inicio = novo; //Inserção do primeiro elemento
    }else{
        aux = inicio;
        anterior = NULL;

        //Percorrer a lista até encontrar a posição de inserção
        while(aux != NULL && aux->info < valor){
            anterior = aux;
            aux = aux->next;
        }

        if(anterior == NULL){
            //Se anterior for NULL, então o novo elemento é o primeiro
            novo->next = inicio;
            inicio = novo;
        }else{
            //Se anterior não for NULL, então o novo elemento é inserido entre anterior e aux
            anterior->next = novo;
            novo->next = aux;
        }
    }
}

int main(){

    insereOrdenado(60);
    insereOrdenado(2);
    insereOrdenado(33);
    insereOrdenado(100);
    insereOrdenado(22);
    insereOrdenado(7);
    insereOrdenado(2);

    escrevaLista();
    return 0;
}
