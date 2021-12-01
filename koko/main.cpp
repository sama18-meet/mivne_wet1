#include <iostream>
#include "avl.h"
#include "Player.h"
#include "Group.h"
#include "PlayersManager.h"

void printIntArray(int* intArray, int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << intArray[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    PlayersManager* pm = new PlayersManager();
    pm->addGroup(1);
    pm->addGroup(2);
    pm->addGroup(3);
    /*
    pm->addPlayer(1, 1, 110);
    pm->addPlayer(2, 1, 220);
    pm->addPlayer(3, 2, 330);
     */
    //pm->print();
    int** playersArr = new int*;
    int* numPlayers = new int;
    std::cout << "im here\n";
    pm->getAllPlayersByLvl(-1, playersArr, numPlayers);
    printIntArray(*playersArr, *numPlayers);
    return 0;
}