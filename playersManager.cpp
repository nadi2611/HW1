

#include "playersManager.h"
#include <ostream>

StatusType playersManager:: addGroup(int id){
    if(id <= 0){
        return INVALID_INPUT;
    }

    // Checks if we didnt add any group yet
    if(groups_tree == nullptr ){
        groups_tree = new avl_tree<group>;
        if(groups_tree == nullptr){
            return ALLOCATION_ERROR;
        }
    }

    // Checks if we didnt add any group yet
    if(not_empty_groups == nullptr ){
        not_empty_groups = new avl_tree<group>;
        if(not_empty_groups == nullptr){
            return ALLOCATION_ERROR;
        }
    }

    // Object of type group (to add).
    group *temp_group1 = new group(id) ;

    if(temp_group1 == nullptr){
        return ALLOCATION_ERROR;
    }



    // Object of type group_node to add for groups_tree
    avl_node<group>* temp_group1_node = new avl_node<group>(temp_group1);

    if(temp_group1_node == nullptr){
        return ALLOCATION_ERROR;
    }
    // Object of type group_node to add for not_empty_group_tree.

    avl_node<group>* temp_group2_node = new avl_node<group>(temp_group1);

    if(temp_group2_node == nullptr){
        return ALLOCATION_ERROR;
    }


    if(groups_tree->findNode(temp_group1, groups_tree->getRoot()) != nullptr
    || not_empty_groups->findNode(temp_group1,not_empty_groups->getRoot()) != nullptr){
        return FAILURE;
    }

    // Insert the new group to both trees.
    if(groups_tree->insertAvlNode(temp_group1_node) && not_empty_groups->insertAvlNode(temp_group2_node)){
        return SUCCESS;
    }


    // Should not reach this code
    return ALLOCATION_ERROR;



}

StatusType playersManager::removePlayer(int id) {

    if (id <= 0) {
        return INVALID_INPUT;
    }

    // Remove player from not_empty_group.

    playerId temp =  playerId(id, 0);
    avl_node<playerId> *player_id_node = playersid_tree->findNode(&temp, playersid_tree->getRoot());

    if (player_id_node == nullptr) {
        return FAILURE ; // there is no player with the given id .
    }

    // Delete the player from the group
    playerLevel* player_level = new playerLevel(player_id_node->getData()->getId(),player_id_node->getData()->getLevel());

    player_id_node->getData()->getPlayersGroup()->players->removeNode(player_level, player_id_node->getData()->getPlayersGroup()->players->getRoot());
    avl_node<playerLevel>* root_players = player_id_node->getData()->getPlayersGroup()->players->getRoot();

    // Checks if we removed the maximum.
    if(player_level->getLevel() > (player_id_node->getData()->getPlayersGroup()->max_player)->getLevel()){

        player_id_node->getData()->getPlayersGroup()->max_player = (player_id_node->getData()->getPlayersGroup()->players->findMaxNode(root_players))->getData();

    }


    player_id_node->getData()->getPlayersNotEmptyGroup()->players->removeNode(player_level, player_id_node->getData()->getPlayersNotEmptyGroup()->players->getRoot());

    if(player_level->getLevel() > (player_id_node->getData()->getPlayersNotEmptyGroup()->max_player)->getLevel()){

        avl_node<playerLevel>* root = player_id_node->getData()->getPlayersNotEmptyGroup()->players->getRoot();
        player_id_node->getData()->getPlayersNotEmptyGroup()->max_player = (player_id_node->getData()->getPlayersNotEmptyGroup()->players->findMaxNode(root))->getData() ;

    }
    if(player_id_node->getData()->getPlayersGroup()->players == 0){
        // Delete the group from not_empty_group tree and update the max.
        player_id_node->getData()->getPlayersGroup()->max_player = nullptr;
        delete(player_id_node->getData()->getPlayersGroup()->players);
        player_id_node->getData()->getPlayersGroup()->players = nullptr;

        player_id_node->getData()->getPlayersNotEmptyGroup()->max_player = nullptr;
        delete(player_id_node->getData()->getPlayersNotEmptyGroup()->players);
        player_id_node->getData()->getPlayersNotEmptyGroup()->players = nullptr;

        not_empty_groups->removeNode(player_id_node->getData()->getPlayersNotEmptyGroup(), not_empty_groups->getRoot());




    }

    playersid_tree->removeNode(player_id_node->getData(),playersid_tree->getRoot());
    free(player_level);

    player_id_node->getData()->setPlayersGroup(nullptr);
    player_id_node->getData()->setPlayersGroupNotEmpty(nullptr);


    playerslevel_tree->removeNode(player_level, playerslevel_tree->getRoot());

    if(player_id_node->getData()->getLevel() > max_player->getLevel()){
        max_player = (playerslevel_tree->findMaxNode(playerslevel_tree->getRoot()))->getData();
    }

    return SUCCESS;

}

StatusType playersManager:: ReplaceGroup(int GroupID, int ReplacementID) {

    int i = 0;
    int j = 0;
    int k = 0;

    if (GroupID <= 0 || ReplacementID <= 0 || GroupID == ReplacementID) {
        return INVALID_INPUT;
    }

    group temp_a = group(GroupID);
    avl_node<group> *group_a = groups_tree->findNode(&temp_a, groups_tree->getRoot());

    if (group_a == nullptr) {
        return FAILURE;
    }

    group temp_b = group(ReplacementID);
    avl_node<group> *group_b = groups_tree->findNode(&temp_b, groups_tree->getRoot());

    if (group_b == nullptr) {
        return FAILURE;
    }

    avl_tree<playerLevel> *player_tree1 = group_a->getData()->players;

    if (player_tree1 == nullptr) {
        groups_tree->removeNode(&temp_a, groups_tree->getRoot());
        return SUCCESS;
    }

    avl_tree<playerLevel> *player_tree2 = group_b->getData()->players;
    if (player_tree2 == nullptr) {
        player_tree2 = new avl_tree<playerLevel>;

        if (player_tree2 == nullptr) {
            return ALLOCATION_ERROR;
        }

    }


    playerLevel *array1 = static_cast<playerLevel *>(malloc((sizeof(playerLevel *)) * (player_tree1->getLenght())));
    if (array1 == nullptr) {
        return ALLOCATION_ERROR;
    }

    playerLevel *array2 = static_cast<playerLevel *>(malloc((sizeof(playerLevel *)) * (player_tree2->getLenght())));
    if (array2 == nullptr) {
        return ALLOCATION_ERROR;
    }


    player_tree1->inOrder(&i, player_tree1->getRoot(), &array1);
    player_tree2->inOrder(&j, player_tree2->getRoot(), &array2);

    int len_1 = player_tree1->getLenght();
    int len_2 = player_tree2->getLenght();


    int array3_length = player_tree1->getLenght() + player_tree2->getLenght();
    playerLevel *array3 = static_cast<playerLevel *>(malloc((sizeof(playerLevel *)) * (array3_length)));
    i = 0;
    j = 0;
    k = 0;
    merge(array1, array2, array3, len_1, len_2);


    for (int x = 0; x < array3_length; x++) {

        cout << (array3[x].getID());
    }


    avl_node<playerLevel>* root_for_new_players = player_tree1->buildTree(nullptr,array3,0,array3_length);

    delete (player_tree1);
    player_tree1= nullptr;
    delete (player_tree2);
    player_tree2= nullptr;
    group_b->getData()->players->setRoot(root_for_new_players,array3_length);



    // updating the trees in the not empty trees
    temp_a = group(GroupID);
    group_a = not_empty_groups->findNode(&temp_a, not_empty_groups->getRoot());
    if (group_a == nullptr) {
        return FAILURE;
    }
    not_empty_groups->removeNode(&temp_a,not_empty_groups->getRoot());
    temp_b = group(ReplacementID);
    group_b = not_empty_groups->findNode(&temp_b, not_empty_groups->getRoot());
    if (group_b == nullptr) {
        return FAILURE;
    }
    player_tree1=group_a->getData()->players;
    player_tree2=group_b->getData()->players;
    player_tree1->inOrder(&i, player_tree1->getRoot(), &array1);
    player_tree2->inOrder(&j, player_tree2->getRoot(), &array2);

    len_1 = player_tree1->getLenght();
    len_2 = player_tree2->getLenght();

    array3_length = len_1+len_2;
    array3 = static_cast<playerLevel *>(malloc((sizeof(playerLevel *)) * (array3_length)));
    i = 0;
    j = 0;
    k = 0;
    merge(array1, array2, array3, len_1, len_2);
    avl_node<playerLevel>* new_root = player_tree1->buildTree(nullptr,array3,0,array3_length);
    delete (player_tree1);
    player_tree1= nullptr;
    delete (player_tree2);
    player_tree2= nullptr;
    group_b->getData()->players->setRoot(new_root,array3_length);
    free(array1);
    free(array2);
    free(array3);
    return  SUCCESS;
}
void playersManager::merge(playerLevel* arr1, playerLevel* arr2, playerLevel* arr3, int len1, int len2){

    int i = 0, j = 0, k = 0;

    // Traverse both array
    while (i < len1 && j < len2)
    {
        // Check if current element of first
        // array is smaller than current element
        // of second array. If yes, store first
        // array element and increment first array
        // index. Otherwise do same with second array
        if (arr1[i] < arr2[j])
            arr3[k++] = arr1[i++];
        else
            arr3[k++] = arr2[j++];
    }

    // Store remaining elements of first array
    while (i < len1)
        arr3[k++] = arr1[i++];

    // Store remaining elements of second array
    while (j < len2)
        arr3[k++] = arr2[j++];
}



StatusType playersManager:: addPlayer(int player_id, int group_id, int level) {

    if (player_id <= 0 || group_id <= 0 || level < 0)//checks if any input is invalid.
    {
        return INVALID_INPUT;
    }

    //checks if there is a player with the same id
    if (playersid_tree != nullptr) {
        playerId *temp_player_id = new playerId(player_id, level);
        if (playersid_tree->findNode(temp_player_id, playersid_tree->getRoot())) {
            return FAILURE; //there is a player with the same id

        }

    }

    // adding player to player id tree
    if (playersid_tree == nullptr) // playersid_tree in empty
    {
        playersid_tree = new avl_tree<playerId>();
        if (playersid_tree == nullptr) {
            return ALLOCATION_ERROR;
        }
    }
    playerId *player_id_2 = new playerId(player_id, level);
    if (player_id_2 == nullptr) {
        return ALLOCATION_ERROR;
    }
    avl_node<playerId> *playerId_node = new avl_node<playerId>(player_id_2);
    if (playerId_node == nullptr) {
        return ALLOCATION_ERROR;
    }
    if (!playersid_tree->insertAvlNode(playerId_node)) {
        return ALLOCATION_ERROR;

    }
    // allocation in the given group.
    group temp_group = group(group_id);
    if (groups_tree == nullptr)// group tree is empty
    {
        return FAILURE; // there is no tree with the given id
    }
    avl_node<group> *group_to_add_to = groups_tree->findNode(&temp_group, groups_tree->getRoot());
    if (group_to_add_to == nullptr) {
        return FAILURE;// there is no group with the given group id
    }

    if (group_to_add_to->getData()->players == nullptr) // players tree in the group is empty.
    {
        group_to_add_to->getData()->players = new avl_tree<playerLevel>;
        if (group_to_add_to->getData()->players == nullptr) {
            return ALLOCATION_ERROR;
        }
    }



    //adding to the players tree in the group.
    playerLevel *player_level_1 = new playerLevel(player_id, level);
    if (player_level_1 == nullptr) {
        return ALLOCATION_ERROR;
    }
    avl_node<playerLevel> *temp_player_node_1 = new avl_node<playerLevel>(player_level_1);

    if (temp_player_node_1 == nullptr) {
        return ALLOCATION_ERROR;
    }
    if (!(group_to_add_to->getData()->players->insertAvlNode(temp_player_node_1))) {
        return ALLOCATION_ERROR;
    }


    // adjusting the max player in the group
    if (group_to_add_to->getData()->max_player == nullptr) {
        group_to_add_to->getData()->max_player = player_level_1;
    } else if (group_to_add_to->getData()->max_player < player_level_1) {
        group_to_add_to->getData()->max_player = player_level_1;
    }

    //setting the group pointer in player id to point at the players group.
    player_id_2->setPlayersGroup((group_to_add_to->getData()));



    //adding to the players tree in the not_empty_groups_tree.
    playerLevel *player_level_2 = new playerLevel(player_id, level);
    if (player_level_2 == nullptr) {
        return ALLOCATION_ERROR;
    }
    avl_node<playerLevel> *temp_player_node_2 = new avl_node<playerLevel>(player_level_2);

    if (temp_player_node_2 == nullptr) {
        return ALLOCATION_ERROR;
    }

    avl_node<group>* group_not_empty_to_add_to = not_empty_groups->findNode(&temp_group,not_empty_groups->getRoot());

    if (!(group_not_empty_to_add_to->getData()->players->insertAvlNode(temp_player_node_2))) {
        return ALLOCATION_ERROR;
    }


    // adjusting the max player in the group
    if (group_not_empty_to_add_to->getData()->max_player == nullptr) {
        group_not_empty_to_add_to->getData()->max_player = player_level_2;
    } else if (group_not_empty_to_add_to->getData()->max_player < player_level_2) {
        group_not_empty_to_add_to->getData()->max_player = player_level_2;
    }

    //setting the group pointer in player id to point at the players group.
    player_id_2->setPlayersGroupNotEmpty((group_not_empty_to_add_to->getData()));


    // adding player to player level tree
    if (playerslevel_tree == nullptr) // playerslevel_tree in empty
    {
        playerslevel_tree = new avl_tree<playerLevel>();
        if (playerslevel_tree == nullptr) {
            return ALLOCATION_ERROR;
        }
    }
    playerLevel *player_level_3 = new playerLevel(player_id, level);
    if (player_level_3 == nullptr) {
        return ALLOCATION_ERROR;
    }

    avl_node<playerLevel> *player_node_3 = new avl_node<playerLevel>(player_level_3);
    if (player_node_3 == nullptr) {
        return ALLOCATION_ERROR;
    }
    if (!playerslevel_tree->insertAvlNode(player_node_3)) {
        return ALLOCATION_ERROR;
    }

    //updating the max player in playersManager
    if (max_player == nullptr ){
        max_player = player_level_3;
    }
    if (*max_player < *player_level_3)
    {
        max_player = player_level_3;
    }

    return SUCCESS;
}

StatusType playersManager::IncreaseLevel(int player_id, int level_increase) {

    // checks if there is invalid input.
    if (player_id <= 0 || level_increase <= 0) {
        return INVALID_INPUT;
    }


    if (playersid_tree->getRoot() == nullptr) {
        return FAILURE; // there is no players.
    }
    playerId temp_player_id = playerId(player_id, 1);// the level does not make a difference.
    avl_node<playerId> *found_player_id = playersid_tree->findNode(&temp_player_id, playersid_tree->getRoot());
    if (found_player_id == nullptr) {
        return FAILURE; // there is no player with the given id
    }

    // player was found , time to update the level
    // update in playersId_tree his place does not change
    int old_level = (found_player_id->getData())->getLevel();
    for (int j = 0; j < level_increase; j++) {
        (*(found_player_id->getData()))++;
    }

    // update in players level_tree
    playerLevel temp_player_level = playerLevel(player_id, old_level);
    if (playerslevel_tree->getRoot() == nullptr) {
        return FAILURE; // there is no players - should no reach it.
    }
    if (!playerslevel_tree->removeNode(&temp_player_level, playerslevel_tree->getRoot())) {
        return FAILURE;
    }
    int new_level = old_level + level_increase;
    playerLevel *new_player_level = new playerLevel(player_id, new_level);
    if (new_player_level == nullptr) {
        return ALLOCATION_ERROR;
    }
    avl_node<playerLevel> *new_player_level_node = new avl_node<playerLevel>(new_player_level);
    if (!playerslevel_tree->insertAvlNode(new_player_level_node)) {
        return ALLOCATION_ERROR;
    }


    // update in group players tree
    playerLevel temp_player_level_2 = playerLevel(player_id, old_level);
    group *players_group = found_player_id->getData()->getPlayersGroup();
    if (!players_group->players->removeNode(&temp_player_level_2, players_group->players->getRoot())) {
        return FAILURE;
    }
    playerLevel *new_player_level_2 = new playerLevel(player_id, new_level);
    if (new_player_level_2 == nullptr) {
        return ALLOCATION_ERROR;
    }
    avl_node<playerLevel> *player_level_node_2 = new avl_node<playerLevel>(new_player_level_2);
    if (!players_group->players->insertAvlNode(player_level_node_2)) {
        return ALLOCATION_ERROR;
    }

    // update max player in the group
    players_group->max_player = (players_group->players->findMaxNode(players_group->players->getRoot()))->getData();
    max_player=playerslevel_tree->findMaxNode(playerslevel_tree->getRoot())->getData();

////+++
    //updating players in not empty groups tree
    playerLevel temp_player_level_3 = playerLevel(player_id, old_level);
    group *players_group_2 = found_player_id->getData()->getPlayersNotEmptyGroup();
    if (!players_group_2->players->removeNode(&temp_player_level_3, players_group_2->players->getRoot())) {
        return FAILURE;
    }
    playerLevel *new_player_level_3 = new playerLevel(player_id, new_level);
    if (new_player_level_3 == nullptr) {
        return ALLOCATION_ERROR;
    }
    avl_node<playerLevel> *player_level_node_3 = new avl_node<playerLevel>(new_player_level_3);
    if (!players_group->players->insertAvlNode(player_level_node_3)) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}
StatusType playersManager::GetHighestLevel(int group_id, int *player_id) {

    if (group_id == 0 || player_id == nullptr) {
        return INVALID_INPUT;
    }

    if (group_id < 0) {
        if (max_player == nullptr) {
            //there is no players
            *player_id = -1;
            return SUCCESS;
        }

        *player_id = (max_player->getID());
        return SUCCESS;
    }
    if (groups_tree == nullptr) {
        return FAILURE; // groups tree is empty,therefore there is no group with the given id.
    }
    group temp_group = group(group_id);
    avl_node<group> *found_group = groups_tree->findNode(&temp_group, groups_tree->getRoot());
    if (found_group == nullptr) {
        return FAILURE; // there is no group with the given id.
    }

    playerLevel *found_max_player = found_group->getData()->max_player;
    if (found_max_player == nullptr) {
        //group has no players
        *player_id = -1;
        return SUCCESS;
    }
    *player_id = found_max_player->getID();
    return SUCCESS;
}

StatusType playersManager::GetAllPlayersByLevel(int group_id, int **players, int *numOfPlayers) {

    if (group_id == 0 || players == nullptr || numOfPlayers == nullptr) {
        return INVALID_INPUT;
    }


    if (group_id < 0) {
        if (playerslevel_tree == nullptr) {
            //there is no players
            *players = nullptr;
            *numOfPlayers = 0;
            return SUCCESS;
        }

        *players = (int *) malloc(sizeof(int) * (playerslevel_tree->getLenght()));
        if (*players == nullptr) {
            return ALLOCATION_ERROR;
        }

        playerLevel *temp_array = static_cast<playerLevel *>( malloc(
                sizeof(playerLevel *) * (playerslevel_tree->getLenght())));
        int i = 0;
        if (temp_array == nullptr) {
            return ALLOCATION_ERROR;

        }
        playerslevel_tree->inOrder(&i, playerslevel_tree->getRoot(), &temp_array);
        int *players_array = (int *) (malloc(sizeof(int) * (playerslevel_tree->getLenght())));
        if (players_array == nullptr) {
            return ALLOCATION_ERROR;
        }
        int l =playerslevel_tree->getLenght();
        for (int j = 0; j < l; j++) {
            players_array[l-j-1] = temp_array[j].getID();
        }
        free(temp_array);
        *players = players_array;
        *numOfPlayers = playerslevel_tree->getLenght();
    }

    if (groups_tree == nullptr)// group tree is empty ??????
    {
        //there is no groups therefore there is no group with the given id
        return FAILURE;
    }

    group temp_group = group(group_id);
    avl_node<group> *found_group = groups_tree->findNode(&temp_group, groups_tree->getRoot());
    if (found_group == nullptr) {
        return FAILURE;// there is no group with the given group id
    }
    if (found_group->getData()->players == nullptr) //the tree is empty
    {
        //there is no players in the group
        *players = nullptr;
        *numOfPlayers = 0;
        return SUCCESS;
    }

    avl_tree<playerLevel> *found_tree = found_group->getData()->players;
    playerLevel *temp_array = static_cast<playerLevel *>( malloc(
            sizeof(playerLevel *) * (found_tree->getLenght())));
    int i = 0;
    if (temp_array == nullptr) {
        return ALLOCATION_ERROR;
    }
    found_tree->inOrder(&i, found_tree->getRoot(), &temp_array);

    int *players_array = (int *) (malloc(sizeof(int) * (playerslevel_tree->getLenght())));
    if (players_array == nullptr) {
        return ALLOCATION_ERROR;
    }
    int m =playerslevel_tree->getLenght();
    for (int j =0; j <m; j++) {
        players_array[m-j-1] = temp_array[j].getID();
    }
    free(temp_array);
    *players = players_array;
    *numOfPlayers = found_tree->getLenght();
    return SUCCESS;
}

StatusType playersManager:: GetGroupsHighestLevel (int numOfGroups, int **Players){
    if (numOfGroups<1 || Players== nullptr)
    {
        return INVALID_INPUT;
    }
    if (not_empty_groups == nullptr )
    {
        return FAILURE;
    }
    if (not_empty_groups->getLenght() < numOfGroups )
    {
        return FAILURE;
    }
    group** temp = reinterpret_cast<group **>((group *) malloc(sizeof(group) * numOfGroups));
    if (temp == nullptr)
    {
        return FAILURE;
    }
    Players = reinterpret_cast<int **>((int *) malloc(sizeof(int) * numOfGroups));
    if (Players == nullptr)
    {
        return FAILURE;
    }
    int i=0;
    not_empty_groups->inOrderByLenght(&i,not_empty_groups->getRoot(),temp,numOfGroups);
    for (int j=0; j<numOfGroups; j++)
    {
        *Players[j]=temp[j]->max_player->getID();
    }
    free(temp);
    return SUCCESS;
}


void playersManager:: Quit()
{
    if (playersid_tree == nullptr)
    {
        //there is no players
        if (groups_tree == nullptr)
        {
            return ; // there is no groups
        }

        groups_tree->deleteAvlTree(groups_tree->getRoot());
        delete (groups_tree);
        groups_tree= nullptr;
    }

//delete the players level tree
    playerslevel_tree->deleteAvlTree(playerslevel_tree->getRoot());
    delete(playerslevel_tree);
    playerslevel_tree= nullptr;

// delete players in players in groups and the groups
    int i=0;
    group** temp_arr= reinterpret_cast<group **>((group *) malloc(sizeof(group) * groups_tree->getLenght()));
    groups_tree->inOrder(&i,groups_tree->getRoot(),temp_arr);
    for (int j=0; j< groups_tree->getLenght(); j++)
    {
        ((*temp_arr[j])).players->deleteAvlTree((*temp_arr[j]).players->getRoot());
        delete ((*temp_arr[j]).players);
        (*temp_arr[j]).players= nullptr;
        (*temp_arr[j]).players = nullptr;
        delete (temp_arr[j]);
        temp_arr[j]= nullptr;
    }
    free(temp_arr);
    temp_arr= nullptr;
    delete (groups_tree);
    groups_tree= nullptr;

    //delete players in players id tree
    playersid_tree->deleteAvlTree(playersid_tree->getRoot());
    delete(playersid_tree);
    playersid_tree= nullptr;

    // delete players in players in groups and the groups in not empty groups
    i=0;
    if (not_empty_groups != nullptr) {
        group *temp_arr_2 = (group *) malloc(sizeof(group *) * not_empty_groups->getLenght());
        not_empty_groups->inOrder(&i, not_empty_groups->getRoot(), &temp_arr_2);
        for (int j = 0; j < not_empty_groups->getLenght(); j++) {
            ((temp_arr_2[j])).players->deleteAvlTree((temp_arr_2[j]).players->getRoot());
            delete ((temp_arr_2[j]).players);
            (temp_arr_2[j]).players = nullptr;
            (temp_arr_2[j]).max_player= nullptr;
            delete (&temp_arr_2[j]);
            temp_arr_2[j] = nullptr;
        }
        free(temp_arr_2);
        temp_arr_2 = nullptr;
        delete (not_empty_groups);
        not_empty_groups = nullptr;

    }
}