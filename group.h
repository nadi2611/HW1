#ifndef GROUP_H
#define GROUP_H

#include "iostream"
#include "avlTree.h"
#include "playerLevel.h"


class group{


public:
    int group_id;
    avl_tree<playerLevel>* players;
    playerLevel* max_player;
    explicit group(int id) : group_id(id),players(nullptr),max_player(nullptr){}
    ~group() = default;

    bool operator==(const group new_group ) const;
    bool operator!=(const group new_group ) const;
    bool operator>(const group new_group ) const;
    bool operator<(const group new_group ) const;
    bool operator>=(const group new_group ) const;
    bool operator<=(const group new_group ) const;





};

#endif