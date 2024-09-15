#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TITLE_LEN 100
#define MAX_URL_LEN 256
#define INDEX_FILE "movie_index.bin"
#define EXTENSION_FILE "movie_extension.bin"

typedef struct {
    char url[MAX_URL_LEN];
    char title[MAX_TITLE_LEN];
    int movieId;
    int releaseYear;
    int directorId;
} Movie;

typedef struct{
    int movieId;
    long offset; // posição do registro no arquivo binário
} IndexEntry;

// Função para abrir arquivo, agora com parâmetros const
FILE *openFile(const char *filename, const char *mode) {
    FILE *file = fopen(filename, mode);
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s\n", filename);
        exit(1);
    }
    return file;
}

// Função que carrega os filmes de um arquivo
int loadMovies(const char *filename, Movie movies[]) {
    FILE *file = openFile(filename, "r");

    char line[1000];
    int count = 0;

    // Read each line until the end of the file
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ";");

        // Movie ID (mandatory)
        if (token != NULL) {
            movies[count].movieId = atoi(token);
        } else {
            continue; // Skip incomplete line
        }

        // Title (mandatory)
        token = strtok(NULL, ";");
        if (token != NULL) {
            strncpy(movies[count].title, token, sizeof(movies[count].title) - 1);
            movies[count].title[sizeof(movies[count].title) - 1] = '\0';
        } else {
            strcpy(movies[count].title, "Title not available");
        }

        // Release year (optional, set to 0 if not present)
        token = strtok(NULL, ";");
        if (token != NULL && strlen(token) > 0) {
            movies[count].releaseYear = atoi(token);
        } else {
            movies[count].releaseYear = 0; // Default value when missing
        }

        // URL (optional, handle NULL)
        token = strtok(NULL, ";");
        if (token != NULL && strlen(token) > 0) {
            strncpy(movies[count].url, token, sizeof(movies[count].url) - 1);
            movies[count].url[sizeof(movies[count].url) - 1] = '\0';
        } else {
            strcpy(movies[count].url, "URL not available");
        }

        // Director ID (optional, set to -1 if not present)
        token = strtok(NULL, ";");
        if (token != NULL && strlen(token) > 0) {
            movies[count].directorId = atoi(token);
        } else {
            movies[count].directorId = -1; // Default value when missing
        }

        count++;
    }

    fclose(file);
    return count;
}



// FUnção de comparação por título que se é utilizado no sort
int compareMoviesByTitle(const void *a, const void *b) {
    Movie *movieA = (Movie *)a;
    Movie *movieB = (Movie *)b;
    return strcmp(movieA->title, movieB->title);
}

// Ordenação dos filmes por título
void sortMovies(Movie movies[], int numMovies) {
    qsort(movies, numMovies, sizeof(Movie), compareMoviesByTitle);

}

// salvar os filmes ordenados em um arquivo binário
void createBinaryFileFromMovies(const char *filename, Movie movies[], int numMovies ){
    FILE *file = openFile(filename, "wb");
    for(int i = 0; i < numMovies; i++){
        fwrite(&movies[i], sizeof(Movie), 1, file);
    }
    fclose(file);
}

// Função de busca binária na memória
int binarySearchInMemory(Movie movies[], int numMovies, const char *movieTitle, int *comparisons){
    
    // low e high representam os limites da busca
    int low = 0, high = numMovies - 1;
    *comparisons = 0;

    while(low <= high){
        (*comparisons)++;

        int mid = (low + high) / 2;
        int cmp = strcmp(movies[mid].title, movieTitle);
        // printf("Comparando %s com %s\n", movies[mid].title, movieTitle);
        if(cmp == 0){
            return mid; // Encontrou o filme
        } else if(cmp < 0){
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    
    }
    return -1; // Filme não encontrado
}

// Função de busca binária no arquivo
int binarySearchInFile(const char *movieTitle, int *comparisons){
    FILE *file = openFile("movies.bin", "rb");
    Movie movie; 
    int low = 0;

    fseek(file, 0, SEEK_END); // Move o cursor para o final do arquivo
    int high = ftell(file) / sizeof(Movie) - 1; // Calcula o número de registros no arquivo
    *comparisons = 0;

    while(low <= high){
        (*comparisons)++;
        int mid = (low + high) / 2;
        fseek(file, mid * sizeof(Movie), SEEK_SET); // Move o cursor para o meio do arquivo
        fread(&movie, sizeof(Movie), 1, file); // Lê o registro do meio

        int cmp = strcmp(movie.title, movieTitle);
        // printf("Comparando %s com %s\n", movie.title, movieTitle);

        if(cmp == 0){
            fclose(file);
            return mid; // Encontrou o filme
        } else if(cmp < 0){
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    fclose(file);
    return -1; // Filme não encontrado
}




void main_tde_one(){
    int n, comparisons;
    Movie movies[10000];
    const char *movieTitle = "Sweet Nothing";

    n = loadMovies("arqMovies.txt", movies);
    if (n <= 0) {
        printf("Erro ao carregar os filmes\n");
        exit(1);
    }

    // Ordenar os filmes por título
    sortMovies(movies, n);

    // Salvar os filmes ordenados em um arquivo binário
    createBinaryFileFromMovies("movies.bin", movies, n);
    

    // Busca binária na memória
    clock_t start = clock();
    int index = binarySearchInMemory(movies, n, movieTitle, &comparisons);
    
    clock_t end = clock();
    double memoryTime = (double)(end - start) / CLOCKS_PER_SEC; // Tempo da busca em segundos

    if (index != -1) {
        printf("Encontrado '%s' no index %d (Comparações: %d, Time: %f s)\n\n",
                movieTitle, index, comparisons, memoryTime);

    } else {
        printf("'%s' não encontrado na memória (Comparações: %d, Time: %f s)\n\n",
                movieTitle, comparisons, memoryTime);
    }

    // Busca binária no arquivo
    start = clock();
    index = binarySearchInFile(movieTitle, &comparisons);
    end = clock();
    memoryTime = (double)(end - start) / CLOCKS_PER_SEC; // Tempo da busca em segundos

    if (index != -1) {
        printf("Encontrado '%s' no index %d (Comparações: %d, Time: %f s)\n\n",
                movieTitle, index, comparisons, memoryTime);

    } else {
        printf("'%s' não encontrado na memória (Comparações: %d, Time: %f s)\n\n",
                movieTitle, comparisons, memoryTime);
    }
}



// Função para criar um índice de filmes por ID
void createIndexById(const Movie movies[], int n, const char *indexFileName){
    FILE *indexFile = openFile(indexFileName, "wb");
    
    if(!indexFile){
        printf("Erro ao abrir o arquivo de índice\n");
        return;
    }

    fwrite(movies, sizeof(Movie), n, indexFile); // Escreve os registros no arquivo
    fclose(indexFile);
}

// cria a área de extensão
void createExtensionArea(const Movie movies[], int n, const char *extensionFileName){
    FILE *extensionFile = openFile(extensionFileName, "wb");
    if(!extensionFile){
        printf("Erro ao abrir o arquivo de extensão\n");
        return;
    }

    fwrite(movies, sizeof(Movie), n, extensionFile);
    fclose(extensionFile);
}


//carregar o índice
void loadIndexById(const char *indexFilename, Movie movies[], int *n){
    FILE *indexFile = openFile(indexFilename, "rb");
    if(!indexFile){
        printf("Erro ao abrir o arquivo de índice\n");
        return;
    }

    fseek(indexFile, 0, SEEK_END);
    long fileSize = ftell(indexFile);
    *n = fileSize / sizeof(Movie);
    rewind(indexFile); // Volta para o início do arquivo
    fread(movies, sizeof(Movie), *n, indexFile); // Lê os registros do arquivo
    fclose(indexFile);
}

// inserir um novo filme com área de extensão

void insertMovieWithExtension(const Movie *movie, const char *extensionFileName){
    FILE *extensionFile = openFile(extensionFileName, "ab");
    if(!extensionFile){
        printf("Erro ao abrir o arquivo de extensão\n");
        exit(1);
    }

    fwrite(movie, sizeof(Movie), 1, extensionFile);
    fclose(extensionFile);
}

void reorganizeIndex(const char *indexFileName, const char *extensionFileName){
    Movie movies[10000];
    int n;

    loadIndexById(indexFileName, movies, &n);
    FILE *extensionFile = openFile(extensionFileName, "rb");

    if(extensionFile){
        fseek(extensionFile, 0, SEEK_END); // Move o cursor para o final do arquivo
        long extensionSize = ftell(extensionFile); // Tamanho do arquivo de extensão
        int extensionCount = extensionSize / sizeof(Movie); // Número de registros no arquivo de extensão
        rewind(extensionFile); // Volta para o início do arquivo
        fread(movies + n, sizeof(Movie), extensionCount, extensionFile); // Lê os registros do arquivo de extensão
        fclose(extensionFile);
    }

    sortMovies(movies, n);
    createIndexById(movies, n, indexFileName); // Recria o índice com os registros reorganizados

    // Limpar a área de extensão
    FILE *extensionFileTruncate = fopen(extensionFileName, "wb");
    if (extensionFileTruncate) {
        fclose(extensionFileTruncate);
    }
}

int binarySearchInIndexFile(const char *indexFileName, const char *title, int *comparisons){
    FILE *indexFile = openFile(indexFileName, "rb");
    if (!indexFile) {
        printf("Erro ao abrir o arquivo de índice\n");
        exit(1);
    }

    fseek(indexFile, 0, SEEK_END);
    long fileSize = ftell(indexFile);
    int numRecords = fileSize / sizeof(Movie);
    rewind(indexFile);

    int low = 0, high = numRecords - 1;
    *comparisons = 0;
    Movie movie;

    while (low <= high) {
        (*comparisons)++;
        int mid = (low + high) / 2;
        fseek(indexFile, mid * sizeof(Movie), SEEK_SET);
        fread(&movie, sizeof(Movie), 1, indexFile);

        int cmp = strcmp(title, movie.title);
        if (cmp == 0) {
            fclose(indexFile);
            return mid; // Encontrou o filme
        } else if (cmp < 0) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    fclose(indexFile);
    return -1; // Filme não encontrado
}

void main_tde_two(){
    const char *filename = "arqMovies.txt";
    const char *indexFileName = INDEX_FILE;
    const char *extensionFileName = EXTENSION_FILE;
    const char *movieTitle = "Sweet Nothing";

    Movie movies[10000];
    int n;


    // Carregar e ordenar os filmes

    n = loadMovies(filename, movies);
    if (n <= 0) {
        printf("Erro ao carregar os filmes\n");
        exit(1);
    }

    sortMovies(movies, n);

    // criar o índice e a área de extensão
    createIndexById(movies, n, indexFileName);
    createExtensionArea(movies, n, extensionFileName);

    //inserir novo filme com area de extensão
    Movie newMovie = {"https://www.newmovie.com", "New Movie",  9999, 2024, 1};
    insertMovieWithExtension(&newMovie, extensionFileName);

    // reordenar os índices após inserir
    reorganizeIndex(indexFileName, extensionFileName);


    // Busca binária no arquivo utilizando o índice
    int comparisons;    
    clock_t start = clock();
    int index = binarySearchInIndexFile(indexFileName, movieTitle, &comparisons);
    clock_t end = clock();
    double memoryTime = (double)(end - start) / CLOCKS_PER_SEC; // Tempo da busca em segundos

    if (index != -1) {
        printf("Encontrado '%s' no index %d (Comparações: %d, Time: %f s)\n\n",
                movieTitle, index, comparisons, memoryTime);

    } else {
        printf("'%s' não encontrado na memória (Comparações: %d, Time: %f s)\n\n",
                movieTitle, comparisons, memoryTime);
    }

}


int main() {

    // main_tde_one();
    main_tde_two();


    return 0;
}
