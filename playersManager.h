

#ifndef DS_H
#define DS_H


#include "group.h"
#include "playerId.h"
#include "hw1.h"

class playersManager {
    avl_tree<group>* groups_tree;
    avl_tree<playerId>* playersid_tree;
    avl_tree<playerLevel>* playerslevel_tree;
    playerLevel* max_player;
    avl_tree<group>* not_empty_groups;


public:

    playersManager():groups_tree(nullptr),playersid_tree(nullptr),playerslevel_tree(nullptr),max_player(nullptr),not_empty_groups(
            nullptr){}
    ~playersManager() = default;

    StatusType addGroup(int id);
    StatusType removePlayer(int id);
    StatusType ReplaceGroup(int GroupID, int ReplacementID);
    StatusType addPlayer(int player_id, int group_id, int level);
    StatusType IncreaseLevel(int player_id, int level_increase);
    StatusType  GetHighestLevel( int group_id, int* player_id);
    StatusType GetAllPlayersByLevel(int group_id, int **players, int *numOfPlayers);
    StatusType GetGroupsHighestLevel(int numOfGroups, int** players);
    void merge(playerLevel* arr1, playerLevel* arr2, playerLevel* arr3, int len1, int len2);
    void Quit();
};


#endif
