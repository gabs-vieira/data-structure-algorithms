// Created by gabriel on 15/03/24.
//
#include <stdio.h>
#define tamanho_vetor 9
//Métodos

void ver_lista_cartas( int *cartas, int posicao){
    if ( tamanho_vetor == posicao ) return;

    printf("%d\n" , cartas[posicao]);
    ver_lista_cartas( cartas, (posicao + 1) );
}

void ver_lista_cartas_invertida(int *cartas, int posicao){

    if ( posicao < 0 ) return;

    printf("%d\n" , cartas[posicao]);
    ver_lista_cartas_invertida( cartas, (posicao - 1) );

}

void recebe_carta(int carta, int posicao, int *cartas) {

    if (posicao == tamanho_vetor) {

        return;
    }
    cartas[posicao] = carta;
    //"Se a minha posição atual for menor que a anterior, então troca"
    for (int i = posicao; i > 0 && cartas[i] < cartas[i - 1]; i--) {
        int temp = cartas[i];
        cartas[i] = cartas[i - 1];
        cartas[i - 1] = temp;
    }
}


int menu(){
    printf("1 - Inserir cartas\n");
    printf("2 - Ver lista de cartas\n");
    printf("3 - Ver lista de cartas inversamente\n");
    printf("4 - Sair\n");

    int op;
    printf("Selecione uma opção: ");
    scanf("%d", &op);
    return op;
}

int main(){
    int cartas[tamanho_vetor], carta;

    int opcao, cartas_inseridas = 0;

    do {
        opcao = menu();

        switch (opcao) {
            case 1:
                if( cartas_inseridas == 1){
                    printf("Voce ja inseriu as cartas\n");
                    printf("\n");
                    break;
                }else{
                    for (int i = 0; i < tamanho_vetor; i++) {
                        printf("Digite a carta (1 a 13): ");
                        scanf("%d", &carta);
                        if (carta < 1 || carta > 13) {
                            printf("Digite um numero entre 1 e 13\n");
                            i--;
                            continue;
                        } else {
                            recebe_carta(carta, i, cartas);
                        }
                    }
                    cartas_inseridas = 1;
                }
                break;
            case 2:
                printf("\nLista das cartas: \n");
                ver_lista_cartas(cartas, 0);
                printf("\n");
                break;
            case 3:
                printf("\nLista das cartas invertidas: \n");
                ver_lista_cartas_invertida(cartas, (tamanho_vetor-1));
                printf("\n");
                break;
            case 4:
                break;
            default:
                printf("Opcao invalida\n");
                break;
        }

    } while (opcao != 4);

    return 0;
}


/**
 * Considere usar recursividade na implementação (ao menos em ver_lista_cartas().
 *ver_lista_cartas
 *  - implementar a operação ver_lista_cartas(...), que exiba a lista de cartas armazenada (exibir os valores das cartas em ordem crescente).
 *  implementar a operação ver_lista_cartas_invertida(...), que exiba a lista de cartas (exibir os valores das cartas)  em ordem decrescente de valores.
 *
 *  A ordenação deve ser em ordem crescente de valores, ou seja, a cada inserção de uma nova carta, ela deve ser colocada na sua posição correta na lista. Pode haver valores repetidos na lista, cada baralho tem 4 cartas de mesmo valor (considere ou não separação por naipes). O valor das cartas deve estar entre 1 e 13.
 */

