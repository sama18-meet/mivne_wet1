#ifndef _AVL_H
#define _AVL_H

#include <iostream>
#include <cmath>

#define ALL_NODES -1

template <class K, class T>
class AVL {
private:
    struct Node {
        K key;
        T data;
        struct Node* left;
        struct Node* right;
        int height;
        Node(K key, T data):
                key(key), data(data), left(nullptr), right(nullptr), height(0) {};
        ~Node() = default;
        Node& operator=(const Node&) = default;
    };
    Node* root;
    int size;

private:
    int getBf(Node* node) const;
    Node* findInSubtree(Node* node, const K& key) const;
    Node* insertInSubtree(Node* node, const K& key, const T& data, bool* success);
    Node* fixBalance(Node* node);
    Node* rollRight(Node* B);
    Node* rollLeft(Node* A);
    Node* LL(Node* C);
    Node* LR(Node* C);
    Node* RL(Node* C);
    Node* RR(Node* C);
    Node* removeFromSubtree(Node* node, K key, bool* success);
    template <class function, class param>
    void applyInorderInternal(Node* node, function func, param p, int* done_nodes, int num_nodes);
    template <class function, class param>
    void applyInorderOnKey(function func, param p, int num_nodes);
    template <class function, class param>
    void applyInorderOnKeyInternal(Node* node, function func, param p, int* done_nodes, int num_nodes);
    static void mergeSortedArrays(int size1, int size2, K* keys1, T* data1, K* keys2, T* data, K* keysMerged, T* dataMerged);
    Node* buildAVLFromArray(int n, K* keyArr, T* dataArr);
    template <class arrType>
    static void insertInArray(arrType* arr, arrType element, int index);
    void deleteSubtree(Node*);
    Node* getNextInInorder(Node* node);
    Node* getSmallestDescendant(Node* node);
    Node* getMaxInSubtree(Node* root) const;
    void switchNodes(Node* node, Node* new_node);
    int getHeight(Node* node) const;
    void updateHeight(Node* node);


public:
    AVL();
    AVL(AVL<K,T>* avl1, AVL<K,T>* avl2); // merge constructor
    AVL(const AVL&) = delete;
    AVL& operator=(const AVL&) = default; // shallow!
    ~AVL();
    T get(const K& key, T notFoundValue) const;
    bool insert(const K& key, T data);
    bool remove(K key);
    template <class function, class param>
    void applyInorder(function func, param p, int num_nodes);
    int getSize() const;
    T getMax() const;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// C'tor & D'tor ///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class K, class T>
AVL<K, T>::AVL() :root(nullptr), size(0) {}

template <class K, class T>
AVL<K, T>::~AVL() {
    deleteSubtree(root);

}

template <class K, class T>
void AVL<K,T>::deleteSubtree(Node *n) {
    if (n == nullptr) {
        return;
    }
    deleteSubtree(n->left);
    deleteSubtree(n->right);
    delete n;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// NODE PROPERTIES//////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class K, class T>
int AVL<K, T>::getHeight(Node* node) const {
    if (node == nullptr) {
        return -1;
    }
    return (node->height);
}

template <class K, class T>
void AVL<K, T>::updateHeight(Node* node) {
    if (node == nullptr) {
        return;
    }
    node->height = fmax(getHeight(node->right), getHeight(node->left)) + 1;
}

template <class K, class T>
int AVL<K,T>::getBf(Node* node) const {
    if (node == nullptr) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// INSERT //////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


template <class K, class T>
typename AVL<K,T>::Node* AVL<K,T>::rollRight(Node* B) {
    Node* A = B->left;
    B->left = A->right;
    A->right = B;
    updateHeight(B);
    updateHeight(A);
    return A;
}

template <class K, class T>
typename AVL<K,T>::Node* AVL<K,T>::rollLeft(Node* A) {
    Node* B = A->right;
    A->right = B->left;
    B->left = A;
    updateHeight(A);
    updateHeight(B);
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
typename AVL<K,T>::Node* AVL<K,T>::fixBalance(Node* node) {
    int bf_node = getBf(node);
    int bf_right = getBf(node->right);
    int bf_left = getBf(node->left);
    if (bf_node == 2) {
        if (bf_left >= 0) {
            return LL(node);
        }
        else {
            return LR(node);
        }
    }
    else {
        if (bf_right <= 0) {
            return RR(node);
        }
        else {
            return RL(node);
        }
    }
}

template <class K, class T>
bool AVL<K,T>::insert(const K& key, T data) {
    bool success = true;
    root = insertInSubtree(root, key, data, &success);
    return success;
}

template <class K, class T>
// insert node into subtree and return the head of the subtree after insertion
typename AVL<K,T>::Node* AVL<K,T>::insertInSubtree(Node* node, const K& key, const T& data, bool* success) {
    if (node == nullptr) {
        this->size += 1;
        Node* n = new Node(key, data);
        *success = true;
        return n;
    }
    if (key == node->key) {
        *success = false;
        return node;
    }
    if (key < node->key) {
        node->left = insertInSubtree(node->left, key, data, success);
    }
    else if (key > node->key) {
        node->right = insertInSubtree(node->right, key, data, success);
    }
    updateHeight(node);
    int bf = getBf(node);
    if (bf >= 2 || bf <= -2) {
        return fixBalance(node);
    }
    return node;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// FIND ////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class K, class T>
T AVL<K,T>::get(const K& key, T notFoundValue) const {
    Node* n = findInSubtree(root, key);
    if (n==nullptr) {
        return notFoundValue;
    }
    return n->data;
}

template <class K, class T>
typename AVL<K,T>::Node* AVL<K,T>::findInSubtree(Node* node, const K& key) const {
    if (node == nullptr) {
        return nullptr;
    }
    if (node->key == key) {
        return node;
    }
    if (key < node->key) {
        return findInSubtree(node->left, key);
    }
    else {
        return findInSubtree(node->right, key);
    }
}

template <class K, class T>
T AVL<K,T>::getMax() const {
    if (root==nullptr){
        return nullptr;
    }
    return getMaxInSubtree(root)->data;
}

template <class K, class T>
typename AVL<K,T>::Node* AVL<K,T>::getMaxInSubtree(Node* node) const {
    if (node->right == nullptr) {
        return node;
    }
    else {
        return getMaxInSubtree(node->right);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// REMOVE //////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class K, class T>
bool AVL<K,T>::remove(K key) {
    bool success;
    root = removeFromSubtree(root, key, &success);
    return success;
}

template <class K, class T>
typename AVL<K,T>::Node* AVL<K,T>::getSmallestDescendant(Node* node) {
    if (node->left == nullptr) {
        return node;
    }
    else {
        return getSmallestDescendant(node->left);
    }
}

template <class K, class T>
typename AVL<K,T>::Node* AVL<K,T>::getNextInInorder(Node* node) {
    node = node->right; //not empty because node has 2 children
    return getSmallestDescendant(node);
}

template <class K, class T>
//switches between key and dat of node and new_node
void AVL<K,T>:: switchNodes(Node* node, Node* new_node) {
    K node_key = node->key;
    T node_data = node->data;
    node->key = new_node->key;
    node->data = new_node->data;
    new_node->key = node_key;
    new_node->data = node_data;
}

template <class K, class T>
typename AVL<K,T>::Node* AVL<K,T>::removeFromSubtree(Node* node, K key, bool* success) {
    if (node == nullptr) {
        *success = false;
        return nullptr;
    }
    if (node->key == key) {
        if (node->right == nullptr && node->left == nullptr) {
            delete node;
            *success = true;
            size -= 1;
            return nullptr;
        }
        else if (node->right == nullptr && node->left != nullptr) {
            Node* new_node = node->left;
            delete node;
            *success = true;
            size -= 1;
            return new_node;
        }
        else if (node->right != nullptr && node->left == nullptr) {
            Node* new_node = node->right;
            delete node;
            *success = true;
            size -= 1;
            return new_node;
        }
        else { //node has two sons
            Node* low_node = getNextInInorder(node);
            switchNodes(node, low_node);
            node->right = removeFromSubtree(node->right, key, success);
            updateHeight(node->right);
            updateHeight(node);
            int bf = getBf(node);
            if (bf >= 2 || bf <= -2) {
                return fixBalance(node);
            }
            return node;
        }
    }
    if (key < node->key) {
        node->left = removeFromSubtree(node->left, key, success);
        updateHeight(node);
    }
    else {
        node->right = removeFromSubtree(node->right, key, success);
        updateHeight(node);
    }
    node->height = getHeight(node);
    int bf = getBf(node);
    if (bf >= 2 || bf <= -2) {
        return fixBalance(node);
    }
    return node;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// APPLY_INORDER ///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class K, class T>
template <class function, class param>
void AVL<K, T>::applyInorder(function func, param p, int num_nodes) {
    int done_nodes = 0;
    applyInorderInternal<function, param>(root, func, p, &done_nodes, num_nodes);
}

template <class K, class T>
template <class function, class param>
void AVL<K, T>::applyInorderOnKey(function func, param p, int num_nodes) {
    int done_nodes = 0;
    applyInorderOnKeyInternal<function, param>(root, func, p, &done_nodes, num_nodes);
}

template <class K, class T>
template <class function, class param>
void AVL<K, T>::applyInorderInternal(Node* node, function func, param p, int* done_nodes, int num_nodes) {
    if (node == nullptr) {
        return;
    }
    applyInorderInternal(node->left, func, p, done_nodes, num_nodes);
    if (num_nodes == ALL_NODES || *done_nodes < num_nodes) {
        func(p, node->data, *done_nodes);
        (*done_nodes)++;
    }
    applyInorderInternal(node->right, func, p, done_nodes, num_nodes);
}

template <class K, class T>
template <class function, class param>
void AVL<K, T>::applyInorderOnKeyInternal(Node* node, function func, param p, int* done_nodes, int num_nodes) {
    if (node == nullptr || (num_nodes!=ALL_NODES && *done_nodes > num_nodes)) {
        return;
    }
    applyInorderOnKeyInternal(node->left, func, p, done_nodes, num_nodes);
    func(p, node->key, *done_nodes);
    (*done_nodes)++;
    applyInorderOnKeyInternal(node->right, func, p, done_nodes, num_nodes);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// BUILD_AVL ///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


template <class K, class T>
typename AVL<K,T>::Node* AVL<K,T>::buildAVLFromArray(int tree_size, K* keyArr, T* dataArr) {
    if (tree_size <= 0) {
        return nullptr;
    }
    int full_rows = log2(tree_size+1); // rounds down
    int remainder = tree_size + 1 - pow(2,full_rows); // number of nodes in last row
    int r1, r2; //
    int last_row_size = pow(2,full_rows);
    if (remainder <= last_row_size/2) {
        r1 = remainder;
        r2 = 0;
    }
    else {
        r1 = last_row_size/2;
        r2 = remainder - r1;
    }
    int left_size = pow(2,(full_rows-1)) - 1 + r1;
    int right_size = pow(2,(full_rows-1)) - 1 + r2;
    K* leftKeyArr = keyArr;
    T* leftDataArr = dataArr;
    K* rightKeyArr = keyArr+left_size + 1;
    T* rightDataArr = dataArr+left_size + 1;
    K currentKey = keyArr[left_size];
    T currentData = dataArr[left_size];
    Node* n = new Node(currentKey, currentData);
    n->left = buildAVLFromArray(left_size, leftKeyArr, leftDataArr);
    n->right = buildAVLFromArray(right_size, rightKeyArr, rightDataArr);
    n->height = std::max(getHeight(n->left), getHeight(n->right)) + 1;
    return n;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// MERGE ///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class K, class T>
int AVL<K,T>::getSize() const {
    return this->size;
}

template <class K, class T>
template <class arrType>
void AVL<K,T>::insertInArray(arrType* arr, arrType element, int index) {
    arr[index] = element;
}

template <class K, class T>
void AVL<K,T>::mergeSortedArrays(int size1, int size2, K* keys1, T* data1, K* keys2, T* data2,
                                 K* keysMerged, T* dataMerged) {
    int curr1 = 0;
    int curr2 = 0;
    int currI = 0;
    while (curr1 < size1 && curr2 < size2) {
        if (keys1[curr1] < keys2[curr2]) {
            keysMerged[currI] = keys1[curr1];
            dataMerged[currI] = data1[curr1];
            curr1++;
        } else {
            keysMerged[currI] = keys2[curr2];
            dataMerged[currI] = data2[curr2];
            curr2++;
        }
        currI++;
    }
    while (curr1 < size1) {
        keysMerged[currI] = keys1[curr1];
        dataMerged[currI] = data1[curr1];
        currI++;
        curr1++;
    }
    while (curr2 < size2) {
        keysMerged[currI] = keys2[curr2];
        dataMerged[currI] = data2[curr2];
        currI++;
        curr2++;
    }
}

template <class K, class T>
// notice that this method does not delete the two old avls!
AVL<K,T>::AVL(AVL<K,T>* avl1, AVL<K,T>* avl2) {
    int n1 = avl1->getSize();
    int n2 = avl2->getSize();
    T* dataArray1 = new T[n1];
    T* dataArray2 = new T[n2];
    avl1->applyInorder(insertInArray<T>, dataArray1, ALL_NODES);
    avl2->applyInorder(insertInArray<T>, dataArray2, ALL_NODES);
    K* keyArray1 = new K[n1];
    K* keyArray2 = new K[n2];
    avl1->applyInorderOnKey(insertInArray<K>, keyArray1, ALL_NODES);
    avl2->applyInorderOnKey(insertInArray<K>, keyArray2, ALL_NODES);
    T* dataMerged = new T[n1+ n2];
    K* keysMerged = new K[n1+n2];
    mergeSortedArrays(n1, n2, keyArray1, dataArray1, keyArray2, dataArray2, keysMerged, dataMerged);
    this->size = n1+n2;
    root = buildAVLFromArray(size, keysMerged, dataMerged);
    delete[] dataArray1;
    delete[] dataArray2;
    delete[] keyArray1;
    delete[] keyArray2;
    delete[] dataMerged;
    delete[] keysMerged;
}

#endif // _AVL_H
