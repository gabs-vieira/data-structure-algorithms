#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int info;
    struct node *next;
} ELEMENTO;


void inserePrimeiro(int valor, ELEMENTO **inicio){
    ELEMENTO *novo;
    novo = (ELEMENTO *) malloc(sizeof(ELEMENTO));
    novo->info = valor;
    novo->next = NULL;

    if(*inicio == NULL){
        *inicio = novo;
    }else{
        novo->next = *inicio;
        *inicio = novo;
    }
}

int main(){

    ELEMENTO *inicio;

    inserePrimeiro(20, &inicio);
    return 0;
}
