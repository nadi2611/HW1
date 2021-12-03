#include "group.h"

bool group::operator==(const group new_group ) const{
    if(new_group.group_id == group_id){
        return true;
    }
    return false;
}

bool group::operator!=(const group new_group ) const{
    if(new_group.group_id != group_id){
        return true;
    }
    return false;
}

bool group::operator<(const group new_group ) const{
    if(new_group.group_id > group_id){
        return true;
    }
    return false;
}

bool group::operator>(const group new_group ) const{
    if(new_group.group_id < group_id){
        return true;
    }
    return false;
}

bool group::operator<=(const group new_group ) const{
    if(new_group.group_id >= group_id){
        return true;
    }
    return false;
}

bool group::operator>=(const group new_group ) const{
    if(new_group.group_id <= group_id){
        return true;
    }
    return false;
}