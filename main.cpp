#include <iostream>
#include "avl.h"
#include "Player.h"
/*
void print_int(int x, int p, int d) {
    std::cout << p << "\n";
}

int main() {
    AVL<int, int>* pm1 = new AVL<int, int>();
    for (int i = 0; i < 10; i+=2) {
        pm1->insert(i, i);
    }
    pm1->printBT();
    std::cout << "__________" << std::endl;
    AVL<int, int>* pm2 = new AVL<int, int>();
    for (int i = 1; i < 10; i+=2) {
        pm2->insert(i, i);
    }
    pm2->printBT();
    std::cout << "__________" << std::endl;
    AVL<int , int>* pm3 = new AVL<int , int>(pm1, pm2);

    pm3->printBT();
    std::cout << "__________" << std::endl;

    std::cout << "getting 5: " << pm3->get(5, -1) << std::endl;
    std::cout << "getting 17: " << pm3->get(17, -1) << std::endl;
    std::cout << "getting size 1 : " << pm1->getSize() << std::endl;
    std::cout << "getting size 2 : " << pm2->getSize() << std::endl;
    std::cout << "getting size 3 : " << pm3->getSize() << std::endl;

    pm3->applyInorder(print_int, 0);
    return 0;
}
*/

void print_player_level(int x, Player* p, int d) {
    std::cout << "player id: " << p->getId() << ". lvl: " << p->getLvl() << "\n";
}

int main() {
    AVL<int, Player*>* pm1 = new AVL<int, Player*>();
    for (int i = 0; i < 8; i+=2) {
        Player* p = new Player(i, i*2, nullptr);
        pm1->insert(i, p);
    }
    pm1->printBT();
    AVL<int , Player*>* pm2 = new AVL<int, Player*>();
    for (int i = 1; i < 8; i+=2) {
        Player* p = new Player(i, i*2, nullptr);
        pm2->insert(i, p);
    }
    AVL<int , Player*>* pm3 = new AVL<int , Player*>(pm1, pm2);

    pm2->printBT();

    //pm1.applyInorder(print_player_level, 0);
    return 0;
}

