#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{
    char url[256];
    char title[100];
    int movieId;
    int releaseYear;
    int directorId;
} Movie;

typedef struct{
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

        token = strtok(NULL, ";");
        strcpy(movies[count].title, token);

        token = strtok(NULL, ";");
        movies[count].releaseYear = atoi(token);

        token = strtok(NULL, ";");
        // Esse copy da segfault
        // strcpy(movies[count].url, token);
        if(token != NULL && strlen(token) > 0 ){
            strncpy(movies[count].url, token, sizeof(movies[count].url) - 1);
            movies[count].url[sizeof(movies[count].url) - 1] = '\0'; 
        } else {
            strcpy(movies[count].url, "URL não disponível");
        }

        token = strtok(NULL, ";");
        if(token != NULL && strlen(token) > 0 ){
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
        char *token = strtok(line, ",");
        directors[count].directorId = atoi(token);

        token = strtok(NULL, "\n");
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
            movies[i].movieId, movies[i].title, movies[i].releaseYear, movies[i].url, movies[i].directorId
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
        

        if (strlen(movies[i].title) == 0 || 
            movies[i].releaseYear == 0 || 
            strlen(movies[i].url) == 0 || 
            strcmp(movies[i].url, "URL não disponível") == 0 || 
            movies[i].directorId == -1 || 
            movies[i].directorId == 0) {

            printf("Filme: %s (ID: %d)\n", movies[i].title, movies[i].movieId );
        }
        
    }
    printf("\n");
}


void duplicateMovies(Movie movies[], int numMovies){
    printf("Filmes duplicados:\n");
    for(int i = 0; i < numMovies; i++){
        for(int j = i+1; j < numMovies; j++){
            if(strcmp(movies[i].title, movies[j].title) == 0){
                printf("Filme: %s (ID: %d)\n", movies[i].title, movies[i].movieId );
            }
        }
    }
    printf("\n");
}

// Mostra apenas os filmes que possuem diretor no banco
void printMovieAndDirector(Movie movies[], Director directors[], int numMovies, int numDirectors)
{
    printf("Filmes com Diretor no banco:\n\n");
    for (int i = 0; i < numMovies; i++)
        for (int j = 0; j < numDirectors; j++)
            if (movies[i].movieId == directors[j].directorId)
            {
                printf("Filme %s (ID: %d) é dirigido por: %s\n", movies[i].title, movies[i].movieId, directors[j].name);

                break;
            }
}


void checkMovieDirectorLink(Movie movies[], Director directors[], int numMovies, int numDirectors  ) {
    printf("Verificação de vínculo entre filmes e diretores:\n");

    for (int i = 0; i < numMovies; i++) {
        int found = 0;  
        for (int j = 0; j < numDirectors; j++) {
            if (movies[i].directorId == directors[j].directorId) {
                printf("Filme %s (ID: %d) é dirigido por: %s\n", movies[i].title, movies[i].movieId, directors[j].name);
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("Filme %s (ID: %d) não possui vínculo com um diretor listado.\n", movies[i].title, movies[i].movieId);
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
        // displayMovies(movies, numMovies);
        // displayDirectors(directors, numDirectors);

        // incompleteMovies(movies, numMovies);
        // duplicateMovies(movies, numMovies);

        checkMovieDirectorLink(movies, directors, numMovies, numDirectors);
        // printMovieAndDirector(movies, directors, numMovies, numDirectors);
    }

    return 0;
}