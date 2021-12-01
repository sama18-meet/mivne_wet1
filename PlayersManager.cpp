#include "PlayersManager.h"


PlayersManager::PlayersManager() : highest(nullptr) {
    groups = new AVL<int, Group*>();
    nonEmptyGroups = new AVL<int, Group*>();
    playersByLvl = new AVL<const Vec2D*, Player*>();
    playersById = new AVL<int, Player*>();
}


bool PlayersManager::addGroup(int groupId) {
    Group* g = new Group(groupId);
    bool success = groups->insert(groupId);
    if (!success) {
        delete g;
    }
    return success;
}
