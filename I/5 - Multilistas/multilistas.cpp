#include <stido.h>
#include <stdlib.h>


struct Lista1{
    int valor;
    struct Lista1 *prox;
};

struct Lista2{
    int letra;
    struct Lista2 *prox;
    struct Lista1 *inicio;
};




void insereLista1( char c, int n  ){

    struct Lista2 *aux2 = inicio1;
    struct Lista1 *pnovo.

    while ( aux2 != NULL && aux2->letra != c ) aux2 = aux2->prox;

    if (aux2==NULL)
    {
        printf("\nletra não está na lista 2\n\n");
        return;
    }

    pnovo = (struct Lista1*)malloc(sizeof(struct Lista1));
    pnovo->valor=n;
    pnovo->prox = aux2->inicio;
    aux2->inicio = pnovo;

}


void insereLista2( char c ){

    struct Lista2 *pnovo;

    pnovo = (struct Lista2*)malloc(sizeof(struct Lista2));

    pnovo->letra = c;
    pnovo->prox = NULL;

}


void escreve(){
    struct Lista2 *aux2=inicio1;

    printf("\nLista 2:\n");
    while (aux2!=NULL)
    {
        printf("%c", aux2->letra);
    
        if( aux2->inicio != NULL ){
            aux1=aux2->inicio;

            while ( aux1 != NULL)
            {
                printf("%d", aux1->valor);
                aux1=aux1->prox;
            }
            

        }
    }

    printf("\n\n");
}



inicio1 = fim1 = NULL;

int main(){



}