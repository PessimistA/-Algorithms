#include <stdio.h>
#include <stdlib.h>

#define T 3  // Minimum derece (2T-1 anahtar, 2T çocuk)

typedef struct BTreeNode {
    int keys[2*T-1];
    struct BTreeNode* children[2*T];
    int n;
    int isLeaf;
} BTreeNode;

BTreeNode* createNode(int isLeaf) {
    BTreeNode* node = (BTreeNode*)malloc(sizeof(BTreeNode));
    node->isLeaf = isLeaf;
    node->n = 0;
    for (int i = 0; i < 2*T; i++)
        node->children[i] = NULL;
    return node;
}

void splitChild(BTreeNode* parent, int i, BTreeNode* fullChild) {
    BTreeNode* newChild = createNode(fullChild->isLeaf);
    newChild->n = T - 1;

    for (int j = 0; j < T - 1; j++)
        newChild->keys[j] = fullChild->keys[j + T];

    if (!fullChild->isLeaf)
        for (int j = 0; j < T; j++)
            newChild->children[j] = fullChild->children[j + T];

    for (int j = parent->n; j >= i + 1; j--)
        parent->children[j + 1] = parent->children[j];

    parent->children[i + 1] = newChild;

    for (int j = parent->n - 1; j >= i; j--)
        parent->keys[j + 1] = parent->keys[j];

    parent->keys[i] = fullChild->keys[T - 1];
    parent->n += 1;
    fullChild->n = T - 1;
}

void insertNonFull(BTreeNode* node, int key) {
    int i = node->n - 1;

    if (node->isLeaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->n += 1;
    } else {
        while (i >= 0 && key < node->keys[i])
            i--;
        i++;
        if (node->children[i]->n == 2*T - 1) {
            splitChild(node, i, node->children[i]);
            if (key > node->keys[i])
                i++;
        }
        insertNonFull(node->children[i], key);
    }
}

void insert(BTreeNode** rootRef, int key) {
    BTreeNode* root = *rootRef;
    if (root->n == 2*T - 1) {
        BTreeNode* newRoot = createNode(0);
        newRoot->children[0] = root;
        splitChild(newRoot, 0, root);
        insertNonFull(newRoot, key);
        *rootRef = newRoot;
    } else {
        insertNonFull(root, key);
    }
}
