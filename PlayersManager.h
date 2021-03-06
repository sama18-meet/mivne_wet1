#ifndef _PLAYERSMANAGER_H
#define _PLAYERSMANAGER_H


class PlayersManager {
private:
    AVL<int, Group*>* groups;
    AVL<int, Group*>* nonEmptyGroups;
    AVL<const Vec2D*, Player*>* playersByLvl;
    AVL<int, Player*>* playersById;
    Player* highest;

public:
    PlayersManager();
    ~PlayersManager();
    PlayersManager(const PlayersManager&) = delete;
    PlayersManager& operator=(const PlayersManager&) = delete;
    bool addGroup(int groupId); // false if groupId already exists
    bool addPlayer(int playerId, int groupId, int lvl);
    bool removePlayer(int playerId);
    bool replaceGroup(int groupId, int replacementId);
    bool increaseLevel(int playerId, int lvlIncrease);
    bool getHighestLvl(int groupId, int playerId);
    bool getAllPlayersByLvl(int groupId, int** playersArr, int* numPlayers);
    bool getGroupsHighestLvl(int numGroups, int** playersArr);
};


#endif // _PLAYERSMANAGER_H
