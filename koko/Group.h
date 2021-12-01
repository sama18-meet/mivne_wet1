#ifndef _GROUP_H
#define _GROUP_H

#include "avl.h"
class Player;
class Vec2D;

class Group {
private:
    int id;
    AVL<const Vec2D*, Player*>* players;
    Player* highest;
public:
    Group(int id);
    ~Group() = default;
    Group(const Group&) = delete;
    Group& operator=(const Group&) = delete;
    int getId() const;
    bool addPlayer(Player*);
    bool removePlayer(Player*);
    void operator<<(Group*); // eat
    Player* getHighest() const;
    static void print(int, Group*, int);
    void updateHighestPlayer();
    int getNumOfPlayers() const;
    template <class function, class param>
    void applyInorderPlayers(function func, param p);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// applyInorder ////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class function, class param>
void Group::applyInorderPlayers(function func, param p) {
    players->applyInorder(func, p, ALL_NODES);
}


#endif // _GROUP_H
