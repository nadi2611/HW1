
#ifndef PLAYERID_H
#define PLAYERID_H
#include "group.h"
class playerId {
    int id;
    int level;
    group* players_group;
    group* players_not_empty_group;

public:

    explicit playerId(int new_id,int new_level) : id(new_id),level(new_level),players_group(nullptr),players_not_empty_group(
            nullptr){}
    ~playerId() = default;

    bool operator==(const playerId new_player ) const;
    bool operator!=(const playerId new_player ) const;
    bool operator>(const playerId new_player ) const;
    bool operator<(const playerId new_player ) const;
    bool operator>=(const playerId new_player ) const;
    bool operator<=(const playerId new_player ) const;
    void setPlayersGroup (group* group);
    void setPlayersGroupNotEmpty (group* group);

    playerId operator++(int) ;
    int getLevel(){
        return level;
    }
    group* getPlayersNotEmptyGroup()
    {
        return players_not_empty_group;
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
