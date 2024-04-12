//
// Created by thugs on 12/04/2024.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int valor;
    struct node *prox;
} NODE;


void insere_meio(int val, NODE **ini){

    NODE  *novo;
    NODE *aux = *ini;
    NODE *ant = *ini;

    novo = (NODE * )malloc(sizeof(NODE)); //Alocar uma nova posição na lista

    novo->valor = val;
    novo->prox = NULL;


    //Caso a lista for vazia, insere na primeira posição
    if(*ini == NULL){
        *ini = novo;

    }else{

        //Insere na frente do valor, caso for menor ou igual
        if( novo->valor <=  aux->valor ){
            novo->prox = *ini;
            *ini = novo;
        }else{

            //Inserir no meio ou no fim
            //Sempre que for percorrer o vetor, tem que comparar o aux para ver se ele n é o último
            while( aux != NULL && aux->valor < novo->valor ){

                ant = aux;
                aux = aux->prox;
            }

            //Inserir na ultima posicao
            if(aux == NULL){
                ant->prox = novo;

            }else{



            }

        }

    }

}



int main(){

    NODE * list;
    list = NULL; // Inicializando a lista



    return 0;
}