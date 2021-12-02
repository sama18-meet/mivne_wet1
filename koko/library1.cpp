#include"library1.h"
#include"PlayersManager.h"

/*
void* Init() {
    PlayersManager *DS = new PlayersManager();
    return (void*)DS;
}
StatusType AddGroup(void *DS, int GroupID){
    return ((PlayersManager*)DS)-> AddGroup (GroupID);
}
 */


StatusType AddGroup(void *DS, int GroupID) {
    if (DS == nullptr || GroupID <= 0) {
        return INVALID_INPUT;
    }
    PlayersManager* pm = (PlayersManager*)DS;
    try {
        bool success = pm->addGroup(GroupID);
    }
    catch (std::bad_alloc) {
        return ALLOCATION_ERROR;
    }
    return success ? SUCCESS : FAILURE;
}


void Quit(void** DS) {
    PlayersManager* pm = (PlayersManager*)DS;
    delete pm;
}
