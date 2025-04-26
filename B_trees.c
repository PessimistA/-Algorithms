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


//düzenli
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define T 3  // Minimum degree (t)

typedef struct BTreeNode {
    int keys[2 * T - 1];
    struct BTreeNode *children[2 * T];
    int n;
    bool isLeaf;
} BTreeNode;

// Yeni düğüm oluşturur
BTreeNode* createNode(bool isLeaf) {
    BTreeNode* node = (BTreeNode*)malloc(sizeof(BTreeNode));
    node->isLeaf = isLeaf;
    node->n = 0;
    for (int i = 0; i < 2 * T; i++) {
        node->children[i] = NULL;
    }
    return node;
}

// Bir düğüm içinde anahtar arar
void search(BTreeNode* node, int key) {
    int i = 0;
    while (i < node->n && key > node->keys[i])
        i++;

    if (i < node->n && node->keys[i] == key) {
        printf("Key %d found in node.\n", key);
        return;
    }

    if (node->isLeaf) {
        printf("Key %d not found.\n", key);
        return;
    }

    search(node->children[i], key);
}

// Bir düğüm doluysa split eder
void splitChild(BTreeNode* parent, int i, BTreeNode* y) {
    BTreeNode* z = createNode(y->isLeaf);
    z->n = T - 1;

    for (int j = 0; j < T - 1; j++)
        z->keys[j] = y->keys[j + T];

    if (!y->isLeaf) {
        for (int j = 0; j < T; j++)
            z->children[j] = y->children[j + T];
    }

    y->n = T - 1;

    for (int j = parent->n; j >= i + 1; j--)
        parent->children[j + 1] = parent->children[j];

    parent->children[i + 1] = z;

    for (int j = parent->n - 1; j >= i; j--)
        parent->keys[j + 1] = parent->keys[j];

    parent->keys[i] = y->keys[T - 1];
    parent->n++;
}

// Bir düğüme anahtar ekler (dolu değilse)
void insertNonFull(BTreeNode* node, int key) {
    int i = node->n - 1;

    if (node->isLeaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->n++;
    } else {
        while (i >= 0 && key < node->keys[i])
            i--;

        i++;

        if (node->children[i]->n == 2 * T - 1) {
            splitChild(node, i, node->children[i]);

            if (key > node->keys[i])
                i++;
        }
        insertNonFull(node->children[i], key);
    }
}

// B-Tree'ye anahtar ekler
void insert(BTreeNode** rootRef, int key) {
    BTreeNode* root = *rootRef;

    if (root->n == 2 * T - 1) {
        BTreeNode* s = createNode(false);
        s->children[0] = root;
        splitChild(s, 0, root);

        int i = 0;
        if (s->keys[0] < key)
            i++;
        insertNonFull(s->children[i], key);

        *rootRef = s;
    } else {
        insertNonFull(root, key);
    }
}

// Ağacı ekrana basar
void printTree(BTreeNode* node, int depth) {
    int i;
    for (i = 0; i < node->n; i++) {
        if (!node->isLeaf)
            printTree(node->children[i], depth + 1);
        for (int j = 0; j < depth; j++) printf("    ");
        printf("%d\n", node->keys[i]);
    }
    if (!node->isLeaf)
        printTree(node->children[i], depth + 1);
}
int findKeyIndex(BTreeNode* node, int key) {
    int idx = 0;
    while (idx < node->n && node->keys[idx] < key)
        idx++;
    return idx;
}
int findMax(BTreeNode* node) {
    while (!node->isLeaf)
        node = node->children[node->n];
    return node->keys[node->n - 1];
}
int findPredecessor(BTreeNode* node, int key) {
    int idx = findKeyIndex(node, key);

    if (idx < node->n && node->keys[idx] == key) {
        // Eğer key bulundu
        if (!node->isLeaf) {
            // Eğer node leaf değilse, sol child'ın max değerine git
            return findMax(node->children[idx]);
        } else {
            // Eğer leaf ise ve solda başka key varsa
            if (idx > 0)
                return node->keys[idx - 1];
            else {
                // Burada normalde parent'a çıkman gerekir (bizim kodda parent bilgisi tutulmuyor)
                // Bu yüzden basit sistemde -1 dönelim
                printf("No predecessor exists in this simple model (requires parent links).\n");
                return -1;
            }
        }
    } else {
        // Key bulunamadı
        printf("Key %d not found in the tree.\n", key);
        return -1;
    }
}
int main() {
    BTreeNode* root = createNode(true);

    insert(&root, 22);
    insert(&root, 1);
    insert(&root, 87);
    insert(&root, 6);
    insert(&root, 36);
    insert(&root, 8);
    insert(&root, 47);
    insert(&root, 11);
    insert(&root, 45);
    insert(&root, 3);
    insert(&root, 2);

    printf("B-Tree:\n");
    printTree(root, 0);
 int pred = findPredecessor(root, 6);
    if (pred != -1)
        printf("Predecessor of 6 is %d\n", pred);

//temiz versiyon
    #include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define T 3 // Minimum degree (t)

typedef struct BTreeNode
{
    int keys[2 * T - 1];
    struct BTreeNode *children[2 * T];
    int n;
    bool isLeaf;
} BTreeNode;

// Yeni düğüm oluşturur
BTreeNode *createNode(bool isLeaf)
{
    BTreeNode *node = (BTreeNode *)malloc(sizeof(BTreeNode));
    if (!node)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE); // Programı sonlandır
    }
    node->isLeaf = isLeaf;
    node->n = 0;
    for (int i = 0; i < 2 * T; i++)
    {
        node->children[i] = NULL;
    }
    return node;
}

// Bir düğüm içinde anahtar arar
void search(BTreeNode *node, int key)
{
    int i = 0;
    while (i < node->n && key > node->keys[i])
        i++;

    if (i < node->n && node->keys[i] == key)
    {
        printf("Key %d found in node.\n", key);
        return;
    }

    if (node->isLeaf)
    {
        printf("Key %d not found.\n", key);
        return;
    }

    search(node->children[i], key);
}

// Bir düğüm doluysa split eder
void splitChild(BTreeNode *parent, int i, BTreeNode *y)
{
    BTreeNode *z = createNode(y->isLeaf);
    z->n = T - 1;

    for (int j = 0; j < T - 1; j++)
        z->keys[j] = y->keys[j + T];

    if (!y->isLeaf)
    {
        for (int j = 0; j < T; j++)
            z->children[j] = y->children[j + T];
    }

    y->n = T - 1;

    for (int j = parent->n; j >= i + 1; j--)
        parent->children[j + 1] = parent->children[j];

    parent->children[i + 1] = z;

    for (int j = parent->n - 1; j >= i; j--)
        parent->keys[j + 1] = parent->keys[j];

    parent->keys[i] = y->keys[T - 1];
    parent->n++;
}

// Bir düğüme anahtar ekler (dolu değilse)
void insertNonFull(BTreeNode *node, int key)
{
    int i = node->n - 1;

    if (node->isLeaf)
    {
        while (i >= 0 && key < node->keys[i])
        {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->n++;
    }
    else
    {
        while (i >= 0 && key < node->keys[i])
            i--;

        i++;

        if (node->children[i]->n == 2 * T - 1)
        {
            splitChild(node, i, node->children[i]);

            if (key > node->keys[i])
                i++;
        }
        insertNonFull(node->children[i], key);
    }
}

// B-Tree'ye anahtar ekler
void insert(BTreeNode **rootRef, int key)
{
    BTreeNode *root = *rootRef;

    if (root->n == 2 * T - 1)
    {
        BTreeNode *s = createNode(false);
        s->children[0] = root;
        splitChild(s, 0, root);

        int i = 0;
        if (s->keys[0] < key)
            i++;
        insertNonFull(s->children[i], key);

        *rootRef = s;
    }
    else
    {
        insertNonFull(root, key);
    }
}

// Ağacı ekrana basar
void printTree(BTreeNode *node, int depth)
{
    int i;
    for (i = 0; i < node->n; i++)
    {
        if (!node->isLeaf)
            printTree(node->children[i], depth + 1);
        for (int j = 0; j < depth; j++)
            printf("    ");
        printf("%d\n", node->keys[i]);
    }
    if (!node->isLeaf)
        printTree(node->children[i], depth + 1);
}

int findKeyIndex(BTreeNode *node, int key)
{
    int idx = 0;
    while (idx < node->n && node->keys[idx] < key)
        idx++;
    return idx;
}

int findMax(BTreeNode *node)
{
    BTreeNode *current = node;
    while (!current->isLeaf)
    {
        current = current->children[current->n];
    }
    return current->keys[current->n - 1];
}

BTreeNode *findParent(BTreeNode *node, BTreeNode *child)
{
    if (node == NULL || child == NULL || node == child)
    {
        return NULL;
    }

    BTreeNode *current = node;
    while (current != NULL && !current->isLeaf)
    {
        for (int i = 0; i < current->n + 1; i++) // current->n + 1'e kadar kontrol etmeliyiz
        {
            if (current->children[i] == child)
            {
                return current;
            }
            else{
                current = current->children[i];
            }
        }
    }
    return NULL;
}

int findPredecessor(BTreeNode *root, int key)
{
    BTreeNode *node = searchNode(root, key);
    if (node == NULL)
    {
        printf("Key %d not found in the tree.\n", key);
        return -1;
    }

    int idx = findKeyIndex(node, key);

    if (!node->isLeaf)
    {
        // Sol alt ağacın en büyük elemanını bul
        return findMax(node->children[idx]);
    }
    else
    {
        // Yaprak düğümdeyiz
        if (idx > 0)
        {
            return node->keys[idx - 1];
        }
        else
        {
            // En soldaki anahtar, ebeveynde veya daha yukarıda bir öncül olabilir
            BTreeNode *current = node;
            BTreeNode *parent = findParent(root, current);

            while (parent != NULL)
            {
                int parentIdx = findKeyIndex(parent, key);
                if (parentIdx > 0)
                {
                    return parent->keys[parentIdx - 1];
                }
                else
                {
                    key = parent->keys[0]; // Ebeveynin ilk key'i ile devam et
                    current = parent;
                    parent = findParent(root, current);
                }
            }
            printf("No predecessor found for %d.\n", key);
            return -1;
        }
    }
}

int main()
{
    BTreeNode *root = createNode(true);

    insert(&root, 22);
    insert(&root, 1);
    insert(&root, 87);
    insert(&root, 6);
    insert(&root, 36);
    insert(&root, 8);
    insert(&root, 47);
    insert(&root, 11);
    insert(&root, 45);
    insert(&root, 3);
    insert(&root, 2);
    insert(&root, 35); // 36'nın soluna bir değer ekledim

    printf("B-Tree:\n");
    printTree(root, 0);

    int pred = findPredecessor(root, 36);
    if (pred != -1)
        printf("Predecessor of 36 is %d\n", pred);

    // Belleği serbest bırak (Önemli!)
    // Ağacı dolaşarak tüm düğümleri serbest bırakmanız gerekir.  Basitlik adına burada atlanmıştır.
    return 0;
}

    return 0;
}
