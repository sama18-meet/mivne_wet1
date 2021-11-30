#ifndef _GROUP_H
#define _GROUP_H

#include "avl.h"
class Player;
class Vec2D;

class Group {
private:
    int id;
    AVL<const Vec2D*, Player*> players;
    Player* highest;
public:
    Group(int id);
    ~Group() = default;
    Group(const Group&) = delete;
    Group& operator=(const Group&) = delete;
    bool addPlayer(Player*);
    bool removePlayer(Player*);
    void operator<<(const Group&); // eat
    Player* getHighest() const;
};


#endif // _GROUP_H
