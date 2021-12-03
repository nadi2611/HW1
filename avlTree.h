#include<iostream>
#include<cstdio>
#include<sstream>
#include<algorithm>
#define pow2(n) (1 << (n))
using namespace std;

template <class T>
// We defined avl_node class to perform actions on avl's tree nodes.
class avl_node{
    T* data;
    avl_node* right_node;
    avl_node* left_node;
    avl_node* parent_node;
public:

    avl_node():data(nullptr),right_node(nullptr), left_node(nullptr), parent_node(nullptr){}
    explicit avl_node( T* new_data) : data(new_data), right_node(nullptr), left_node(nullptr), parent_node(nullptr){}
    ~avl_node() = default;

    T* getData(){
        return data;
    }

    void insertLeftNode(avl_node* left){
        left_node = left;
    }

    void insertRightNode(avl_node* right){
        right_node = right;
    }

    void insertParentNode(avl_node* parent){
        parent_node = parent;
    }

    void replaceData( T* new_data){ // Replace data worked great!
        data = new_data;
    }
    avl_node* getLeftNode(){
        return left_node;
    }

    avl_node* getRightNode(){
        return right_node;
    }

    avl_node* getParentNode(){
        return parent_node;
    }
};

template<class T>
class avl_tree{
    avl_node<T>* root;
    int length; // TODO


public:
    avl_tree(): root(nullptr), length(0){} // TODO DONE
    avl_tree(avl_node<T>* root1, int new_length):root(root1), length(new_length){}
    ~avl_tree();
    void deleteAvlTree(avl_node<T>* root);
    bool insertAvlNode(avl_node<T>* new_node); // TODO DONE
    void insertAvlNodeHelperFunc(avl_node<T>* new_node, avl_node<T>* root);
    int height(avl_node<T>* base);// TODO DONE
    int balanceFactor(avl_node<T>* base);// TODO DONE
    void inOrder(int* i, avl_node<T>* root, T** array);
    avl_node<T>* rotateLL (avl_node<T>* base); //TODO DONE
    avl_node<T>*  rotateLR (avl_node<T>* base); //TODO DONE
    avl_node<T>*  rotateRR (avl_node<T>* base); //TODO DONE
    avl_node<T>*  rotateRL (avl_node<T>* base);// TODO DONE
    avl_node<T>* findNode(T* data, avl_node<T>* root);// TODO DONE
    avl_node<T>* removeNode(T* data, avl_node<T>* root); // TODO DONE
    avl_node<T>* findMaxNode(avl_node<T>* root); // TODO DONE
    avl_node<T>* getRoot(); //TODO DONE
    avl_node<T>* buildTree(avl_node<T>* father, T* array, int start, int end);
    //void inOrderHelperFun(int* i,avl_node<T>* root, T* array);
    int getLenght();
    void setRoot (avl_node<T>* new_root,int new_len);
    void inOrderByLenght(int* i, avl_node<T>* root, T** array, int len);

};




template <class T>
int avl_tree<T>::getLenght() {
    return this->length;
}

template<class T>
void avl_tree<T>:: inOrderByLenght(int* i, avl_node<T>* root, T** array, int len){

    if (root == NULL || *i == len) {
        return;
    }

    inOrder(i,root->getLeftNode(),array);
    array[*i] = (root->getData());
    *i = *i + 1;
    inOrder(i,root->getRightNode(),array);
}


template <class T>
void avl_tree<T>::setRoot (avl_node<T>* new_root,int new_len){
    root=new_root;
    length=new_len;
}




template<class T>
void avl_tree<T>:: inOrder(int* i, avl_node<T>* root, T** array){
    if (root == NULL) {
        return;
    }



    inOrder(i,root->getLeftNode(),array);
    array[*i] = (root->getData());
    *i = *i + 1;
    inOrder(i,root->getRightNode(),array);



}

template<class T>
avl_node<T>* avl_tree<T>::buildTree(avl_node<T>* father, T* array, int start, int end){

    if (start > end){
        return nullptr;
    }

    int mid = (start + end)/2 ;

    avl_node<T>* tree_root = new avl_node<T>();
    *tree_root->getData() = array[mid];

    tree_root->insertParentNode(father);
    tree_root->insertLeftNode(buildTree(tree_root,array,start,mid - 1));
    tree_root->insertRightNode(buildTree(tree_root,array,mid + 1,end));

    return tree_root;

}

template<class T>
avl_node<T>* avl_tree<T>::getRoot() {
    return root;
}
template<class T>
avl_node<T>* avl_tree<T>::findMaxNode(avl_node<T> *root) {
    if(root -> getRightNode() == nullptr){
        return root;
    }

    return findMaxNode(root -> getRightNode());

}


template<class T>
avl_node<T>* avl_tree<T>::removeNode(T* data, avl_node<T> *root) {   // We implement the algorithim for removing node from avl tree.

    if(root == nullptr){

        return root;

    }

    if(*(root -> getData()) > *data){

        removeNode(data, root->getLeftNode());

    }

    else if(*(root -> getData()) < *data){

        removeNode(data, root->getRightNode());

    }

    else {// We found the node

        if(root -> getLeftNode() == nullptr && root->getRightNode()== nullptr)// the node is a leaf
        {
            avl_node<T>* parent_node = root->getParentNode();

            if(parent_node -> getRightNode() == root){

                parent_node->insertRightNode(nullptr);

            }
            else {

                parent_node->insertLeftNode(nullptr);

            }
            delete data;////+++
            delete root;
            root= nullptr;
            length--;
        }

        else if (root ->getRightNode()== nullptr)
        {
            avl_node<T>* parent_node = root->getParentNode();

            if(parent_node -> getRightNode() == root){

                parent_node->insertRightNode(root->getLeftNode());

            }
            else {

                parent_node->insertLeftNode(root->getLeftNode());

            }

            root=root ->getLeftNode();
            delete data; ///// +++
            delete root;
            length--;
        }
        else if (root ->getLeftNode()== nullptr)
        {
            avl_node<T>* parent_node = root->getParentNode();

            if(parent_node -> getRightNode() == root){

                parent_node->insertRightNode(root -> getRightNode());

            }
            else {

                parent_node->insertLeftNode(root-> getRightNode());

            }

            root=root ->getRightNode();
            delete root;
            length--;
        }
        else// the root has more than one child
        {
            avl_node<T>* maximum_node = findMaxNode(root -> getLeftNode());

            root->replaceData(maximum_node -> getData());

            removeNode(root -> getData(), root -> getLeftNode());

        }
    }

    if(root == nullptr){
        return root;
    }

    int balance_factor = balanceFactor(root);

    if(balance_factor == 2 && balanceFactor(root -> getLeftNode()) >= 0){
        return rotateLL(root);
    }

    else if(balance_factor == 2 && balanceFactor(root -> getLeftNode()) < 0){
        return rotateLR(root);
    }

    else if(balance_factor == -2 && balanceFactor(root -> getRightNode()) <= 0){
        return rotateRR(root);
    }
    else if(balance_factor == -2 && balanceFactor(root -> getRightNode()) > 0){
        return rotateRL(root);
    }

    return root;



}

template<class T>
avl_node<T>* avl_tree<T>::findNode(T* data, avl_node<T>* root ) {

    if(root == nullptr) return nullptr;

    if(*(root->getData()) == *data) return root;

    else if(*(root -> getData()) < *data) {
        return findNode(data, root -> getRightNode());
    }
    else {
        return findNode(data, root -> getLeftNode());
    }
}



template<class T>
int avl_tree<T>::balanceFactor(avl_node<T> *base) {
    if(base == nullptr) return 0;
    return height(base->getLeftNode()) - height(base->getRightNode());
}

template<class T>
avl_node<T>* avl_tree<T>::rotateLL(avl_node<T> *base) {

    avl_node<T>* new_base = base->getLeftNode();
    base->insertLeftNode(new_base->getRightNode());
    if (new_base->getRightNode() != nullptr)
    {
        (new_base->getRightNode())->insertParentNode(base);
    }
    new_base->insertRightNode(base);

    avl_node<T>* base_parent= base->getParentNode();
    base->insertParentNode(new_base);
    if (base_parent == nullptr){ // if base ia the root of our tree we adjust the tree.
        root =new_base;
        new_base->insertParentNode(nullptr);
        return new_base;
    }
    if (base_parent->getRightNode() == base)
    {
        base_parent->insertRightNode(new_base);
    }
    else { // base_parent->getLeftNode() = base
        base_parent->insertLeftNode(new_base);
    }
    new_base->insertParentNode(base_parent);
    return new_base;
}

template<class T>
avl_node<T>* avl_tree<T>::rotateLR(avl_node<T> *base) {

    avl_node<T>* old_base_left=base->getLeftNode();
    avl_node<T>* new_base= old_base_left->getRightNode();
    old_base_left->insertRightNode(new_base->getLeftNode());
    if (old_base_left->getRightNode() != nullptr)
    {
        (old_base_left->getRightNode())->insertParentNode(old_base_left);
    }
    new_base->insertLeftNode(old_base_left);
    base->insertLeftNode(new_base->getRightNode());
    if (base->getLeftNode() != nullptr)
    {
        (base->getLeftNode())->insertParentNode(base);
    }
    new_base->insertRightNode(base);

    old_base_left->insertParentNode(new_base);
    if (base->getParentNode() == nullptr){
        root=new_base;
        new_base->insertParentNode(nullptr);
        base->insertParentNode(new_base);
        return new_base;
    }
    avl_node<T>* base_parent=base->getParentNode();
    if (base_parent->getLeftNode()==base)
    {
        base_parent->insertLeftNode(new_base);
    }
    else {// base_parent->getRightNode()=base
        base_parent->insertRightNode(new_base);
    }
    new_base->insertParentNode(base_parent);
    base->insertParentNode(new_base);
    return new_base;
}

template<class T>
avl_node<T>* avl_tree<T>::rotateRR(avl_node<T> *base) {

    avl_node<T>* new_base = base->getRightNode();
    base->insertRightNode(new_base->getLeftNode());
    if (new_base->getLeftNode() != nullptr)
    {

        (new_base->getLeftNode())->insertParentNode(base);
    }
    new_base->insertLeftNode(base);
    avl_node<T>* base_parent= base->getParentNode();
    base->insertParentNode(new_base);
    if (base_parent == nullptr){ // if base ia the root of our tree we adjust the tree.
        root =new_base;
        new_base->insertParentNode(nullptr);
        return new_base;
    }
    if (base_parent->getRightNode() == base)
    {
        base_parent->insertRightNode(new_base);
    }
    else { // base_parent->getLeftNode() = base
        base_parent->insertLeftNode(new_base);
    }
    new_base->insertParentNode(base_parent);
    return new_base;
}

template<class T>
avl_node<T>*  avl_tree<T>::rotateRL(avl_node<T> *base) {

    avl_node<T>* old_base_right=base->getRightNode();
    avl_node<T>* new_base= old_base_right->getLeftNode();
    old_base_right->insertLeftNode(new_base->getRightNode());
    if (old_base_right->getLeftNode() != nullptr)
    {
        (old_base_right->getLeftNode())->insertParentNode(old_base_right);
    }
    new_base->insertRightNode(old_base_right);
    base->insertRightNode(new_base->getLeftNode());
    if (base->getRightNode() != nullptr)
    {
        (base->getRightNode())->insertParentNode(base);
    }
    new_base->insertLeftNode(base);

    old_base_right->insertParentNode(new_base);
    if (base->getParentNode() == nullptr){
        root=new_base;
        new_base->insertParentNode(nullptr);
        base->insertParentNode(new_base);
        return new_base;
    }
    avl_node<T>* base_parent=base->getParentNode();
    if (base_parent->getLeftNode()==base)
    {
        base_parent->insertLeftNode(new_base);
    }
    else {// base_parent->getRightNode()=base
        base_parent->insertRightNode(new_base);
    }
    new_base->insertParentNode(base_parent);
    base->insertParentNode(new_base);
    return new_base;
}

template<class T>
int avl_tree<T>::height(avl_node<T> *base) {

    if(base == nullptr){
        return -1;
    }
    else{
        int height_left = height(base->getLeftNode());
        int height_right = height(base->getRightNode());
        if(height_left > height_right) return height_left + 1;
        else return height_right + 1;
    }

}

template<class T>
void avl_tree<T>::deleteAvlTree(avl_node<T>* root) {

    if(root != nullptr){

        deleteAvlTree(root->getLeftNode());
        deleteAvlTree(root->getRightNode());
        delete(root); // After We reach the base of the recurssion we start deleting the nodes from the leaf up to the root.

    }
}

template<class T>
bool avl_tree<T>::insertAvlNode(avl_node<T>* new_node) {

    length++;
    if (new_node == nullptr) {
        return false;
    }
    if (root == nullptr)
    {
        root = new_node;
        return true;
    }

    else{

        insertAvlNodeHelperFunc(new_node, root);

    }
    return true;
}

template<class T>
void avl_tree<T>::insertAvlNodeHelperFunc(avl_node<T>* new_node, avl_node<T>* root){

    if(*(new_node->getData()) <= *(root->getData())){
        if(root->getLeftNode() != nullptr){
            insertAvlNodeHelperFunc(new_node, root->getLeftNode());
        }
        else{ // We reached the leaf
            root->insertLeftNode(new_node);
            new_node->insertParentNode(root);
        }
    }
    else {
        if (root->getRightNode() != nullptr){
            insertAvlNodeHelperFunc(new_node, root->getRightNode());
        }
        else {
            root->insertRightNode(new_node);
            new_node->insertParentNode(root);
        }
    }

    int balance_factor = balanceFactor(root);
    int balance_factor_left = balanceFactor(root->getLeftNode());
    int balance_factor_right = balanceFactor(root->getRightNode());

    if(balance_factor == 2){

        if (balance_factor_left >= 0 ){
            rotateLL(root);
        }
        else if(balance_factor_left == -1) {
            rotateLR(root);
        }
    }
    else if(balance_factor == -2){
        if(balance_factor_right <=0 ){
            rotateRR(root);
        }
        else if(balance_factor_right == 1){
            rotateRL(root);
        }
    }
}

template<class T>
avl_tree<T>::~avl_tree() {
    if(root != nullptr) deleteAvlTree(root);
}

