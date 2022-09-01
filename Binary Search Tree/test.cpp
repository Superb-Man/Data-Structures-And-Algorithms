#include<iostream>
#include"BST.h"

template< typename T>
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

template< typename T>
void print(BST<T>& bst){
    print(bst.getRoot()) ;
}



int main(){
    BST<int>bst ;
    bst.insert(8) ;
    bst.insert(10) ;
    bst.insert(3) ;
    bst.insert(2) ;
    bst.insert(14) ;
    bst.insert(6) ;
    bst.insert(4) ;
    bst.insert(13) ;
    bst.insert(7) ;
    if(bst.find(14)) std::cout <<"TRUE" <<'\n' ;
    preOrderIterative(bst.getRoot()) ;
    bst.PreOrder() ;
    std::cout <<'\n' ;
    //postOrderIterative(bst.getRoot()) ;
    bst.PostOrder() ;

    std::cout <<'\n' ;
    int ara[10] = {1,2,3,4,5,6,7} ;
    BST<int>bstt(ara,0,7) ;
    InOrderIterative(bst.getRoot()) ;
    bstt.InOrder() ;
    std::cout <<'\n' ;
    print(bstt) ;
    std::cout <<'\n';
    bst.InOrder() ;
    std::cout <<'\n' ;
    std::cout << "Kth Smallest element is : " << bst.KthSmallest(3) <<'\n' ;
    findKthLargest(bst,3) ;
    std::cout <<'\n' ;
    std::cout<<bstt.getRoot()->item <<'\n' ;
    std::cout <<'\n' ;
    bst.deleteItem(8) ;
    std::cout << bst.getHeight() <<'\n' ;
    bst.InOrder() ;
}