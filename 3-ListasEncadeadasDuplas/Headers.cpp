//
// Created by gabriel on 12/04/24.
//

typedef struct aluno{
    float nota;
    char nome[20];
    struct aluno *prox, *ant;
} ALUNO;

typedef struct header{
    int total;
    float tnotas;
    ALUNO *inicio;
} h;


int main(){

    h.total = 0

    return 0;
}