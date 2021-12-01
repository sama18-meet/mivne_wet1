#include "Group.h"
#include "Player.h"

Group::Group(int id) : id(id), highest(nullptr) {
    players = new AVL<const Vec2D*, Player*>();
}

int Group::getId() const {
    return this->id;
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
    Player* highestThis = this->getHighest();
    Player* highestRep = replacementGroup->getHighest();
    Player* newHighest = *(highestThis->getRankVec()) > *(highestRep->getRankVec()) ? highestThis : highestRep;
    AVL<const Vec2D*, Player*>* new_players = new AVL<const Vec2D*, Player*>(this->players, replacementGroup->players); //merge
    delete this->players;
    players = new_players;
    players->applyInorder(Player::setGroupStatic, this, -1);

    highest = newHighest;
}

Player* Group::getHighest() const {
    return highest;
}

void Group::print(int i, Group* g, int j) {
    if (g==nullptr) {
        return;
    }
    std::cout << "Printing group.. id: " << g->id << ". players: " << std::endl;
    g->players->printBT();
}


void Group::updateHighestPlayer() {
    highest = players->getMax();
}

int Group::getNumOfPlayers() const {
    return players->getSize();
}