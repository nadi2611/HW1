
#include "hw1.h"
#include "playersManager.h"
#include "ostream"

void* init(){
    playersManager* ds = new playersManager();

    if(ds == nullptr){
        return nullptr;
    }

    return (void*)ds;

}

StatusType addGroup(void* DS, int GroupID){
    if(DS == nullptr){
        return INVALID_INPUT;
    }
    return ((playersManager*)DS)->addGroup(GroupID);
}
StatusType RemovePlayer(void *DS, int PlayerID){
    if(DS == nullptr){
        return INVALID_INPUT;
    }

    return ((playersManager*)DS)->removePlayer(PlayerID);
}

StatusType ReplaceGroup(void *DS, int GroupID, int ReplacementID){
    if(DS == nullptr){
        return INVALID_INPUT;
    }

    return ((playersManager*)DS)->ReplaceGroup(GroupID,ReplacementID);
}

StatusType AddPlayer(void *DS, int PlayerID, int GroupID, int Level){
    if(DS == nullptr){
        return INVALID_INPUT;
    }

    return ((playersManager*)DS)->addPlayer(PlayerID,GroupID,Level);
}

StatusType GetHighestLevel(void *DS, int GroupID, int *PlayerID){
    if(DS == nullptr){
        return INVALID_INPUT;
    }

    return ((playersManager*)DS)->GetHighestLevel(GroupID,PlayerID);
}
StatusType GetGroupsHighestLevel(void *DS, int numOfGroups, int** players){
    if (DS == nullptr || players == nullptr || numOfGroups < 1){
        return INVALID_INPUT;
    }

    return ((playersManager*)DS)->GetGroupsHighestLevel(numOfGroups,players);


}

StatusType IncreaseLevel (void *DS, int PlayerID, int LevelIncrease){

    if (DS == nullptr){
        return INVALID_INPUT;
    }

    return ((playersManager*)DS)->IncreaseLevel(PlayerID,LevelIncrease);
}

StatusType GetAllPlayersByLevel (void *DS, int GroupID, int **Players, int *numOfPlayers){
    if(DS == nullptr || Players == nullptr || numOfPlayers == nullptr){
        return INVALID_INPUT;
    }

    return ((playersManager*)DS)->GetAllPlayersByLevel(GroupID,Players,numOfPlayers);

}

void Quit(void** DS){
    return ((playersManager*)DS)->Quit();
}




int main(){
    void* ds = init();
   // if(addGroup(ds, 3) == INVALID_INPUT){
  //      cout<<"fail";
   // }
    //if(addGroup(ds, 3) == FAILURE){
    //    cout<<"fail";
   // }
    //    cout<<"success";

    addGroup(ds,3);
    addGroup(ds,5);
    addGroup(ds,15);



}