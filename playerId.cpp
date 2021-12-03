
#include "playerId.h"


bool playerId::operator==(const playerId new_player ) const{
    if(new_player.id == id){
        return true;
    }
    return false;
}

bool playerId::operator!=(const playerId new_player ) const{
    if(new_player.id != id){
        return true;
    }
    return false;
}

bool playerId::operator>(const playerId new_player ) const{
    if(new_player.id < id){
        return true;
    }
    return false;
}

bool playerId::operator<(const playerId new_player ) const{
    if(new_player.id > id){
        return true;
    }
    return false;
}


bool playerId::operator>=(const playerId new_player ) const{
    if(new_player.id <= id){
        return true;
    }
    return false;
}

bool playerId::operator<=(const playerId new_player ) const{
    if(new_player.id >= id){
        return true;
    }
    return false;
}

playerId playerId:: operator++(int) {
    level++;
}

void playerId::setPlayersGroup (group* group){
    players_group=group;
}