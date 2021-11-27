#ifndef _AVL_H
#define _AVL_H

template <class K, class T>
class AVL {
private:
    struct Node {
        K key;
        T* data;
        struct Node* left;
        struct Node* right;
        int height;
        Node(K key, T* data):
                key(key), data(data), left(nullptr), right(nullptr), height(0) {};
        ~Node() = default;
    };
    Node* root;

private:
    int get_bf(Node* root);
    int get_height(Node* root);
    Node* find_in_subtree(Node* root, K key);
    Node* insert_in_subtree(Node* root, K key, T* data);
    Node* fix_balance(Node* root);
    Node* rollRight(Node* B);
    Node* rollLeft(Node* A);
    Node* LL(Node* C);
    Node* LR(Node* C);
    Node* RL(Node* C);
    Node* RR(Node* C);
    Node* remove_from_subtree(Node* root, K key);
    template <class function>
    void apply_inorder_internal(Node* root, function func);


        public:
    AVL();
    ~AVL();
    AVL(const AVL&) = delete;
    AVL& operator=(const AVL&) = delete;

    T* get(K key);
    void insert(K key, T* data);
    void remove(K key);
    template <class function>
    void apply_inorder(function func);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// C'tor & D'tor ///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class K, class T>
AVL<K, T>::AVL() :root(nullptr) {}

template <class K, class T>
AVL<K, T>::~AVL() {
    // apply inorder on remove
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// NODE PROPERTIES//////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class K, class T>
int AVL<K, T>::get_height(Node* root) {
    if (root == nullptr) {
        return -1;
    }
    return (root->height);
}

template <class K, class T>
int AVL<K,T>::get_bf(Node* root) {
    if (root == nullptr) {
        return 0;
    }
    return height(root->left) - height(root->right);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// INSERT //////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


template <class K, class T>
typename AVL<K,T>::Node* AVL<K,T>::rollRight(Node* B) {
    Node* A = B->left;
    B->left = A->right;
    A->right = B;
    A->height = get_height(A);
    B->height = het_height(B);
    return A;
}

template <class K, class T>
typename AVL<K,T>::Node* AVL<K,T>::rollLeft(Node* A) {
    Node* B = A->right;
    A->right = B->left;
    B->left = A;
    A->height = get_height(A);
    B->height = het_height(B);
    return B;
}

template <class K, class T>
typename AVL<K,T>::Node* AVL<K,T>::LL(Node* C) {
    return rollRight(C);
}

template <class K, class T>
typename AVL<K,T>::Node* AVL<K,T>::LR(Node* C) {
    C->left = rollLeft(C->left);
    return rollRight(C);
}

template <class K, class T>
typename AVL<K,T>::Node* AVL<K,T>::RL(Node* C) {
    C->right = rollRight(C->right);
    return rollLeft(C);
}

template <class K, class T>
typename AVL<K,T>::Node* AVL<K,T>::RR(Node* C) {
    return rollLeft(C);
}

template <class K, class T>
typename AVL<K,T>::Node* AVL<K,T>::fix_balance(Node* root) {
    assert(root != nullptr);
    int bf_root = get_bf(root);
    int bf_right = get_bf(root->right);
    int bf_left = get_bf(root->left);
    if (bf_root == 2) {
        if (bf_left >= 0) {
            return LL(root);
        }
        else {
            return LR(root);
        }
    }
    else {
        if (bf_right <= 0) {
            return RR(root);
        }
        else {
            return RL(root);
        }
    }
}


template <class K, class T>
void AVL<K,T>::insert(K key, T* data) {
    root = insert_in_subtree(root, key, data);
}


template <class K, class T>
// insert node into subtree and return the head of the subtree after insertion
typename AVL<K,T>::Node* AVL<K,T>::insert_in_subtree(Node* root, K key, T* data) {
    if (root == nullptr) {
        return Node(key, data);
    }
    if (key == root->key) {
        root->data = data;
        return root;
    }
    if (key < root->key) {
        root->left = insert_in_subtree(root->left, key, data);
    }
    else if (key > root->key) {
        root->right = insert_in_subtree(root->right, key, data);
    }
    root->height = get_height(root);
    int bf = get_bf(root);
    if (bf >= 2 || bf <= -2) {
        return fix_balance(root);
    }
    return root;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// FIND ////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class K, class T>
T* AVL<K,T>::
        get(K key) {
    return find_in_subtree(root, key);
}
template <class K, class T>
typename AVL<K,T>::Node* AVL<K,T>::find_in_subtree(Node* root, K key) {
    if (root == nullptr) {
        return nullptr;
    }
    if (root->key == key) {
        return root->data;
    }
    if (key < root->key) {
        return find_in_subtree(root->left, key);
    }
    else {
        return find_in_subtree(root->right, key);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// REMOVE //////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class K, class T>
void AVL<K,T>::remove(K key) {
    root = remove_from_subtree(root, key);
}

template <class K, class T>
// removes the node from subtree and returns the new root of the subtree
typename AVL<K,T>::Node* AVL<K,T>::remove_from_subtree(Node* root, K key) {
    if (root == nullptr) {
        return nullptr; //nothing to remove
    }
    if (root->key == key) {
        // destruct node
        return nullptr;
    }
    if (key < root->key) {
        root->left = remove_from_subtree(root->left, key);
    }
    else {
        root->right = remove_from_subtree(root->right, key);
    }
    root->height = get_height(root);
    int bf = get_bf(root);
    if (bf >= 2 || bf <= -2) {
        return fix_balance(root);
    }
    return root;
}

template <class K, class T, class function>
void AVL<K, T>::apply_inorder(function func) {
    apply_inorder_internal(root, func);
}

template <class K, class T, class function>
void AVL<K, T>::apply_inorder_internal(Node* root, function func) {
    if (root == nullptr) {
        return;
    }
    apply_inorder_internal(root->left, func);
    func(root);
    apply_inorder_internal(root->right, func);
}


#endif // _AVL_H
