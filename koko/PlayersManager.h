#ifndef _PLAYERSMANAGER_H
#define _PLAYERSMANAGER_H
#include "Group.h"
#include "Player.h"
#include "avl.h"

class PlayersManager {
private:
    AVL<int, Group*>* groups;
    AVL<int, Group*>* nonEmptyGroups;
    AVL<Vec2D, Player*>* playersByLvl;
    AVL<int, Player*>* playersById;
    Player* highest;

private:
    void updateHighestPlayer();
    static void insertHighestPlayerIdInArray(int* arr, Group* g, int idx);
    static void reverseArray(int* playersArr, int size);
    static void insertPlayerIdInArray(int* arr, Player* p, int idx);

public:
    PlayersManager();
    ~PlayersManager();
    PlayersManager(const PlayersManager&) = delete;
    PlayersManager& operator=(const PlayersManager&) = delete;
    bool addGroup(int groupId);
    bool addPlayer(int playerId, int groupId, int lvl);
    bool removePlayer(int playerId);
    bool replaceGroup(int groupId, int replacementId);
    bool increaseLevel(int playerId, int lvlIncrease);
    bool getHighestLvl(int groupId, int* playerId);
    bool getAllPlayersByLvl(int groupId, int** playersArr, int* numPlayers);
    bool getGroupsHighestLvl(int numGroups, int** playersArr);
};


#endif // _PLAYERSMANAGER_H
