// Programa em C para implementar uma árvore B+
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define GRAU_MINIMO 3 // Grau mínimo (define a faixa para o número de chaves)

typedef struct No {
    // Array de chaves
    int* chaves;
    // Grau mínimo (define a faixa para o número de chaves)
    int t;
    // Array de ponteiros para os filhos
    struct No** filhos;
    // Número atual de chaves
    int n;
    // Para determinar se o nó é folha ou não
    bool folha;
    // Ponteiro para o próximo nó folha
    struct No* proximo;
} No;

typedef struct ArvoreB {
    // Ponteiro para o nó raiz
    No* raiz;
    // Grau mínimo
    int t;
} ArvoreB;

// Função para criar um novo nó da árvore B+
No* criarNo(int t, bool folha)
{
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->t = t;
    novoNo->folha = folha;
    novoNo->chaves = (int*)malloc((2 * t - 1) * sizeof(int));
    novoNo->filhos = (No**)malloc((2 * t) * sizeof(No*));
    novoNo->n = 0;
    novoNo->proximo = NULL;
    return novoNo;
}

// Função para criar uma nova árvore B+
ArvoreB* criarArvoreB(int t)
{
    ArvoreB* arvore = (ArvoreB*)malloc(sizeof(ArvoreB));
    arvore->t = t;
    arvore->raiz = criarNo(t, true);
    return arvore;
}

// Função para exibir a árvore B+ e imprimir suas chaves
void exibir(No* no)
{
    if (no == NULL)
        return;
    int i;
    for (i = 0; i < no->n; i++) {
        if (!no->folha) {
            exibir(no->filhos[i]);
        }
        printf("%d ", no->chaves[i]);
    }
    if (!no->folha) {
        exibir(no->filhos[i]);
    }
}

// Função para buscar uma chave na árvore B+
bool buscar(No* no, int chave)
{
    int i = 0;
    while (i < no->n && chave > no->chaves[i]) {
        i++;
    }
    if (i < no->n && chave == no->chaves[i]) {
        return true;
    }
    if (no->folha) {
        return false;
    }
    return buscar(no->filhos[i], chave);
}

// Função para dividir o filho de um nó durante a inserção
void dividirFilho(No* pai, int i, No* filho)
{
    int t = filho->t;
    No* novoFilho = criarNo(t, filho->folha);
    novoFilho->n = t - 1;

    for (int j = 0; j < t - 1; j++) {
        novoFilho->chaves[j] = filho->chaves[j + t];
    }

    if (!filho->folha) {
        for (int j = 0; j < t; j++) {
            novoFilho->filhos[j] = filho->filhos[j + t];
        }
    }

    filho->n = t - 1;

    for (int j = pai->n; j >= i + 1; j--) {
        pai->filhos[j + 1] = pai->filhos[j];
    }
    pai->filhos[i + 1] = novoFilho;

    for (int j = pai->n - 1; j >= i; j--) {
        pai->chaves[j + 1] = pai->chaves[j];
    }
    pai->chaves[i] = filho->chaves[t - 1];
    pai->n += 1;
}

// Função para inserir um nó não cheio
void inserirNaoCheio(No* no, int chave)
{
    int i = no->n - 1;

    if (no->folha) {
        while (i >= 0 && no->chaves[i] > chave) {
            no->chaves[i + 1] = no->chaves[i];
            i--;
        }
        no->chaves[i + 1] = chave;
        no->n += 1;
    }
    else {
        while (i >= 0 && no->chaves[i] > chave) {
            i--;
        }
        i++;
        if (no->filhos[i]->n == 2 * no->t - 1) {
            dividirFilho(no, i, no->filhos[i]);
            if (no->chaves[i] < chave) {
                i++;
            }
        }
        inserirNaoCheio(no->filhos[i], chave);
    }
}

// Função para inserir uma chave na árvore B+
void inserir(ArvoreB* arvore, int chave)
{
    No* raiz = arvore->raiz;
    if (raiz->n == 2 * arvore->t - 1) {
        No* novaRaiz = criarNo(arvore->t, false);
        novaRaiz->filhos[0] = raiz;
        dividirFilho(novaRaiz, 0, raiz);
        inserirNaoCheio(novaRaiz, chave);
        arvore->raiz = novaRaiz;
    }
    else {
        inserirNaoCheio(raiz, chave);
    }
}

// Protótipos de função para as funções auxiliares usadas em deletarChave
void deletarChaveAux(No* no, int chave);
int encontrarChave(No* no, int chave);
void removerDeFolha(No* no, int idx);
int obterPredecessor(No* no, int idx);
void preencher(No* no, int idx);
void emprestarDoAnterior(No* no, int idx);
void emprestarDoProximo(No* no, int idx);
void fundir(No* no, int idx);

// Função para deletar uma chave da árvore B+
void deletarChave(ArvoreB* arvore, int chave)
{
    No* raiz = arvore->raiz;

    // Chamar uma função auxiliar para deletar a chave recursivamente
    deletarChaveAux(raiz, chave);

    // Se a raiz não tiver chaves e tiver um filho, tornar o primeiro filho a nova raiz
    if (raiz->n == 0 && !raiz->folha) {
        arvore->raiz = raiz->filhos[0];
        free(raiz);
    }
}

// Função auxiliar para deletar recursivamente uma chave da árvore B+
void deletarChaveAux(No* no, int chave)
{
    int idx = encontrarChave(no, chave); // Encontra o índice da chave no nó

    // Se a chave estiver presente neste nó
    if (idx < no->n && no->chaves[idx] == chave) {
        if (no->folha) {
            // Se o nó for uma folha, simplesmente remove a chave
            removerDeFolha(no, idx);
        }
        else {
            // Se o nó não for uma folha, substitui a chave pelo seu predecessor/sucessor
            int predecessor = obterPredecessor(no, idx);
            no->chaves[idx] = predecessor;
            // Remove recursivamente o predecessor
            deletarChaveAux(no->filhos[idx], predecessor);
        }
    }
    else {
        // Se a chave não estiver presente neste nó, desce para o filho apropriado
        if (no->folha) {
            // Chave não encontrada na árvore
            printf("Chave %d não encontrada na árvore B+.\n", chave);
            return;
        }

        bool ehUltimoFilho = (idx == no->n);

        // Se o filho onde a chave deveria estar tiver menos de t chaves, preenche esse filho
        if (no->filhos[idx]->n < no->t) {
            preencher(no, idx);
        }

        // Se o último filho foi fundido, deve ter sido fundido com o filho anterior

        // Então, precisamos deletar recursivamente a chave do filho anterior
        if (ehUltimoFilho && idx > no->n) {
            deletarChaveAux(no->filhos[idx - 1], chave);
        }
        else {
            deletarChaveAux(no->filhos[idx], chave);
        }
    }
}

// Função para encontrar o índice de uma chave em um nó
int encontrarChave(No* no, int chave)
{
    int idx = 0;
    while (idx < no->n && chave > no->chaves[idx]) {
        idx++;
    }
    return idx;
}

// Função para remover uma chave de um nó folha
void removerDeFolha(No* no, int idx)
{
    for (int i = idx + 1; i < no->n; ++i) {
        no->chaves[i - 1] = no->chaves[i];
    }
    no->n--;
}

// Função para obter o predecessor de uma chave em um nó não folha
int obterPredecessor(No* no, int idx)
{
    No* atual = no->filhos[idx];
    while (!atual->folha) {
        atual = atual->filhos[atual->n];
    }
    return atual->chaves[atual->n - 1];
}

// Função para preencher um filho que tem menos de t chaves
void preencher(No* no, int idx)
{
    if (idx != 0 && no->filhos[idx - 1]->n >= no->t) {
        emprestarDoAnterior(no, idx);
    }
    else if (idx != no->n && no->filhos[idx + 1]->n >= no->t) {
        emprestarDoProximo(no, idx);
    }
    else {
        if (idx != no->n) {
            fundir(no, idx);
        }
        else {
            fundir(no, idx - 1);
        }
    }
}

// Função para emprestar uma chave do nó anterior
void emprestarDoAnterior(No* no, int idx)
{
    No* filho = no->filhos[idx];
    No* irmao = no->filhos[idx - 1];

    for (int i = filho->n - 1; i >= 0; --i) {
        filho->chaves[i + 1] = filho->chaves[i];
    }

    if (!filho->folha) {
        for (int i = filho->n; i >= 0; --i) {
            filho->filhos[i + 1] = filho->filhos[i];
        }
    }

    filho->chaves[0] = no->chaves[idx - 1];

    if (!filho->folha) {
        filho->filhos[0] = irmao->filhos[irmao->n];
    }

    no->chaves[idx - 1] = irmao->chaves[irmao->n - 1];

    filho->n += 1;
    irmao->n -= 1;
}

// Função para emprestar uma chave do nó seguinte
void emprestarDoProximo(No* no, int idx)
{
    No* filho = no->filhos[idx];
    No* irmao = no->filhos[idx + 1];

    filho->chaves[filho->n] = no->chaves[idx];

    if (!filho->folha) {
        filho->filhos[filho->n + 1] = irmao->filhos[0];
    }

    no->chaves[idx] = irmao->chaves[0];

    for (int i = 1; i < irmao->n; ++i) {
        irmao->chaves[i - 1] = irmao->chaves[i];
    }

    if (!irmao->folha) {
        for (int i = 1; i <= irmao->n; ++i) {
            irmao->filhos[i - 1] = irmao->filhos[i];
        }
    }

    filho->n += 1;
    irmao->n -= 1;
}

// Função para fundir dois filhos
void fundir(No* no, int idx)
{
    No* filho = no->filhos[idx];
    No* irmao = no->filhos[idx + 1];

    filho->chaves[no->t - 1] = no->chaves[idx];

    for (int i = 0; i < irmao->n; ++i) {
        filho->chaves[i + no->t] = irmao->chaves[i];
    }

    if (!filho->folha) {
        for (int i = 0; i <= irmao->n; ++i) {
            filho->filhos[i + no->t] = irmao->filhos[i];
        }
    }

    for (int i = idx + 1; i < no->n; ++i) {
        no->chaves[i - 1] = no->chaves[i];
    }

    for (int i = idx + 2; i <= no->n; ++i) {
        no->filhos[i - 1] = no->filhos[i];
    }

    filho->n += irmao->n + 1;
    no->n--;

    free(irmao);
}

// Função principal para testar a implementação da árvore B+
int main()
{
    int t = GRAU_MINIMO;
    ArvoreB* arvore = criarArvoreB(t);

    // Inserir algumas chaves na árvore B+
    inserir(arvore, 10);
    inserir(arvore, 20);
    inserir(arvore, 5);
    inserir(arvore, 6);
    inserir(arvore, 12);
    inserir(arvore, 30);
    inserir(arvore, 7);
    inserir(arvore, 17);

    printf("Árvore B+ criada:\n");
    exibir(arvore->raiz);

    // Deletar uma chave
    deletarChave(arvore, 6);
    printf("\nÁrvore B+ após deletar 6:\n");
    exibir(arvore->raiz);

    // Buscar uma chave
    int chave = 10;
    if (buscar(arvore->raiz, chave)) {
        printf("\nChave %d encontrada na árvore B+.\n", chave);
    }
    else {
        printf("\nChave %d não encontrada na árvore B+.\n", chave);
    }

    return 0;
}
