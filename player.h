#ifndef _PLAYER_H
#define _PLAYER_H

class Group;
#include "Vec2D.h"

class Player {
private:
    int id;
    int lvl;
    Group* group;
    Vec2D rankVec;
public:
    Player(int id, int lvl, Group* group);
    ~Player() = default;
    int getId() const;
    int getLvl() const;
    Group* getGroup() const;
    void setGroup(Group* new_group);
    static void setGroupStatic(Group* new_group, Player p);
    void increaseLvl(int inc);
    const Vec2D* getRankVec() const;
};


#endif // _PLAYER_H
