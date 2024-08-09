//
// Created by gabriel on 22/03/24.
//

/**
 *
 * Dada uma lista L1, na qual cada nodo armazena um número inteiro, implementada com encadeamento simples, que pode conter números repetidos. Implemente operações (funções, métodos) em C/Java/C++/C#/Python que:
a) verifique se L1 está ordenada ou não (a ordem pode ser crescente ou decrescente);
b) faça uma cópia da lista L1 em uma outra lista L2;
c) faça uma cópia da Lista L1 em uma outra lista L2, eliminando elementos repetidos;
d) inverta L1 colocando o resultado em L2;
e) inverta L1 colocando o resultado na própria L1;
f) gere uma lista L3 que representa a concatenação de L1 e uma outra lista L2;
g) gere uma lista L2 onde cada registro contém dois campos de informação: elem contém um elemento de L1, e count contém quantas vezes este elemento apareceu em L1;
h) assumindo que os elementos da lista L1 são inteiros positivos, forneça os elementos que aparecem o maior e o menor número de vezes (forneça os elementos e o número de vezes correspondente).
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct NODO{
    int info;
    struct NODO *next;
} NODO;




//verifique se L1 está ordenada ou não (a ordem pode ser crescente ou decrescente);
void verificarOrdenacao(NODO **lista) {
    NODO *aux = *lista;
    int crescente = 1, decrescente = 1;
    while (aux->next != NULL) {

        if(aux->info > aux->next->info){
            crescente = 0;
        }

        if(aux->info < aux->next->info){
            decrescente = 0;
        }
    }

    if(crescente == 1 && decrescente == 0) {
        printf("Lista ordenada de forma crescente\n");
    }else if(crescente == 0 && decrescente == 1){
        printf("Lista ordenada de forma decrescente\n");
    }

}

void inserirValor(int val, NODO **lista){
    NODO *novo;
    novo = (NODO *) malloc(sizeof(NODO));
    novo->info = val;
    novo->next = NULL;

    if(*lista == NULL){
        *lista = novo;
    }else{
        novo->next = *lista;
        *lista = novo;
    }
}

int main(){
    //Variaveis
    NODO *L1 = NULL, *L2 = NULL;

    inserirValor(10,&L1);
    inserirValor(5,&L1);
    inserirValor(2,&L1);

    //Testes
    verificarOrdenacao(&L1);

   return 0;
}