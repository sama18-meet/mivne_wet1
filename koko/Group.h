#ifndef _GROUP_H
#define _GROUP_H

#include "avl.h"
class Player;
class Vec2D;

class Group {
private:
    int id;
    AVL<Vec2D, Player*>* players;
    Player* highest;
public:
    Group(int id);
    ~Group();
    Group(const Group&) = delete;
    Group& operator=(const Group&) = delete;
    int getId() const;
    bool addPlayer(Player*);
    bool removePlayer(Player*);
    void insertAllPlayersOf(Group*);
    Player* getHighest() const;
    void updateHighestPlayer();
    int getNumOfPlayers() const;
    template <class function, class param>
    void applyInorderPlayers(function func, param p);
    static void deleteGroup(int redundant1, Group* groupToDelete, int redundant2);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// applyInorder ////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class function, class param>
void Group::applyInorderPlayers(function func, param p) {
    players->applyInorder(func, p, ALL_NODES);
}


#endif // _GROUP_H
