#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typdef struct{
    int movieId;
    char title[100];
    int releaseYear;
    char url[100];
    int directorId;
} Movie;

typdef struct{
    int directorId;
    char name[100];
} Director;


FILE *openFile(char *filename, char *mode){
    FILE *file = fopen(filename, mode);
    if(file == NULL){
        printf("Erro ao abrir o arquivo %s\n", filename);
        exit(1);
    }
    return file;
}

// Leitura dos arquivos
int readMovies(char *filename, Movie movies[]){
    FILE *file = openFile(filename, "r");

    char line[1000];
    int count = 0;

    fgets(line, sizeof(line), file); //Ignora a primeira linha (cabecalho)

    while (fgets(line, sizeof(line), file)){

        // Com certeza tem um jeito mais inteligente de fazer isso, talvez utilizando regex

        char *token = strtok(line, ";");
        movies[count].movieId = atoi(token);

        token = strtok(line, ";");
        strcpy(movies[count].title, token);

        token = strtok(line, ";");
        movies[count].releaseYear = atoi(token);

        token = strtok(line, ";");
        strcpy(movies[count].url, token);

        token = strtok(line, ";");
        if(token != NULL){
            movies[count].directorId = atoi(token);
        } else {
            movies[count].directorId = -1;
        }

        count++;
    }

    fclose(file);
    return count;

}


int readDirectors(char *filename, Director directors[]){
    FILE *file = openFile(filename, "r");

    char line[1000];
    int count = 0;

    while (fgets(line, sizeof(line), file)){

        char *token = strtok(line, ";");
        directors[count].directorId = atoi(token);

        token = strtok(line, ";");
        strcpy(directors[count].name, token);

        count++;
    }

    fclose(file);
    return count;

}



//Manipulação e exibição 
void displayMovies(Movie movies[], int numMovies){
    printf("Lista de Filmes:\n");
    for(int i = 0; i < numMovies; i++){
        printf("ID: %d | Título: %s | Ano: %d | URL: %s | Diretor ID: %d\n", 
            movies[i].movieID, movies[i].title, movies[i].releaseYear, movies[i].url, movies[i].directorID
        );
    }
    printf("\n");
}

void displayDirectors(Director directors[], int numDirectors){
    printf("Lista de Diretores:\n");
    for(int i = 0; i < numDirectors; i++){
        printf("ID: %d | Nome: %s\n", 
            directors[i].directorId, directors[i].name
        );
    }
    printf("\n");
}


void incompleteMovies(Movie movies[], int numMovies){
    printf("Lista de Filmes com dados Incompletos:\n");
    for(int i = 0; i < numMovies; i++){

        if(movies[i].directorID == -1){
            printf("Filme: %s (ID: %d)\n", movies[i].title, movies[i].movieID );
        }
    }
    printf("\n");
}


void duplicateMovies(Movie movies[], int numMovies){
    printf("Filmes duplicados:\n");
    for(int i = 0; i < numMovies; i++){
        for(int j = i+1; j < numMovies; j++){
            if(strcmp(movies[i].title, movies[j].title) == 0){
                printf("Filme: %s (ID: %d)\n", movies[i].title, movies[i].movieID );
            }
        }
    }
    printf("\n");
}



int main(){

    Movie movies[10000];
    Director directors[10000];

    int numMovies = readMovies("arqMovies.txt", movies);
    int numDirectors = readDirectors("directors.txt", directors);

    if(numMovies > 0 && numDirectors > 0){
        displayMovies(movies, numMovies);
        displayDirectors(directors, numDirectors);

        incompleteMovies(movies, numMovies);
        duplicateMovies(movies, numMovies);
    }

    return 0;
}