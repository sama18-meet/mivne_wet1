#include "PlayersManager.h"


PlayersManager::PlayersManager() : highest(nullptr) {
    groups = new AVL<int, Group*>();
    nonEmptyGroups = new AVL<int, Group*>();
    playersByLvl = new AVL<Vec2D, Player*>();
    playersById = new AVL<int, Player*>();
}


void PlayersManager::print() {
    std::cout << "Printing players manager details:" << std::endl;
    std::cout << "groups: " << "\n";
    groups->printBT();
    std::cout << "nonEmptyGroups: " << "\n";
    nonEmptyGroups->printBT();
    std::cout << "playersByLvl: " << "\n";
    playersByLvl->printBT();
    std::cout << "playersById: " << "\n";
    playersById->printBT();
    std::cout << "highest: " << highest->getId() << std::endl;
    std::cout << "groups: " << std::endl;
    groups->applyInorder(Group::print, 1, -1);
    std::cout << "______________________________________________________" << std::endl;
}

bool PlayersManager::addGroup(int groupId) {
    assert(groupId > 0);
    if (groups->get(groupId, nullptr) == nullptr) {
        Group* g = new Group(groupId);
        bool success = groups->insert(groupId, g);
        assert(success == true);
        return success;
    }
    return false;
}

bool PlayersManager::removePlayer(int playerId) {
    Player* p = playersById->get(playerId, nullptr);
    if (p==nullptr) {
        return false;
    }
    p->getGroup()->removePlayer(p); // remove player from Players tree in his group
    p->getGroup()->updateHighestPlayer();
    nonEmptyGroups->remove(p->getId());
    playersById->remove(p->getId());
    playersByLvl->remove(p->getRankVec());
    updateHighestPlayer();
    delete p;
    return true;
}

void PlayersManager::updateHighestPlayer() {
    highest = playersByLvl->getMax();
}

bool PlayersManager::addPlayer(int playerId, int groupId, int lvl) {
    Player* p = playersById->get(playerId, nullptr);
    Group* g = groups->get(groupId, nullptr);
    if (p != nullptr || g == nullptr) {
        return false;
    }
    p = new Player(playerId, lvl);
    g->addPlayer(p);
    playersById->insert(playerId, p);
    playersByLvl->insert(p->getRankVec(), p);
    nonEmptyGroups->insert(groupId, g);
    highest = playersByLvl->getMax();
    g->updateHighestPlayer();
    return true;
}

bool PlayersManager::replaceGroup(int groupId, int replacementId) {
    Group* group = groups->get(groupId, nullptr);
    Group* repGroup = groups->get(replacementId, nullptr);
    if (group == nullptr || repGroup == nullptr) {
        return false;
    }
    *repGroup << group;

    delete group;
    assert(groups->remove(groupId));
    nonEmptyGroups->remove(groupId);
    if (repGroup->getNumOfPlayers() > 0) {
        nonEmptyGroups->insert(repGroup->getId(), repGroup);
    }
    return true;
}

bool PlayersManager::increaseLevel(int playerId, int lvlIncrease) {
    Player* p = playersById->get(playerId, nullptr);
    if (p == nullptr) {
        return false;
    }
    Group* g = p->getGroup();
    playersByLvl->remove(p->getRankVec());
    g->removePlayer(p);
    p->increaseLvl(lvlIncrease);
    playersByLvl->insert(p->getRankVec(), p);
    g->addPlayer(p);
    g->updateHighestPlayer();
    updateHighestPlayer();
    return true;
}

bool PlayersManager::getHighestLvl(int groupId, int* playerId) {
    if (groupId < 0) {
        int id = (highest==nullptr)? -1 : highest->getId();
        *playerId = id;
        return true;
    }
    else {
        Group* g = groups->get(groupId, nullptr);
        if (g==nullptr) {
            return false;
        }
        int id = (g->getHighest()==nullptr)? -1 : g->getHighest()->getId();
        *playerId = id;
        return true;
    }
}

void PlayersManager::insertHighestPlayerIdInArray(int* arr, Group* g, int idx) {
    Player* p = g->getHighest();
    arr[idx] = p->getId();
}

bool PlayersManager::getGroupsHighestLvl(int numGroups, int** playersArrPtr) {
    if (numGroups > nonEmptyGroups->getSize()) {
        return false;
    }
    int* playersArr = new int[numGroups];
    nonEmptyGroups->applyInorder(PlayersManager::insertHighestPlayerIdInArray, playersArr, numGroups);
    *playersArrPtr = playersArr;
    return true;
}

void PlayersManager::reverseArray(int *playersArr, int size) {
    if (size==0) {return;}
    int switch_var;
    for (int i = 0; i < size/2; i++) {
        switch_var = *(playersArr+i);
        *(playersArr+i) = *(playersArr+size-i-1);
        *(playersArr+size-i-1) = switch_var;
    }
}

void PlayersManager::insertPlayerIdInArray(int* arr, Player* p, int idx) {
    arr[idx] = p->getId();
}

bool PlayersManager::getAllPlayersByLvl(int groupId, int** playersArr, int* numPlayers) {
    if (groupId<0) {
        *numPlayers = playersByLvl->getSize();
        if (*numPlayers==0) {
            *playersArr = nullptr;
        }
        else {
            *playersArr = new int[*numPlayers];
            playersByLvl->applyInorder(PlayersManager::insertPlayerIdInArray, *playersArr, ALL_NODES);
        }
    }
    else {
        Group* g = groups->get(groupId, nullptr);
        if (g==nullptr) {
            return false;
        }
        *numPlayers = g->getNumOfPlayers();
        if (*numPlayers==0) {
            *playersArr = nullptr;
        }
        else {
            *playersArr = new int[*numPlayers];
            g->applyInorderPlayers(PlayersManager::insertPlayerIdInArray, *playersArr);
        }
    }
    if (*numPlayers > 0) {
        reverseArray(*playersArr, *numPlayers);
    }
    return true;
}
