#include "PlayersManager.h"


PlayersManager::PlayersManager() : highest(nullptr) {
    groups = new AVL<int, Group*>();
    nonEmptyGroups = new AVL<int, Group*>();
    playersByLvl = new AVL<const Vec2D*, Player*>();
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
    std::cout << "highest: " << highest->getId();
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
    Player notFoundPlayer = Player(-1, -1);
    Player* p = playersById->get(playerId, &notFoundPlayer);
    if (p->getId() > 0) {
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
    highest = playersByLvl->getMax();
    return true;
}
