
#ifndef PLAYERID_H
#define PLAYERID_H
#include "group.h"
class playerId {
    int id;
    int level;
    group* players_group;

public:

    explicit playerId(int new_id,int new_level) : id(new_id),level(new_level),players_group(nullptr){}
    ~playerId() = default;

    bool operator==(const playerId new_player ) const;
    bool operator!=(const playerId new_player ) const;
    bool operator>(const playerId new_player ) const;
    bool operator<(const playerId new_player ) const;
    bool operator>=(const playerId new_player ) const;
    bool operator<=(const playerId new_player ) const;
    void setPlayersGroup (group* group);
    playerId operator++(int) ;
    int getLevel(){
        return level;
    }
    group* getPlayersGroup()
    {
        return players_group;
    }
    int getId(){
        return id;
    }
};





#endif
