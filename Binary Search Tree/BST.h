#include<iostream>
#include<assert.h>
#include<stack>

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
class BST{

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

    /**
     * @brief making an ordered BST from an sorted array using binary search
     * 
     * @param arr pointer to the original array
     * @param low lower bound of the array
     * @param high upper bound of the arr
     * @return node<T>* 
     */
    node<T>* makeBST(T* arr , int low , int high){
        if(low >= high) return NULL ;
        int mid = (low+high)/2 ;
        //create the node
        node<T>* _root = new node<T>(arr[mid]) ;
        
        //go to left 
        _root->left = makeBST(arr,low, mid) ;

        //go to right
        _root->right = makeBST(arr,mid+1 , high) ;

        return _root ;
    }
    void makeBST(T* arr , int low , int high,node<T>*& _root = NULL){
        if(low >= high) return ;
        int mid = (low+high)/2 ;
        _root = new node<T>(arr[mid]) ;
        makeBST(arr,low, mid,_root->left) ;
        makeBST(arr,mid+1 , high, _root->right) ;

    }

    void PreOrder(node<T>* _root){
        if(_root == NULL) return ;
        std::cout << _root->item <<" " ;
        if(!_root->left && !_root->right) return ;
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
     * @brief Get the Min data
     * the Min must be in the left most child/leaf of the BST
     * @param _root root of the tree
     * @return node<T>* the node containing the minimum value
     */
    node<T>* getMin(node<T>* _root){
        
        //node<T>* cur = _root ;
        //while(cur->left) cur = cur->left ;

        //return cur ;
        if(!_root->left) return _root ;
        return getMin(_root->left) ;
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
        if(_root->item > item) _root->left = deleteItem(_root->left, item) ;

        //if the item is greater than current node item then go to right 
        else if(_root->item < item) _root->right = deleteItem(_root->right, item) ;

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
            //find the maximum item/key in the left subtree of that node 
            //assign the value in current node
            //recursively call deleteItem to remove the MaxNode of of the left subtree from the current updated node 


            node<T>* temp = getMax(_root->left) ;
            _root->item = temp->item ;
            _root->left = deleteItem(_root->left, temp->item) ;

        }

        return _root ;
    }

    /**
     * @brief finding the KthSmallest key
     * 
     * @param _root root of the BST
     * @param k the  ?th least element we want 
     * @return node<T>* node with the found Kth smallest value
     */

    node<T>* KthSmallest(node<T>* _root, int &k){
        if(_root == NULL){
            return NULL ;
        }
        //go to left 
        node<T>* temp = KthSmallest(_root->left, k) ;
        //if temp exists then return to that node
        if(temp){
            return temp ;
        }
        k-- ;
        if(!k) return _root ;

        //otherwise go to right
        return KthSmallest(_root->right, k) ;
    }

    int getHeight(node<T>* _root){
        if(_root == NULL) return -1 ;
        int left = getHeight(_root->left) ;
        int right = getHeight(_root->right) ;

        return std::max(left+1,right+1) ;
    }

public:
    BST(){
        root = NULL ;
    }
    //making a balanced binary tree from a sorted array
    BST(T* arr , int low , int high){
        //root = makeBST(arr,low,high) ;
        root = NULL ;
        makeBST(arr,low,high,root) ;
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

    node<T>* getRoot(){
        return root ;
    }

    const T& KthSmallest(int k){
        node<T>* res = KthSmallest(root,k) ;
        if(res == NULL){
            std::cout <<"There are lesser Nodes" <<'\n' ;
        }
        if(res) return res->item ;
    }

    int getHeight(){
        return getHeight(root) ;
    }


};

/**
 * @brief finding the Kth Largest key
 * 
 * @param _root root of the BST
 * @param k the  ?th max element we want 
 * @return node<T>* node with the found Kth largest value
 */
template< typename T >
void findKthLargest(node<T>* _root, int& k){
    if(_root == NULL || k<=0) return ;

    findKthLargest(_root->right, k); 
    k-- ;
    if(!k){
        std::cout << "Kth Largest element is : " <<_root->item ;
        return ; 
    }
    findKthLargest(_root->left,k) ;
}

template< typename T >
void findKthLargest(BST<T>& bst,int k){
    findKthLargest(bst.getRoot() , k) ;
}
template<typename T>
void preOrderIterative(node<T>* _root){
    if(_root == NULL) return ;
    node<T>* cur = _root ;
    std::stack<node<T> *>st ;
    while(true){
        if(cur){
            st.push(cur) ;
            std::cout << cur->item <<" " ;
            cur = cur->left ;
        }
        else{
            if(st.empty()) {
                std::cout <<'\n' ;
                return ; 
            }
            cur = st.top() ;
            st.pop() ;
            cur = cur->right ; 
        }
    }
    
}

template<typename T>
void InOrderIterative(node<T>* _root){
    if(_root == NULL) return ;
    node<T>* cur = _root ;
    std::stack<node<T> *>st ;
    while(true){
        if(cur){
            st.push(cur) ;
            cur = cur->left ;
        }
        else{
            if(st.empty()) {
                std::cout <<'\n' ;
                return ; 
            }
            cur = st.top() ;
            std::cout << cur->item <<" " ;
            st.pop() ;
            cur = cur->right ; 
        }
    }
    
}