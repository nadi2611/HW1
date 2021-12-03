

#ifndef playerLevel_H
#define playerLevel_H

class playerLevel {
    int id;
    int level;

public:

    explicit playerLevel(int new_id,int new_level) : id(new_id),level(new_level){}
    explicit playerLevel() : id(0),level(0){}
    ~playerLevel() = default;

    bool operator==(const playerLevel new_player ) const;
    playerLevel& operator=( playerLevel* new_player ) ;
    bool operator!=(const playerLevel new_player ) const;
    bool operator>(const playerLevel new_player ) const;
    bool operator<(const playerLevel new_player ) const;
    bool operator>=(const playerLevel new_player ) const;
    bool operator<=(const playerLevel new_player ) const;
    playerLevel operator++(int);
    int getID()
    {
        return id;
    }
    int getLevel(){
        return level;
    }
};


#endif
