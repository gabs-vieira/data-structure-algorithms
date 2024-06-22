#include <stdio.h>
#include <stdlib.h>

typedef struct product{
    char c[20];
    int quantidade;
    struct product *esq;
    struct product *dir;
}PRODUCT;


//Vetor de ponteiros para as palavras 
typedef struct nodo{
    char c;
    struct nodo *prox;
    PRODUCT *seed;
}NODO;




NODO verificaKeyCatalogo(char key, NODO *ini){
    //Verifica se a chave já existe no catálogo, caso não tiver insere a chave em ordem alfabética
    NODO *aux = (NODO *) malloc(sizeof(NODO));
    NODO *auxIni, *anterior;
    aux->c = key;
    aux->prox = NULL;
    aux->seed = NULL;

    //Aloca em primeiro
    if(ini == NULL){
        ini = aux; //Insere no início

    }else{
        auxIni = ini;
        anterior = NULL;
        //Percorre a lista até encontrar a posição de inserção
        while(auxIni->prox != NULL && auxIni->c < key){
            anterior = auxIni;
            auxIni = auxIni->prox;
        }

        
        if(anterior == NULL){
            //Se o anterior for NULL, então o elemento é o primeiro
            aux->prox = ini;
            ini = aux;

        }else{
            //Se não, insere o elemento na posição correta (entre o anterior e o auxIni)
            aux->prox = anterior->prox;
            anterior->prox = aux;
        }
    }


}


void addWord(NODO **ini, char[20] key){

    verificaKeyCatalogo[ tolower(key[0]) , *ini]

}


int main(){
    //Inicialização catálogo
    NODO *ini;
    ini = null;


    addWord(&ini,"Palmeira");
}