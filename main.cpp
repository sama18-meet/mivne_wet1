#include <iostream>
#include "avl.h"


void print_int(int p,int i, int d) {
    std::cout << i << "\n";
}

void print_integer_tree (AVL<int, double> tree) {
    tree.apply_inorder(print_int, 0);
}
int main() {
    AVL<int, double> PlayersManager;
    for (int i = 0; i < 7; ++i) {
        PlayersManager.insert(i, i+10);
    }
    for (int i = 2; i < 7; ++i) {
        PlayersManager.get_parent(i);
    }
    PlayersManager.get_parent(0);
    for (int i = 0; i < 7; ++i) {
        std::cout << "key: " << i << " height: " << PlayersManager.get_height_by_key(i) << "\n";
    }
    PlayersManager.apply_inorder(print_int, 0);
    return 0;
}
