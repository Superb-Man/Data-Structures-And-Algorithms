#include<iostream>
#include<assert.h>

template<typename T>
struct node{
    node<T>* left ;
    node<T>* right ;
    T item  ;
    node(const T& _item ,node<T>* _left = NULL , node<T>* _right = NULL){
        item = _item ;
        left = _left ;
        right = _right ;
    }
};

template<typename T>
class BST {

private:
    node<T>* root ;
    /**
     * creating new nodes
     * 
     * @param _root 
     * @param item the element needs to be inserted
     * @return node<T>* pointer to the root
     */
    node<T>* insert(node<T>* _root, const T& item){
        //create a new node 
        if(_root == NULL) {
            _root = new node<T>(item) ;
        }
        //go to left 
        else if(item < _root->item) {
            _root->left = insert(_root->left, item) ;
        }
        //go to right
        else{   
            _root->right = insert(_root->right, item) ;
        }
        return _root ;
    }

    void PreOrder(node<T>* _root){
        if(_root == NULL) return ;
        std::cout << _root->item <<" " ;
        //if(!_root->left && !_root->right) return ;
        PreOrder(_root->left) ;
        PreOrder(_root->right) ;
    }

    void PostOrder(node<T>* _root){
        if(_root == NULL) return ;
        PostOrder(_root->left) ;
        PostOrder(_root->right) ;
        std::cout << _root->item <<" " ;
    }

    void InOrder(node<T>* _root){
        if(_root == NULL) return ;
        InOrder(_root->left) ;
        std::cout << _root->item <<" " ;
        InOrder(_root->right) ;
    }

    /**
     * @brief deleting all nodes calling the nodes recursively
     * 
     * @param _root pointer to the root
     */
    void removeSubTree(node<T>* _root){
        if(!_root) return ;
        removeSubTree(_root->left) ;
        removeSubTree(_root->right) ;

        //deleting nodes
        delete _root ;
    }

    /**
     * @brief Get the Max data
     * the Max must be in the right most child/leaf of the BST
     * @param _root root of the tree
     * @return node<T>* the node containing the maximum value
     */

    node<T>* getMax(node<T>* _root){
        if(!_root->right) return _root ;
        return getMax(_root->right) ;
    }

    /**
     * @brief finding the element 
     * 
     * @param _root root of the tree 
     * @param item the data needs to be found
     * @return true data present in the BST
     * @return false data not present in the BST
     */
    bool find(node<T>* _root , const T& item){
        if(_root == NULL) return false ;
        if(_root->item == item) return true ;

        //if the item is lesser than current node item then go to left 
        if(item < _root->item)  return find(_root->left, item) ;
        
        //if the item is greater than current node item then go to right 
        else if(item >= _root->item)   return find(_root->right, item) ;
    }

    /**
     * @brief deleting a node and reordering the nodes in BST
     * 
     * @param _root root of the tree
     * @param item data needs to be deleted
     * @return node<T>* root of the BST
     */
    node<T>* deleteItem(node<T>* _root, const T& item){
        if(_root == NULL) return _root ;

        //if item is lesser than current node item go to left
        if(item < _root->item) _root->left = deleteItem(_root->left, item) ;

        //if the item is greater than current node item then go to right 
        else if( item > _root->item ) _root->right = deleteItem(_root->right, item) ;

        else {
            if(!_root->right && !_root->left){
                return NULL ;
            }
            //only if the right child exists
            else if(!_root->left){
                node<T>* temp = _root->right ;
                delete _root ;
                return temp ;
            }

            //only if the left child exists
            else if(!_root->right){
                node<T>* temp = _root->left ;
                delete _root ;
                return temp ;
            }

            //Both of the child exists
            //find the maximum item in the left subtree of that node 
            //assign the value in current node
            //recursively call deleteItem to remove the MaxNode of of the left subtree from the current updated node 


            node<T>* temp = getMax(_root->left) ;
            _root->item = temp->item ;
            _root->left = deleteItem(_root->left, temp->item) ;

        }

        return _root ;
    }
    //PreOrder Traversal !
    void print(node<T>* _root){
        if(_root == NULL) return ;
        std::cout << _root->item ;
        if(!_root->left && !_root->right) return ;
        std::cout <<"(" ;
        print(_root->left) ;
        std::cout <<")" ;
        std::cout <<"(" ;
        print(_root->right) ;
        std::cout << ")" ;
    }


public:
    BST(){
        root = NULL ;
    }

    ~BST(){
        removeSubTree(root) ;
    }

    void insert(const T& item){
        root = insert(root, item) ;
    }

    void PreOrder(){
        PreOrder(root) ;
    }
    void PostOrder(){
        PostOrder(root) ;
    }
    void InOrder(){
        InOrder(root) ;
    }

    bool find(const T& item){
        return find(root, item) ;
    }

    void deleteItem(const T& item){
        root = deleteItem(root, item) ;
    }

    void print(){
        print(root) ;
    }



};