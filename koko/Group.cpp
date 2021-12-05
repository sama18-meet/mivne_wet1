#include "Group.h"
#include "Player.h"

Group::Group(int id) : id(id), highest(nullptr) {
    players = new AVL<Vec2D, Player*>();
}


Group::~Group() {
    delete players;
}

int Group::getId() const {
    return this->id;
}

bool Group::addPlayer(Player* new_player) {
    Vec2D rank = new_player->getRankVec();
    bool success = players->insert(rank, new_player);
    new_player->setGroup(this);
    updateHighestPlayer();
    return success;
}

bool Group::removePlayer(Player* player) {
    bool success = players->remove(player->getRankVec());
    updateHighestPlayer();
    return success;
}

void Group::insertAllPlayersOf(Group* groupToBeDeleted) {
    AVL<Vec2D, Player*>* new_players = new AVL<Vec2D, Player*>(this->players, groupToBeDeleted->players); //merge
    delete this->players;
    this->players = new_players;
    this->players->applyInorder(Player::setGroupStatic, this, ALL_NODES);
    updateHighestPlayer();

}

Player* Group::getHighest() const {
    return highest;
}

void Group::print(int i, Group* g, int j) {
    if (g==nullptr) {
        std::cout << "WARNING: attempt to print null group " << std::endl;
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

void Group::deleteGroup(int redundant1, Group* groupToDelete, int redundant2) {
    delete groupToDelete;
}
