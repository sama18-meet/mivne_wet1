#ifndef _AVL_H
#define _AVL_H

#include <cmath>
#include <assert.h>


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
        void update(K new_key, T new_data) {key = new_key; data = new_data;};
    };
    Node* root;
    int size;

private:
    int get_bf(Node* root);
    int get_height(Node* root);
    Node* find_in_subtree(Node* root, K key);
    Node* insert_in_subtree(Node* root, K key, T data);
    Node* fix_balance(Node* root);
    Node* rollRight(Node* B);
    Node* rollLeft(Node* A);
    Node* LL(Node* C);
    Node* LR(Node* C);
    Node* RL(Node* C);
    Node* RR(Node* C);
    Node* remove_from_subtree(Node* root, K key);
    template <class function, class param>
    void apply_inorder_internal(Node* root, function func, param p, int done_nodes);
    template <class function, class param>
    void apply_inorder_on_node_internal(Node* root, function func, param p, int done_nodes);
    static void mergeSortedArrays(int size1, int size2, K* keys1, T* data1, K* keys2, T* data, K* keysMerged, T* dataMerged);
    static AVL<K,T> buildAVLInternal(int size, K* keyArr, T* dataArr);
    template <class arrType>
    static void insertDataInArray(arrType* arr, T element, int index);
    template <class arrType>
    static void insertKeyInArray(arrType* arr, Node* node, int index);
    static AVL<K,T> buildAVLFromArray(int size, K* keyArr, T* dataArr);

public:
    AVL();
    ~AVL();
    AVL(const AVL&) = delete;
    AVL& operator=(const AVL&) = delete;

    T get(K key);
    void insert(K key, T data);
    void remove(K key);
    template <class function, class param>
    void apply_inorder(function func, param p, bool on_node=false);
    int getSize() const;
    static AVL<K,T> mergeAVLs(AVL<K,T>& avl1, AVL<K,T>& avl2);

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
void AVL<K,T>::insert(K key, T data) {
    root = insert_in_subtree(root, key, data);
}


template <class K, class T>
// insert node into subtree and return the head of the subtree after insertion
typename AVL<K,T>::Node* AVL<K,T>::insert_in_subtree(Node* root, K key, T data) {
    if (root == nullptr) {
        this->size += 1;
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
T AVL<K,T>::get(K key) {
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
        this->size -= 1;
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// APPLY_INORDER ///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


template <class K, class T>
template <class function, class param>
void AVL<K, T>::apply_inorder(function func, param p, bool on_node) {
    if (on_node) {
        apply_inorder_on_node_internal(root, func, p, 0);
    }
    else {
        apply_inorder_internal(root, func, p, 0);
    }
}

template <class K, class T>
template <class function, class param>
void AVL<K, T>::apply_inorder_internal(Node* root, function func, param p, int done_nodes) {
    if (root == nullptr) {
        return;
    }
    apply_inorder_internal(root->left, func, done_nodes);
    func(p, root->data, done_nodes);
    done_nodes++;
    apply_inorder_internal(root->right, func, done_nodes);
}

template <class K, class T>
template <class function, class param>
void AVL<K, T>::apply_inorder_on_node_internal(Node* root, function func, param p, int done_nodes) {
    if (root == nullptr) {
        return;
    }
    apply_inorder_internal(root->left, func, done_nodes);
    func(p, root, done_nodes);
    done_nodes++;
    apply_inorder_internal(root->right, func, done_nodes);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// BUILD_EMPTY_AVL /////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class K, class T>
AVL<K,T> AVL<K,T>::buildAVLFromArray(int size, K* keyArr, T* dataArr) {
    AVL<K,T> avl = AVL<K,T>();
    avl.root = buildAVLInternal(size, keyArr, dataArr);
    avl.size = size;
}

template <class K, class T>
AVL<K,T> AVL<K,T>::buildAVLInternal(int size, K* keyArr, T* dataArr) {
    if (size <= 0) {
        return nullptr;
    }
    int full_rows = log2(size+1); // rounds down
    int remainder = size + 1 - 2^full_rows; // number of nodes in last row
    int r1, r2; //
    int last_row_size = 2^full_rows;
    if (remainder <= last_row_size/2) {
        r1 = remainder;
        r2 = 0;
    }
    else {
        assert(remainder < last_row_size);
        r1 = last_row_size/2;
        r2 = remainder - r1;
    }
    int left_size = 2^(full_rows-1) + r1;
    int right_size = 2^(full_rows-1) + r2;
    K* leftKeyArr = keyArr;
    T* leftDataArr = dataArr;
    K* rightKeyArr = keyArr+left_size + 1;
    T* rightDataArr = dataArr+left_size + 1;
    K currentKey = keyArr[left_size];
    T currentData = dataArr[left_size];
    Node n = Node(K(), T()); // this assumes a default constructor for both T and K
    n->left = buildAVLInternal(left_size, leftKeyArr, leftDataArr);
    n->right = buildAVLInternal(right_size, rightKeyArr, rightDataArr);
    n->height = max(n->left->height, n->right->height) + 1;
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
void AVL<K,T>::insertDataInArray(arrType* arr, T element, int index) {
    arr[index] = element;
}

template <class K, class T>
template <class arrType>
void AVL<K,T>::insertKeyInArray(arrType* arr, Node* node, int index) {
    arr[index] = node->key;
}

template <class K, class T>
void AVL<K,T>::mergeSortedArrays(int size1, int size2, K* keys1, T* data1, K* keys2, T* data2,
                                K* keysMerged, T* dataMerged) {
    int curr1 = 0;
    int curr2 = 0;
    int currI = 0;
    while (curr1 + curr2 < size1+size2) {
        if (keys1[curr1] <= keys2[curr2]) {
            keysMerged[currI] = keys1[curr1];
            dataMerged[currI] = data1[curr1];
        }
        else {
            keysMerged[currI] = keys2[curr2];
            dataMerged[currI] = data2[curr2];
        }
    }
}


template <class K, class T>
AVL<K,T> AVL<K,T>::mergeAVLs(AVL<K,T>& avl1, AVL<K,T>& avl2) {
    int n1 = avl1.getSize();
    int n2 = avl2.getSize();
    T* dataArray1 = new T[n1];
    T* dataArray2 = new T[n2];
    avl1.apply_inorder(insertDataInArray, dataArray1, true);
    avl2.apply_inorder(insertDataInArray, dataArray2, true);
    K* keyArray1 = new K[n1];
    K* keyArray2 = new K[n2];
    avl1.apply_inorder(insertKeyInArray, keyArray1, true);
    avl2.apply_inorder(insertKeyInArray, keyArray2, true);
    T* dataMerged = new T[n1+ n2];
    K* keysMerged = new K[n1+n2];
    mergeSortedArrays(n1, n2, keyArray1, dataArray1, keyArray2, dataArray2, keysMerged, dataMerged);
    AVL<K,T> newAvl = buildAVLFromArray(n1+n2, keysMerged, dataMerged);
    return newAvl;
}

#endif // _AVL_H
