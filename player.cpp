#include "Player.h"
#include "Group.h"

Player::Player(int id, int lvl, Group* group) : id(id), lvl(lvl), group(group), rankVec(lvl, id) {}

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
    p->setGroup(new_group);
}

void Player::increaseLvl(int inc) {
    this->lvl += inc;
    rankVec.updateX(this->lvl);
}

const Vec2D* Player::getRankVec() const {
    return &(this->rankVec);
}
