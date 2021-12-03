
#include "playerLevel.h"

bool playerLevel::operator==(const playerLevel new_player ) const{
    if(new_player.level == level){
        return true;
    }
    return false;
}


playerLevel& playerLevel::operator=( playerLevel* new_player ) {

    id = new_player->id;
    level = new_player->level;
}

bool playerLevel::operator!=(const playerLevel new_player ) const{
    if(new_player.level != level){
        return true;
    }
    return false;
}

bool playerLevel::operator>(const playerLevel new_player ) const{
    if(new_player.level < level){
        return true;
    }
    if (new_player.level == level && new_player.id > id)
    {
        return true;
    }
    return false;
}

bool playerLevel::operator<(const playerLevel new_player ) const{
    if(new_player.level > level){
        return true;
    }
    if (new_player.level == level && new_player.id < id)
    {
        return true;
    }
    return false;
}


bool playerLevel::operator>=(const playerLevel new_player ) const{
    if(new_player.level <= level){
        return true;
    }
    return false;
}

bool playerLevel::operator<=(const playerLevel new_player ) const{
    if(new_player.level >= level){
        return true;
    }
    return false;
}

playerLevel playerLevel:: operator++(int) {
    level++;
}