#include "Player.h"
#include "Group.h"

Player::Player(int id, int lvl) : id(id), lvl(lvl), group(nullptr), rankVec(lvl, id) {}

int Player::getId() const {
    return this->id;
}

int Player::getLvl() const {
    return this->lvl;
}

Group* Player::getGroup() const {
    return this->group;
}

void Player::setGroup(Group* new_group) {
    this->group = new_group;
}

void Player::setGroupStatic(Group* new_group, Player* p, int redundant) {
    if (p==nullptr) {
        return;
    }
    p->setGroup(new_group);
}

void Player::increaseLvl(int inc) {
    this->lvl += inc;
    rankVec.updateX(this->lvl);
}

Vec2D Player::getRankVec() const {
    return this->rankVec;
}
