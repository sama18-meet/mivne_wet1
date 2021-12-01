#include <iostream>
#include "avl.h"
#include "Player.h"
#include "Group.h"
#include "PlayersManager.h"

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
    /*
    Group* g1 = new Group(1);
    for (int i = 0; i < 8; i+=2) {
        Player* p = new Player(i, i*2);
        g1->addPlayer(p);
    }
    g1->print();

    Group* g2 = new Group(2);
    for (int i = 10; i < 18; i+=2) {
        Player* p = new Player(i, i*2);
        g2->addPlayer(p);
    }
    Player* p = new Player(20, 20*2);
    g2->addPlayer(p);
    g2->print();

    *g1 << g2;
    g1->print();
    g2->print();
    g2->removePlayer(p);
    g2->print();
    delete g2;
     */

    PlayersManager* pm = new PlayersManager();
    pm->addGroup(1);
    pm->addGroup(2);

    pm->addPlayer(1, 1, 110);
    pm->print();
    pm->addPlayer(2, 1, 220);
    pm->print();
    pm->addPlayer(3, 2, 330);
    pm->print();
    pm->replaceGroup(1, 2);


/*
    AVL<int, Player*>* pm1 = new AVL<int, Player*>();
    for (int i = 0; i < 8; i+=2) {
        Player* p = new Player(i, i*2);
        pm1->insert(i, p);
    }
    pm1->printBT();
    AVL<int , Player*>* pm2 = new AVL<int, Player*>();
    for (int i = 1; i < 8; i+=2) {
        Player* p = new Player(i, i*2);
        pm2->insert(i, p);
    }
    AVL<int , Player*>* pm3 = new AVL<int , Player*>(pm1, pm2);

    pm2->printBT();

    //pm1.applyInorder(print_player_level, 0);
    */
    return 0;
}

