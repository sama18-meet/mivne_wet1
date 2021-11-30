#include "Group.h"
#include "Player.h"

Group::Group(int id) : id(id), highest(nullptr) {}

bool Group::addPlayer(Player* new_player) {
    const Vec2D* rank = new_player->getRankVec();
    bool success = players.insert(rank, new_player);
    return success;
}

bool Group::removePlayer(Player* player) {
    bool success = players.remove(player->getRankVec());
    return success;
}

void Group::operator<<(const Group& replacementGroup) {
    Player* highestThis = this->highest;
    Player* highestRep = replacementGroup.highest;
    Player* newHighest = highestThis->getRankVec() > highestRep->getRankVec() ? highestThis : highestRep;
    AVL<const Vec2D*, Player*> new_players(this->players, replacementGroup.players); //merge
    delete this->players;
    players = new_players;
    players.apply_inorder(Player::setGroupStatic, this, false, false);

    highest = newHighest;
}

Player* Group::getHighest() const {
    return highest;
}
