//
// Created by thugs on 12/04/2024.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int valor;
    struct node *prox;
} NODE;

//Lista global
NODE *list = NULL;


void insere_meio(int valor){
    NODE *novo, *aux = list, *ant = list;
    novo = (NODE *)malloc(sizeof(NODE));
    novo->valor = valor;
    novo->prox = NULL;

    if(list == NULL){
        list = novo;
    }else{
        if(novo->valor <= aux->valor){
            novo->prox = list;
            list = novo;
        }else{
            while(aux != NULL && aux->valor < novo->valor){
                ant = aux;
                aux = aux->prox;
            }
            if(aux == NULL){
                ant->prox = novo;
            }else{
                ant->prox = novo;
                novo->prox = aux;
            }
        }
    }
}

void contar_repetidos(){
    NODE *aux = list;
    int val = aux->valor, count = 0;

    for (int i = 0; aux != NULL; i++){
        if(val == aux->valor){
            count++;
        }else{
            printf("\n O numero %d aparece %d vezes. ", val, count);
            val = aux->valor;
            count = 1;
        }
        aux = aux->prox;
    }

    // Verificar e imprimir o último número
    if (count > 0) {
        printf("\n O numero %d aparece %d vezes. ", val, count);
    }
}

void remover_repetidos() {
    NODE *atual = list;
    NODE *anterior = NULL;

    while (atual != NULL) {
        int valor = atual->valor;
        NODE *verificador = atual->prox;
        NODE *ant_verificador = atual;

        while (verificador != NULL) {
            if (verificador->valor == valor) {
                ant_verificador->prox = verificador->prox;
                NODE *temp = verificador;
                verificador = verificador->prox;
                free(temp);
            } else {
                ant_verificador = verificador;
                verificador = verificador->prox;
            }
        }

        anterior = atual;
        atual = atual->prox;
    }
}

void escreve(){
    NODE *aux = list;
    printf("\nLista: \n");
    while(aux != NULL){
        printf("%d (%d) \n",aux->valor,aux);
        aux = aux->prox;
    }
    printf("\n----------------------------*");
}


int main(){

    insere_meio(40);
    insere_meio(40);
    insere_meio(50);
    insere_meio(10);
    insere_meio(20);
    insere_meio(20);
    insere_meio(30);
    insere_meio(30);

    escreve();
    contar_repetidos();
    remover_repetidos();
    printf("\n");
    contar_repetidos();
    escreve();

    return 0;
}