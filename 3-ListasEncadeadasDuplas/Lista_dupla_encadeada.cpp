//
// Created by gabriel on 12/04/24.
//


#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int valor;
    struct node *prox, *ant;
} NODE;

//Lista global
NODE *inicio = NULL;


void inserePrimeiro(int valor){
    NODE *novo = (NODE *)malloc(sizeof(NODE));
    novo->valor = valor;
    novo->prox = NULL;
    novo->ant = NULL;

    if(inicio == NULL){
        inicio = novo;
    }else{
        novo->prox = inicio;
        inicio->ant = novo;
        inicio = novo;
    }
}

void escreva(){
    NODE *aux = inicio;
    printf("\nLista: \n");
    while(aux != NULL){
        printf("%d (%d) \n",aux->valor,aux);
        aux = aux->prox;
    }
    printf("\n----------------------------*");
}

void insereUltimo(int valor){

    NODE *novo, *aux = inicio;

    novo = (NODE *)malloc(sizeof(NODE));

    novo->valor = valor;
    novo->prox = NULL;
    novo->ant = NULL;

    if(inicio == NULL){
        inicio = novo;

    }else{
        while(aux->prox != NULL){
            aux = aux->prox;
        }
            aux->prox = novo;
            novo->ant = aux;
    }
}

void insereMeio(int valor){
    NODE *novo, *aux = inicio, *ant = inicio;

    novo = (NODE *)malloc(sizeof(NODE));
    novo->valor = valor;
    novo->prox = NULL;
    novo->ant = NULL;

    if(inicio == NULL){
        inicio = novo;
    }else{
        if(novo->valor <= aux->valor){
            novo->prox = inicio;
            inicio->ant = novo;
            inicio = novo;
        }else{

            //Serve para percorrer a lista e encontrar o lugar correto para inserir o novo nodo
            while(aux != NULL && aux->valor < novo->valor){
                ant = aux;
                aux = aux->prox;
            }

            //Se o aux for NULL, significa que o novo nodo é o maior da lista, ou seja, a última posição
            if(aux == NULL){
                ant->prox = novo;
                novo->ant = ant;

            }else{
                // Se não, o novo nodo é inserido no meio da lista
                ant->prox = novo; //
                novo->prox = aux;
                novo->ant = ant;
                aux->ant = novo;
            }
        }
    }
}


void removerValor(int val){

    NODE *novo, *aux = inicio;

    if(inicio == NULL) {
        printf("Lista vazia");

    }else{


        //Pegar o nó
        while( aux != NULL && aux->valor != val ){
            aux = aux->prox;
        }

        if(aux == NULL){
            //Lista está vazia
            printf("Lista está vazia\n");
        }else{

            if(inicio->valor == val  ){
                inicio = inicio->prox;
                free(aux);



            }

        }
    }

}


void remover_Valor(int val){

}

int main(){

    insereMeio(10);
    insereMeio(8);
    insereMeio(5);
    insereMeio(9);
    insereMeio(15);
    insereMeio(100);
    insereMeio(25);


    escreva();
    return 0;
}