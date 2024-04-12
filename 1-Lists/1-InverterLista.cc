#include <stdio.h>

#define t 3
typedef struct pessoa{
    int numero;
    char nome[t];
} PESSOA;


void escreve( PESSOA *p, int tamanho, int posicao ){

    if (posicao == tamanho){
        return;
    }else{
        printf("%d %s\n" , p[posicao].numero, p[posicao].nome);
        escreve(p, t, (posicao + 1) );
    }
}

int  main(void){

    PESSOA pessoas[t];
    PESSOA p;

    for(int i = 0; i < t; i++){
        printf("Digite o nome da pessoa: ");
        scanf("%s", pessoas[i].nome); //Não é necessário o &. O array de char é o próprio endereço de memória
        printf("Digite o numero da pessoa: ");
        scanf("%d", &pessoas[i].numero);
    }

    //inverter Vetor
    int i, j;
    for (i = 0, j = (t-1); i < j; i++, j--) {
        p = pessoas[i];
        pessoas[i] = pessoas[j];
        pessoas[j] = p;
    }

    escreve(pessoas, t, 0);


}