#include <stdio.h>

typedef struct pessoa{
    int numero;
    char nome[10];
} PESSOA;

void main(){

    PESSOA pessoas[10];

    for(int i = 0; i < 10; i++){
        printf("Digite o nome da pessoa %d: ", i+1);
        scanf("%s", pessoas[i].nome); //Não é necessário o &. O array de char é o próprio endereço de memória
        printf("Digite o numero da pessoa %d: ", i+1);
        scanf("%d", &pessoas[i].numero);
    }



}