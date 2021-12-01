#include "Group.h"
#include "Player.h"

Group::Group(int id) : id(id), highest(nullptr) {
    players = new AVL<const Vec2D*, Player*>();
}

bool Group::addPlayer(Player* new_player) {
    const Vec2D* rank = new_player->getRankVec();
    bool success = players->insert(rank, new_player);
    new_player->setGroup(this);
    return success;
}

bool Group::removePlayer(Player* player) {
    bool success = players->remove(player->getRankVec());
    return success;
}

void Group::operator<<(Group* replacementGroup) {
    Player* highestThis = this->highest;
    Player* highestRep = replacementGroup->highest;
    Player* newHighest = highestThis->getRankVec() > highestRep->getRankVec() ? highestThis : highestRep;
    AVL<const Vec2D*, Player*>* new_players = new AVL<const Vec2D*, Player*>(this->players, replacementGroup->players); //merge
    delete this->players;
    players = new_players;
    players->applyInorder(Player::setGroupStatic, this);

    highest = newHighest;
}

Player* Group::getHighest() const {
    return highest;
}

void Group::print() {
    std::cout << "Printing group.. id: " << id << ". players: " << std::endl;
    players->printBT();
}