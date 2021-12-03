
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

    AddPlayer(ds,2116,15,0);
    AddPlayer(ds, 2118, 15, 4);
    AddPlayer(ds, 2110, 5,500);
    ReplaceGroup(ds,5,15);

}