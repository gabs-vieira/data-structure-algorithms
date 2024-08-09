//
// Created by gabriel on 12/04/24.
//
//a) O texto vai ser armazenado em uma lista duplamente encadeada, na qual cada nodo vai conter um caractere.
//- se for palíndrome, exibe uma mensagem dizendo "é palíndrome";
//- se não for palíndrome, o programa/função gera a palíndrome do texto informado, escrevendo-a na tela.
//b) Defina um header (cabeçalho) para a lista que armazena a quantidade de caracteres do texto (e opcionalmente) a quantidade de palavras do texto. Considere outras operações que poderiam ser executadas sobre o texto para definir o conteúdo do header.
//OBS: pode ser desenvolvido em dupla, nesse caso inscrever-se no grupo Listas Duplas (através da aba Pessoas)


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    char valor;
    struct node *prox, *ant;
} NODE;

//Lista global
NODE *inicio = NULL;
int total = 0;


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

void ehPalindromo(){
    NODE *aux = inicio;
    NODE *aux2 = inicio;
    int palindromo = 1;

    while(aux2->prox != NULL){
        aux2 = aux2->prox;
    }

    while(aux != NULL){
        if(aux->valor != aux2->valor){
            palindromo = 0;
            break;
        }
        aux = aux->prox;
        aux2 = aux2->ant;
    }

    if(palindromo){
        printf("\nÉ palíndromo\n");
    }else{
        printf("\nNão é palíndromo\n");
        NODE *aux = inicio;
        while(aux != NULL){
            insereUltimo(aux->valor);
            aux = aux->prox;
        }
        escreva();
    }

}


int main(){
    char texto[100];
    printf("Digite o texto: ");
    fgets(texto, 100, stdin);

    texto[strcspn(texto, "\n")] = '\0'; // Remove o \n do fgets

    for (int i = 0; i < strlen(texto); i++){
        insereUltimo(texto[i]);
    }

    ehPalindromo();

    return 0;
}