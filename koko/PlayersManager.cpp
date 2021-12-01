#include "PlayersManager.h"


PlayersManager::PlayersManager() : highest(nullptr) {
    groups = new AVL<int, Group*>();
    nonEmptyGroups = new AVL<int, Group*>();
    playersByLvl = new AVL<const Vec2D*, Player*>();
    playersById = new AVL<int, Player*>();
}

bool PlayersManager::addGroup(int groupId) {
    Group* g = new Group(groupId);
    bool success = groups->insert(groupId, g);
    if (!success) {
        delete g;
    }
    return success;
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
