//delete
// Transplant fonksiyonu: Bir düğümün yerine başka bir düğüm yerleştirir
void transplant(Node** root, Node* u, Node* v) {
    if (u->parent == NULL) {  // Eğer u kökse, root'u v'ye değiştir
        *root = v;
    }
    else if (u == u->parent->left) {  // Eğer u, ebeveyninin sol çocuğuyse
        u->parent->left = v;
    }
    else {  // Eğer u, ebeveyninin sağ çocuğuyse
        u->parent->right = v;
    }

    if (v != NULL) {
        v->parent = u->parent;  // v'nin ebeveynini u'nun ebeveyni yap
    }
}

// En küçük değeri bulan fonksiyon (in-order successor)
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

// Düğüm silme fonksiyonu (Transplant kullanarak)
Node* delete(Node* root, int key) {
    Node* nodeToDelete = search(root, key);
    if (nodeToDelete == NULL) {
        printf("Node not found!\n");
        return root;
    }

    // 1. Durum: Düğümün hiç çocuğu yok
    if (nodeToDelete->left == NULL && nodeToDelete->right == NULL) {
        transplant(&root, nodeToDelete, NULL);  // Düğümü doğrudan sil
    }
    // 2. Durum: Düğümün bir çocuğu var
    else if (nodeToDelete->left == NULL) {
        transplant(&root, nodeToDelete, nodeToDelete->right);  // Sağ çocuğu ile değiştir
    }
    else if (nodeToDelete->right == NULL) {
        transplant(&root, nodeToDelete, nodeToDelete->left);  // Sol çocuğu ile değiştir
    }
    // 3. Durum: Düğümün iki çocuğu var
    else {
        // In-order successor'ü bul
        Node* successor = minValueNode(nodeToDelete->right);
        // Eğer successor, nodeToDelete'nin sağ çocuğuyse, doğrudan transplant yap
        if (successor->parent != nodeToDelete) {
            transplant(&root, successor, successor->right);  // Successor'un sağ çocuğunu al
            successor->right = nodeToDelete->right;
            successor->right->parent = successor;
        }
        // Successor'u nodeToDelete'nin yerine yerleştir
        transplant(&root, nodeToDelete, successor);
        successor->left = nodeToDelete->left;
        successor->left->parent = successor;
    }

    free(nodeToDelete);  // Silinen düğümü serbest bırak
    return root;
}

//insert işlemi
Node* insert(Node* root, int key) {
    // Eğer ağaç boşsa, yeni düğüm oluşturulur
    if (root == NULL) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->key = key;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    // Eğer key, root'un key'inden küçükse, sol alt ağaca ekle
    if (key < root->key) {
        root->left = insert(root->left, key);
    }
    // Eğer key, root'un key'inden büyükse, sağ alt ağaca ekle
    else if (key > root->key) {
        root->right = insert(root->right, key);
    }

    return root;
}
