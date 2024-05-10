#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct nodo{
    char id[6];
    int pou;
    int att;
    struct nodo *prox; //endereço do próximo nodo no qual contém a informação'
}NODO;

typedef struct hash{
    char topic;
    struct hash *prox; //endereço do próximo endereço do hash
    NODO *comeco; //endereço aonde começa a lista o qual pertence aquela categória
}HASH;

void cadastra_aviao(NODO **ini, char id[6]){
    NODO *new, *aux = *ini, *ant = NULL; //new não precisa atribuir o ini. 
    new = (NODO*)malloc(sizeof(NODO));
    strcpy(new->id, id);
    new->prox = NULL; //lembrar de nullar
    if(*ini == NULL){
        *ini = new; //esta atribuindo ao marcador ini o new ou ini agora aponta para o nodo alocado de new;
        return;
    } 
    while (aux != NULL && strcmp(aux->id, new->id) < 0){ //percorre os nodos e compara  strcmp retorna um inteiro se for menor q zero t1 é menor que t2
        ant = aux;
        aux = aux -> prox;
    }
    if (ant == NULL){
        new->prox = *ini;
        aux = aux->prox;
    }
    else if (aux == NULL){ //inserção no fim
        ant -> prox = new;
    }
    else{ //inserção no meio
        ant->prox = new;
        new -> prox = aux;
    }          
}

void conv_id(char id[6]){
    int i;
    for(i = 0; i < 5; i++){
        id[i] = toupper(id[i]);
    }
}

void esc_list(NODO *ini){
    NODO *aux = ini;
    while(aux != NULL){
        printf("Aeronave: %s \n",aux->id);
        aux = aux->prox;
    }
}
int main(){
    char id[6] = "ab123";
    NODO *inicio;
    inicio = NULL;
    printf("Insira o código do a ser cadastrado: ");
    printf("[Lembrando que o código é composto por 2 letras seguido por 3 números]");
    //fflush(stdin);
    //gets(id);
    conv_id(id);
    cadastra_aviao(&inicio,id);
    esc_list(inicio);
}