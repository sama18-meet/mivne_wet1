#include"library1.h"
#include"PlayersManager.h"

void* Init() {
    try {
        PlayersManager *DS = new PlayersManager();
        return (void*)DS;
    }
    catch (std::bad_alloc&) {
        return nullptr;
    }
}

StatusType AddGroup(void *DS, int GroupID) {
    if (DS == nullptr || GroupID <= 0) {
        return INVALID_INPUT;
    }
    PlayersManager* pm = (PlayersManager*)DS;
    try {
        bool success = pm->addGroup(GroupID);
        return success ? SUCCESS : FAILURE;
    }
    catch (std::bad_alloc&) {
        return ALLOCATION_ERROR;
    }
}

StatusType AddPlayer(void *DS, int PlayerID, int GroupID, int Level) {
    if (DS == nullptr || PlayerID <= 0 || GroupID <= 0 || Level < 0) {
        return INVALID_INPUT;
    }
    PlayersManager* pm = (PlayersManager*)DS;
    try {
        bool success = pm->addPlayer(PlayerID, GroupID, Level);
        return success ? SUCCESS : FAILURE;
    }
    catch (std::bad_alloc&) {
        return ALLOCATION_ERROR;
    }
}

StatusType RemovePlayer(void *DS, int PlayerID) {
    if (DS == nullptr || PlayerID <= 0) {
        return INVALID_INPUT;
    }
    PlayersManager* pm = (PlayersManager*)DS;
    try {
        bool success = pm->removePlayer(PlayerID);
        return success ? SUCCESS : FAILURE;
    }
    catch (std::bad_alloc&) {
        return ALLOCATION_ERROR;
    }
}

StatusType ReplaceGroup(void *DS, int GroupID, int ReplacementID) {
    if (DS == nullptr || GroupID <= 0 || ReplacementID <= 0 || GroupID == ReplacementID) {
        return INVALID_INPUT;
    }
    PlayersManager* pm = (PlayersManager*)DS;
    try {
        bool success = pm->replaceGroup(GroupID, ReplacementID);
        return success ? SUCCESS : FAILURE;
    }
    catch (std::bad_alloc&) {
        return ALLOCATION_ERROR;
    }
}

StatusType IncreaseLevel(void *DS, int PlayerID, int LevelIncrease) {
    if (DS == nullptr || PlayerID <= 0 || LevelIncrease <= 0) {
        return INVALID_INPUT;
    }
    PlayersManager* pm = (PlayersManager*)DS;
    try {
        bool success = pm->increaseLevel(PlayerID, LevelIncrease);
        return success ? SUCCESS : FAILURE;
    }
    catch (std::bad_alloc&) {
        return ALLOCATION_ERROR;
    }
}

StatusType GetHighestLevel(void *DS, int GroupID, int *PlayerID) {
    if (DS == nullptr || PlayerID == nullptr || GroupID == 0) {
        return INVALID_INPUT;
    }
    PlayersManager* pm = (PlayersManager*)DS;
    try {
        bool success = pm->getHighestLvl(GroupID, PlayerID);
        return success ? SUCCESS : FAILURE;
    }
    catch (std::bad_alloc&) {
        return ALLOCATION_ERROR;
    }
}

StatusType GetAllPlayersByLevel(void *DS, int GroupID, int **Players, int *numOfPlayers) {
    if (DS == nullptr || Players == nullptr || numOfPlayers == nullptr || GroupID == 0) {
        return INVALID_INPUT;
    }
    PlayersManager* pm = (PlayersManager*)DS;
    try {
        bool success = pm->getAllPlayersByLvl(GroupID, Players, numOfPlayers);
        return success ? SUCCESS : FAILURE;
    }
    catch (std::bad_alloc&) {
        return ALLOCATION_ERROR;
    }
}

StatusType GetGroupsHighestLevel(void *DS, int numOfGroups, int **Players) {
    if (DS == nullptr || Players == nullptr || numOfGroups < 1) {
        return INVALID_INPUT;
    }
    PlayersManager* pm = (PlayersManager*)DS;
    try {
        bool success = pm->getGroupsHighestLvl(numOfGroups, Players);
        return success ? SUCCESS : FAILURE;
    }
    catch (std::bad_alloc&) {
        return ALLOCATION_ERROR;
    }
}

void Quit(void** DS) {
    PlayersManager* pm = (PlayersManager*)* DS;
    delete pm;
    *DS = nullptr;
}
