//feito por Luiz P. Kakuichi e Gabriel V. Almeida

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo{
    char carc;
    struct nodo *prox;
    struct nodo *ant;
}NODO;

typedef struct header{
    int quant;
    NODO *comeco;
    NODO *fim;
}HEADER;

void conv_str2list(char vet[20], HEADER *cont){
    int i = 0;
    NODO *new = cont->comeco;
    NODO *aux = cont->comeco;
    NODO *ant = cont->comeco;
    
    while(i < strlen(vet)){
        new = (NODO*) malloc (sizeof(NODO)); // esta aqui dentro pois tem que alocar toda vez um novo espaço para  o nodo
        new->carc = vet[i];
        new->prox = NULL;
        new->ant = NULL;

        if (aux == NULL){
            aux = new;
            cont->comeco = aux;
        }
        else{
            aux->prox = new;
            new->ant = aux;
        }
        i++;

    }
    cont->quant = i;
    cont->fim = new;
    
} 

void ver_list(NODO *ini){
    NODO *aux = ini;
    NODO *fim = NULL;
    while(aux->prox != NULL){
        aux = aux->prox;
    }
    fim = aux;
    aux = ini;

    while(aux != fim && aux->prox != NULL){
        if(aux->carc != fim->carc){
            printf("Não é palindromo...");
            return;
        }
        else{

        }
        aux = aux->prox;
        fim = fim->ant;
    }
    printf("É palindromo...");
}

int main (){
    NODO *aux1;
    HEADER *cont = NULL;
    char vet[20];

    cont = (HEADER*) malloc (sizeof(HEADER));
    cont->comeco = NULL;
    printf("Insira a sequência de caractérs: \n");
    scanf("%s", vet);

    conv_str2list(vet, cont);

    aux1 = cont->comeco;

    while(aux1->prox != NULL){
        printf("%c", aux1->carc);
        aux1 = aux1->prox;
    }
    ver_list(cont->comeco);
    printf("\n %d elementos na lista,\n %p / inicio \n %p / fim", cont->quant, cont->comeco, cont->fim);

}