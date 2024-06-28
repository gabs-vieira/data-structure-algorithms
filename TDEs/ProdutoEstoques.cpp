#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct product {
    char c[20];
    int quantidade;
    struct product *esq;
    struct product *dir;
} PRODUCT;

typedef struct nodo {
    char c;
    struct nodo *prox;
    PRODUCT *seed;
} NODO;

NODO* verificaKeyCatalogo(char key, NODO **ini) {
    // Verifica se a chave já existe no catálogo, caso não tiver insere a chave em ordem alfabética
    NODO *aux = (NODO *) malloc(sizeof(NODO));
    NODO *auxIni = *ini;
    NODO *anterior = NULL;
    aux->c = key;
    aux->prox = NULL;
    aux->seed = NULL;

    // Aloca em primeiro
    if (*ini == NULL) {
        *ini = aux; // Insere no início
        return aux;
    } else {
        while (auxIni != NULL && auxIni->c < key) {
            anterior = auxIni;
            auxIni = auxIni->prox;
        }

        if (auxIni != NULL && auxIni->c == key) {
            free(aux);
            return auxIni; // Chave já existe no catálogo
        }

        if (anterior == NULL) {
            // Se o anterior for NULL, então o elemento é o primeiro
            aux->prox = *ini;
            *ini = aux;
        } else {
            // Se não, insere o elemento na posição correta (entre o anterior e o auxIni)
            aux->prox = anterior->prox;
            anterior->prox = aux;
        }

        return aux;
    }
}


void addProduct(PRODUCT **root, char *productName, int quantity) {
    // aloca memória para um novo produto e inicializa seus campos
    PRODUCT *newProduct = (PRODUCT *) malloc(sizeof(PRODUCT));
    strcpy(newProduct->c, productName);
    newProduct->quantidade = quantity;
    newProduct->esq = NULL;
    newProduct->dir = NULL;

    // se a árvore estiver vazia, insere o novo produto como a raiz
    if (*root == NULL) {
        *root = newProduct;
    } else {
        PRODUCT *current = *root;
        PRODUCT *parent = NULL;

        //percorre árvore para encontrar a posição correta para inserir o novo produto
        while (current != NULL) {
            parent = current;
            if (strcmp(productName, current->c) == 0) {
                // Produto já existe, liberar a memória alocada para newProduct e retornar
                printf("Produto já existe\n");
                free(newProduct);
                return;
            } else if (strcmp(productName, current->c) < 0) {
                // Se o nome do novo produto é menor, continua a busca na subárvore esquerda
                current = current->esq;
            } else {
                // Se o nome do novo produto é maior, continua a busca na subárvore direita
                current = current->dir;
            }
        }

        // insere o novo produto na posição correta
        if (strcmp(productName, parent->c) < 0) {
            parent->esq = newProduct; // Se o nome do novo produto é menor, insere na subárvore esquerda
        } else {
            parent->dir = newProduct; // Se o nome do novo produto é maior, insere na subárvore direita
        }
    }
}

void addWord(NODO **ini, char *word, int quantity) {
    char key = tolower(word[0]);
    NODO *catalogoNodo = verificaKeyCatalogo(key, ini);
    addProduct(&(catalogoNodo->seed), word, quantity);  // Exemplo de quantidade fixa, pode ser ajustado conforme necessário
}


//Função que exibe todos os produtos do catálogo. Mostra a letra e também todos os produtos daquela letra.
//OBS: No trabalho pedia duas funções separadas, esta esta mesclada
void printCatalog(NODO *ini) {
    while (ini != NULL) {
        printf("Letra %c:\n", ini->c);
        PRODUCT *product = ini->seed;
        while (product != NULL) {
            printf("\t* %s - Quantidade: %d\n", product->c, product->quantidade);
            product = product->dir;  // Printando apenas na direção direita
        }
        ini = ini->prox;
    }
}


void consultaProduto(NODO *ini, char *productName){
    char key = tolower(productName[0]);

    //vai percorrer a lista encadeada de letras até encontrar a letra inicial correta
    while(ini != NULL && ini->c < key){
        ini = ini->prox;
    }
    //Se a letra não for encontrada, printa que o produto não foi encontrado
    if (ini == NULL){
        printf("Produto não encontrado\n");
        return;
    }

    //busca na árvore binária de produtos que corresponde a letra (key)
    PRODUCT *current = ini->seed; // Pega o primeiro produto da letra
    while(current != NULL){
        int cmp = strcmp(productName, current->c); // Compara o nome do produto com o produto atual

        if (cmp == 0){
            //nomes iguais == produto encontrado
            printf("Produto encontrado: %s - Quantidade: %d\n", current->c, current->quantidade);
            return;
        } else if (cmp < 0){
            //Se o nome do produto procurado é menor (alfabeitcamente), continua a busca na subárvore esquerda
            current = current->esq;
        } else {
            //Se o nome do produto procurado é maior (alfabeitcamente), continua a busca na subárvore direita
            current = current->dir;
        }
    }

    printf("Produto não encontrado\n");
}


PRODUCT* findMin(PRODUCT* ini){
    while(ini->esq != NULL){
        ini = ini->esq;
    }
    return ini;
}

PRODUCT* removeProduto(PRODUCT *ini, char *nomeProduto){
    if(ini == NULL) return ini;

    int cmp = strcmp(nomeProduto, ini->c);

    if(cmp < 0){
        //Se o nome do produto procurado é menor (alfabeitcamente), continua a busca na subárvore esquerda
        ini->esq = removeProduto(ini->esq, nomeProduto); //Chama a função recursivamente para a subárvore esquerda

    }else if(cmp >0){
        //Se o nome do produto procurado é maior (alfabeitcamente), continua a busca na subárvore direita
        ini->dir = removeProduto(ini->dir, nomeProduto); //Chama a função recursivamente para a subárvore direita

    }else{
        //produto encontrado --> próximo passo é remover

        if(ini->esq == NULL) {
            //Se o produto não tem filho à esquerda, então o filho à direita se torna o novo pai
            PRODUCT *temp = ini->dir;
            free(ini);
            return temp;

        }else if(ini->dir == NULL){
            //Se o produto não tem filho à direita, então o filho à esquerda se torna o novo pai
            PRODUCT *temp = ini->esq;
            free(ini);
            return temp;
        }

        //Se o produto tem dois filhos, então o produto é substituído pelo menor produto da subárvore direita
        PRODUCT *temp = findMin(ini->dir);
        strcpy(ini->c, temp->c); //Copia o nome do produto
        ini->quantidade = temp->quantidade; //Copia a quantidade do produto
        ini->dir = removeProduto(ini->dir, temp->c); //Remove o produto da subárvore direita
    }

    return ini;
}

//Função para contar o número total de produtos na árvore binária de pesquisa (ABP) de cada produto
int totalProdutos(PRODUCT *ini){
    if(ini == NULL) return 0;
    return 1 + totalProdutos(ini->esq) + totalProdutos(ini->dir);
}

//Função pra contar o número total de produtos na lista encadeada de nodos
int totalProdutosCatalogo(NODO *ini){
    int total = 0;
    while(ini != NULL){
        total += totalProdutos(ini->seed);
        ini = ini->prox;
    }
    return total;
}


//Função para somar a quantidade total de todos os produtos na ABP
int totalQuantidadesProdutos(PRODUCT* ini){
    if(ini == NULL) return 0;
    return ini->quantidade + totalQuantidadesProdutos(ini->esq) + totalQuantidadesProdutos(ini->dir);
}
//Somar a quantidade total de produtos na lista encadeada de nodos
int totalQuantidadesCatalogo(NODO *ini){
    int total = 0;
    while(ini != NULL){
        total += totalQuantidadesProdutos(ini->seed);
        ini = ini->prox;
    }
    return total;
}

//Função para exibir os produtos com quantidade maior que X
void exibeCatalogoDeQuantidade(NODO *ini, int quantidade, bool maiorQue){
    while(ini != NULL){
        PRODUCT *product = ini->seed;
        while(product != NULL){
            if(maiorQue){
                if(product->quantidade > quantidade){
                    printf("  Produto: %s - Quantidade: %d\n", product->c, product->quantidade);
                }
            }else{
                if(product->quantidade <= quantidade){
                    printf("  Produto: %s - Quantidade: %d\n", product->c, product->quantidade);
                }
            }
            product = product->dir;
        }
        ini = ini->prox;
    }
}

// Função para percorrer a árvore binária de pesquisa (ABP) de cada produto em ordem prefixada
void preifixadoProduto(PRODUCT *ini){
    if(ini != NULL){
        printf("\t %s - Quantidade: %d\n", ini->c, ini->quantidade);
        preifixadoProduto(ini->esq);
        preifixadoProduto(ini->dir);
    }
}
//Função pra fazer o percurso prefixiado de forma completa, indo de nodo em nodo (letra em letra) e de produto em produto
void prefixadoCompleto(NODO *ini){
    while(ini != NULL){
        printf("Letra %c:\n", ini->c);
        preifixadoProduto(ini->seed);
        ini = ini->prox;
    }
}

int menu(){
    int opcao;
    printf("\n----- Menu -----\n");
    printf("1. Adicionar produto\n");
    printf("2. Consultar produto\n");
    printf("3. Remover produto\n");
    printf("4. Total de produtos\n");
    printf("5. Total de quantidades\n");
    printf("6. Exibir catálogo\n");
    printf("7. Exibir produtos com quantidade maior que X\n");
    printf("8. Exibir produtos com quantidade menor ou igual a X\n");
    printf("9. Exibir catálogo completo (prefixado)\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    return opcao;
}


int main() {
    NODO *ini = NULL;
    
    int opcao, quantidade;
    char produto[50];
    
    while ((opcao = menu()) != 0) {
        switch (opcao) {
            case 1:
                printf("Digite o nome do produto: ");
                scanf("%s", produto);
                printf("Digite a quantidade: ");
                scanf("%d", &quantidade);
                addWord(&ini, produto, quantidade);
                break;
            case 2:
                printf("Digite o nome do produto para consulta: ");
                scanf("%s", produto);
                consultaProduto(ini, produto);
                break;
            case 3:
                printf("Digite o nome do produto para remover: ");
                scanf("%s", produto);
                ini->seed = removeProduto(ini->seed, produto);
                break;
            case 4:
                printf("Total de produtos: %d\n", totalProdutosCatalogo(ini));
                break;
            case 5:
                printf("Total de quantidades de produtos: %d\n", totalQuantidadesCatalogo(ini));
                break;
            case 6:
                printCatalog(ini);
                break;
            case 7:
                printf("Digite a quantidade para exibir produtos com quantidade maior que: ");
                scanf("%d", &quantidade);
                exibeCatalogoDeQuantidade(ini, quantidade, true);
                break;
            case 8:
                printf("Digite a quantidade para exibir produtos com quantidade menor ou igual a: ");
                scanf("%d", &quantidade);
                exibeCatalogoDeQuantidade(ini, quantidade, false);
                break;
            case 9:
                prefixadoCompleto(ini);
                break;
            default:
                printf("Opcao invalida!\n");
        }
    }



    return 0;
}
