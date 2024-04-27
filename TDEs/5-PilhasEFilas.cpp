#include <stdio.h>
#include <stdbool.h>



bool ehDigito(char caractere) {
    if (caractere >= '0' && caractere <= '9') {
        return true;
    } else {
        return false;
    }
}

int main(){
    char digitos[100];
    int ultimoLetras = 0;
    int ultimoDigitos = 0;
    char listaFinal[100];
    char letras[100];

    char vetor[100];

    printf("Digite uma sequencia de caracteres: ");
    scanf("%s", vetor);

    int i = 0;
    while (vetor[i] != '\0') {
        if (ehDigito(vetor[i])) {
            digitos[ultimoDigitos] = vetor[i];
            ultimoDigitos++;
        } else {
            letras[ultimoLetras] = vetor[i];
            ultimoLetras++;
        }
        i++;
    }

    int j = ultimoDigitos - 1;
    int z = 0;

    if(ehDigito(vetor[0])){
        for (int i = 0; i <= (ultimoDigitos + ultimoLetras); i++) {
            if (i % 2 == 0) {
                printf("%c", digitos[j]);
                j--;
            } else {
                printf("%c", letras[z]);
                z++;
            }
        }
    } else {
        for (int i = 0; i <= (ultimoDigitos + ultimoLetras); i++) {
            if (i % 2 == 0) {
                printf("%c", letras[z]);
                z++;
            } else {
                printf("%c", digitos[j]);
                j--;
            }
        }
    }


    return 0;
}