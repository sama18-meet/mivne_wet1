#ifndef _AVL_H
#define _AVL_H

#include <iostream>
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
    };
    Node* root;
    int size;

private:
    int get_bf(Node* root);
    Node* find_in_subtree(Node* root, const K& key);
    Node* insert_in_subtree(Node* root, const K& key, const T& data, bool* success);
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
    void apply_inorder_on_key(function func, param p);
    template <class function, class param>
    void apply_inorder_on_key_internal(Node* root, function func, param p, int done_nodes);
    static void mergeSortedArrays(int size1, int size2, K* keys1, T* data1, K* keys2, T* data, K* keysMerged, T* dataMerged);
    Node* buildAVLInternalFromArr(int size, K* keyArr, T* dataArr);
    template <class arrType>
    static void insertInArray(arrType* arr, arrType element, int index);
    void deleteSubtree(Node*);
    void printBT(const std::string& prefix, const Node* node, bool isLeft);


public:
    Node* get_smallest_bigger_son(Node* root); //return to private when done debugging
    Node* get_smallest_son(Node* root); //return to private when done debugging
    void remove_less_then_two_sons(Node* root, Node* parent); //return to private when done debugging
    Node* get_parent(K key); //return to private when done debugging
    Node* get_parent_in_subtree(Node* root, K key); //return to private when done debugging
    bool is_key_immediate_kid(Node* root, K key); //return to private when done debugging
    bool has_right_son(Node* root); //return to private when done debugging
    bool has_left_son(Node* root); //return to private when done debugging
    Node* get_only_child(Node* root); //return to private when done debugging
    void switch_nodes(Node* root, Node* new_root); //return to private when done debugging
    int get_height(Node* root); //return to private when done debugging
    int get_height_by_key(K key); //return to private when done debugging
    Node* get_node(K key); //return to private when done debugging
    void update_height(Node* root); //return to private when done debugging


    AVL();
    AVL(const AVL<K,T>& avl1, const AVL<K,T>& avl2); // merge constructor
    AVL(const AVL&) = delete;
    AVL& operator=(const AVL&) = default; // shallow!
    ~AVL();
    T get(const K& key);
    bool insert(const K& key, T data);
    void remove(K key);
    template <class function, class param>
    void apply_inorder(function func, param p);
    int getSize() const;

    void printBT();


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
int AVL<K, T>::get_height(Node* root) {
    if (root == nullptr) {
        return -1;
    }
    return (root->height);
}

template <class K, class T>
int AVL<K, T>::get_height_by_key(K key) {
    Node* node = get_node(key);
    return get_height(node);
}

template <class K, class T>
void AVL<K, T>::update_height(Node* root) {
    root->height = fmax(get_height(root->right),get_height(root->left)) + 1;
}

template <class K, class T>
int AVL<K,T>::get_bf(Node* root) {
    if (root == nullptr) {
        return 0;
    }
    return get_height(root->left) - get_height(root->right);
}

template <class K, class T>
typename AVL<K,T>::Node* AVL<K,T>::get_parent(K key) {
    Node* parent = get_parent_in_subtree(root, key);
    std::cout << "key: " << key << " parent: " << parent->key << "\n"; //debug
    return parent;
}

template <class K, class T>
typename AVL<K,T>::Node* AVL<K,T>::get_parent_in_subtree(Node* root, K key) {
    if (root == nullptr) {
        return nullptr; //ket does not exist in tree
    }
    if (is_key_immediate_kid(root, key)) { //means he's the parent
        return root;
    }
    if (key < root->key) {
        return get_parent_in_subtree(root->left, key);
    }
    else {
        return get_parent_in_subtree(root->right, key);
    }
}

template <class K, class T>
bool AVL<K,T>::is_key_immediate_kid(Node* root, K key) {
    //decided to write function because if root has 1 child naive solution raises errors
    if (root->right != nullptr) {
        if (root->right->key == key) {return true;}
    }
    if (root->left != nullptr) {
        if (root->left->key == key) {return true;}
    }
    return false;
}

template <class K, class T>
bool AVL<K,T>::has_right_son(Node* root) {
    return root->right != nullptr;
}
template <class K, class T>
bool AVL<K,T>::has_left_son(Node* root) {
    return root->left != nullptr;
}

template <class K, class T>
typename AVL<K,T>::Node* AVL<K,T>::get_only_child(Node* root) {
    //use if root is known to have one or less children.
    //if has no children will return nullptr
    if (has_right_son(root)){
        return root->right;
    }
    else if (has_left_son(root)) {
        return root->left;
    }
    return nullptr;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// INSERT //////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


template <class K, class T>
typename AVL<K,T>::Node* AVL<K,T>::rollRight(Node* B) {
    Node* A = B->left;
    B->left = A->right;
    A->right = B;
    //A->height = get_height(A); //not needed
    B->height = get_height(B) - 2; //decreases by 2 after roll
    return A;
}

template <class K, class T>
typename AVL<K,T>::Node* AVL<K,T>::rollLeft(Node* A) {
    Node* B = A->right;
    A->right = B->left;
    B->left = A;
    A->height = get_height(A) - 2; //decreases by 2 after roll
    //B->height = get_height(B); //not needed
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
bool AVL<K,T>::insert(const K& key, T data) {
    bool success = true;
    root = insert_in_subtree(root, key, data, &success);
    return success;
}


template <class K, class T>
// insert node into subtree and return the head of the subtree after insertion
typename AVL<K,T>::Node* AVL<K,T>::insert_in_subtree(Node* root, const K& key, const T& data, bool* success) {
    if (root == nullptr) {
        this->size += 1;
        Node* n = new Node(key, data);
        *success = true;
        return n;
    }
    if (key == root->key) {
        root->data = data;
        *success = false;
        return root;
    }
    if (key < root->key) {
        root->left = insert_in_subtree(root->left, key, data, success);
    }
    else if (key > root->key) {
        root->right = insert_in_subtree(root->right, key, data, success);
    }
    update_height(root);
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
T AVL<K,T>::get(const K& key) {
    return find_in_subtree(root, key)->data;
}

template <class K, class T>
typename AVL<K,T>::Node* AVL<K,T>::get_node(K key) {
    return find_in_subtree(root, key);
}

template <class K, class T>
typename AVL<K,T>::Node* AVL<K,T>::find_in_subtree(Node* root, const K& key) {
    if (root == nullptr) {
        return nullptr;
    }
    if (root->key == key) {
        return root;
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
typename AVL<K,T>::Node* AVL<K,T>::get_smallest_son(Node* root) {
    if (root->left == nullptr) { //arrived at smallest son
        return root;
    }
    else {
        return get_smallest_son(root->left);
    }
}

template <class K, class T>
typename AVL<K,T>::Node* AVL<K,T>::get_smallest_bigger_son(Node* root) {
    root = root->right; //not empty because root has 2 children
    return get_smallest_son(root);
}

template <class K, class T>
void AVL<K,T>:: remove_less_then_two_sons(Node* root, Node* parent) {
    bool is_right_kid = (parent->right == root);
    Node* new_child = get_only_child(root);
    std::cout << "parent: " << parent->key << "\n"; //debug
    std::cout << "new_child: " << new_child << "\n"; //debug
    if (is_right_kid) {
        std::cout << "Right" << "\n"; //debug
        parent->right = new_child;
    }
    else {
        std::cout << "left" << "\n"; //debug
        parent->left = new_child;
    }
}

template <class K, class T>
void AVL<K,T>:: switch_nodes(Node* root, Node* new_root) {
    //switches between key and dat of root and new_root
    K root_key = root->key;
    T root_data = root->data;
    root->key = new_root->key;
    root->data = new_root->data;
    new_root->key = root_key;
    new_root->data = root_data;
}

template <class K, class T>
typename AVL<K,T>::Node* AVL<K,T>::remove_from_subtree(Node* root, K key) {
    if (root == nullptr) {
        return nullptr; //nothing to remove
    }
    if (root->key == key) {
        Node* new_root;
        Node* parent;
        if (has_right_son(root) && has_left_son(root)) {
            new_root = get_smallest_bigger_son(root); //son that will replace removed node
            parent = get_parent(new_root->key);
            switch_nodes(root, new_root);
        }
        else {
            new_root = root; //can remove requested node directly
            parent = get_parent(new_root->key);
        }
        remove_less_then_two_sons(new_root, parent);
        std::cout << "PRight: " << parent->right << " Pleft: " << parent->left << "\n"; //debug
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
void AVL<K, T>::apply_inorder(function func, param p) {
    apply_inorder_internal<function, param>(root, func, p, 0);
}

template <class K, class T>
template <class function, class param>
void AVL<K, T>::apply_inorder_on_key(function func, param p) {
    apply_inorder_on_key_internal<function, param>(root, func, p, 0);
}

template <class K, class T>
template <class function, class param>
void AVL<K, T>::apply_inorder_internal(Node* root, function func, param p, int done_nodes) {
    if (root == nullptr) {
        return;
    }
    apply_inorder_internal(root->left, func, p, done_nodes);
    func(p, root->data, done_nodes);
    done_nodes++;
    apply_inorder_internal(root->right, func, p, done_nodes);
}

template <class K, class T>
template <class function, class param>
void AVL<K, T>::apply_inorder_on_key_internal(Node* root, function func, param p, int done_nodes) {
    if (root == nullptr) {
        return;
    }
    apply_inorder_internal(root->left, func, p, done_nodes);
    func(p, root->key, done_nodes);
    done_nodes++;
    apply_inorder_internal(root->right, func, p, done_nodes);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// BUILD_AVL ///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


template <class K, class T>
typename AVL<K,T>::Node* AVL<K,T>::buildAVLInternalFromArr(int size, K* keyArr, T* dataArr) {
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
    Node n = Node(currentKey, currentData);
    n->left = buildAVLInternalFromArr(left_size, leftKeyArr, leftDataArr);
    n->right = buildAVLInternalFromArr(right_size, rightKeyArr, rightDataArr);
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
void AVL<K,T>::insertInArray(arrType* arr, arrType element, int index) {
    arr[index] = element;
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
// notice that this method does not delete the two old avls!
AVL<K,T>::AVL(const AVL<K,T>& avl1, const AVL<K,T>& avl2) {
    int n1 = avl1.getSize();
    int n2 = avl2.getSize();
    T* dataArray1 = new T[n1];
    T* dataArray2 = new T[n2];
    avl1.apply_inorder(insertInArray<T>, dataArray1);
    avl2.apply_inorder(insertInArray<T>, dataArray2);
    K* keyArray1 = new K[n1];
    K* keyArray2 = new K[n2];
    avl1.apply_inorder_on_key(insertInArray<K>, keyArray1);
    avl2.apply_inorder_on_key(insertInArray<K>, keyArray2);
    T* dataMerged = new T[n1+ n2];
    K* keysMerged = new K[n1+n2];
    mergeSortedArrays(n1, n2, keyArray1, dataArray1, keyArray2, dataArray2, keysMerged, dataMerged);
    size = n1+n2;
    root = buildAVLInternalFromArr(size, keysMerged, dataMerged);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class K, class T>
void AVL<K,T>::printBT(const std::string& prefix, const Node* node, bool isLeft)
{
    if( node != nullptr )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──" );

        // print the value of the node
        std::cout << node->data << std::endl;

        // enter the next tree level - left and right branch
        printBT( prefix + (isLeft ? "│   " : "    "), node->left, true);
        printBT( prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}

template <class K, class T>
void AVL<K,T>::printBT()
{
    printBT("", root, false);
}


#endif // _AVL_H
