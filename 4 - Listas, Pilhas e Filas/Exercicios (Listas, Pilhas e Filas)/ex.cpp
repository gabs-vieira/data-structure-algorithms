// Desenvolva uma programa que leia um texto, e escreva as palavras do texto em ordem invertida. 
// Use uma pilha, e considere que os separadores de palavras são espaços em branco (se quiser considere 
// também outros separadores, como : , ; . ! etc)


#include <stdio.h>
#include <string.h>


typedef struct node{
    char palavra[50];
    NODE *prox, *ant;
}NODE;


void empilha(){

}


int main(){

    char frase[1000];
    printf("Informe a frase: ");
    fgets(frase, sizeof(frase), stdin);

    int tamanho = strlen(frase);
    char *token = strtok(frase, " ");



    while (token != NULL)
    {
        printf("\n%s", token);


        // CONTINUAR AQUI --> FAZER A FUNÇAÕ PARA INSERIR/


        token = strtok(NULL, " ");
    }


    return 0;
}