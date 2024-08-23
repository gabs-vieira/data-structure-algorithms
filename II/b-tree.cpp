#include <stdio.h>
#include <stdlib.h>

#define ORDER 1 // Ordem 1 (2-3 Tree)

typedef struct BTreeNode {
    int keys[2 * ORDER];
    struct BTreeNode *children[2 * ORDER + 1];
    int n;    // Número de chaves no nó
    int leaf; // 1 se nó é folha, 0 caso contrário
} BTreeNode;

typedef struct BTree {
    BTreeNode *root;
} BTree;

// Criar um nó
BTreeNode *createNode(int leaf) {
    BTreeNode *node = (BTreeNode *)malloc(sizeof(BTreeNode));
    node->n = 0;
    node->leaf = leaf;

    for (int i = 0; i < (2 * ORDER + 1); i++) {
        node->children[i] = NULL;
    }

    return node;
}

// Criar uma árvore B-Tree
BTree *createBTree() {
    BTree *tree = (BTree *)malloc(sizeof(BTree));
    tree->root = createNode(1);
    return tree;
}

// Dividir filho
void splitChild(BTreeNode *x, int i, BTreeNode *y) {
    BTreeNode *z = createNode(y->leaf);
    z->n = ORDER;

    for (int j = 0; j < ORDER; j++) {
        z->keys[j] = y->keys[j + ORDER];
    }

    if (!y->leaf) {
        for (int j = 0; j < ORDER; j++) {
            z->children[j] = y->children[j + ORDER];
        }
    }

    y->n = ORDER;
    for (int j = x->n; j >= i + 1; j--) {
        x->children[j + 1] = x->children[j];
    }

    x->children[i + 1] = z;
    for (int j = x->n - 1; j >= i; j--) {
        x->keys[j + 1] = x->keys[j];
    }

    x->keys[i] = y->keys[ORDER - 1];
    x->n = x->n + 1;
}

// Inserir em um nó não cheio
void insertNonFull(BTreeNode *x, int k) {
    int i = x->n - 1;

    if (x->leaf) {
        while (i >= 0 && k < x->keys[i]) {
            x->keys[i + 1] = x->keys[i];
            i--;
        }
        x->keys[i + 1] = k;
        x->n = x->n + 1;
    } else {
        while (i >= 0 && k < x->keys[i]) {
            i--;
        }
        i++;
        if (x->children[i]->n == 2 * ORDER) {
            splitChild(x, i, x->children[i]);
            if (k > x->keys[i]) {
                i++;
            }
        }
        insertNonFull(x->children[i], k);
    }
}

// Inserção de um número na B-Tree
void insert(BTree *tree, int k) {
    BTreeNode *r = tree->root;

    if (r->n == 2 * ORDER) {
        BTreeNode *s = createNode(0);
        tree->root = s;

        s->children[0] = r;
        splitChild(s, 0, r);
        insertNonFull(s, k);
    } else {
        insertNonFull(r, k);
    }
}

// Procurar um número na B-Tree
BTreeNode *search(BTreeNode *x, int k) {
    int i = 0;
    while (i < x->n && k > x->keys[i]) {
        i++;
    }

    if (i < x->n && k == x->keys[i]) {
        return x;
    }

    if (x->leaf) {
        return NULL;
    } else {
        return search(x->children[i], k);
    }
}

// Exibir os números em ordem crescente
void numbersInOrder(BTreeNode *x) {
    int i;
    for (i = 0; i < x->n; i++) {
        if (!x->leaf) {
            numbersInOrder(x->children[i]);
        }
        printf("%d ", x->keys[i]);
    }

    if (!x->leaf) {
        numbersInOrder(x->children[i]);
    }
}

int main() {
    BTree *tree = createBTree();

    insert(tree, 10);
    insert(tree, 20);
    insert(tree, 5);
    insert(tree, 6);
    insert(tree, 12);
    insert(tree, 30);
    insert(tree, 7);
    insert(tree, 17);

    numbersInOrder(tree->root); 
    printf("\n");

    if (search(tree->root, 6) != NULL) {
        printf("Found 6\n");
    } else {
        printf("6 not found\n");
    }

    return 0;
}
