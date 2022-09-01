#include<iostream>
#include<string>
#include<fstream>
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
    std::ifstream input("input.txt") ;

    while(!input.eof()){
        std::string str ;
        char ch ;
        int n ;
        input >> ch ;
        switch (ch)
        {
        case 'F':
            input >> n ;
            if(bst.find(n)) std::cout <<"True" ;
            else std::cout <<"False" ;
            std::cout <<'\n' ;
            break;
        case 'I':
            input >> n ;
            bst.insert(n) ;
            print(bst) ;
            std::cout <<'\n' ;
            break ;
        case 'T':
            input >> str ;
            if(str == "In") bst.InOrder() ;
            else if(str == "Pre") bst.PreOrder() ;
            else if(str == "Post") bst.PostOrder() ;

            std::cout << '\n' ;
            break ;
        case 'D':
            input >> n ;
            if(bst.find(n)){
                bst.deleteItem(n) ;
                print(bst) ;
            }
            else std::cout <<"Invalid Operation" ;
            std::cout <<'\n' ;
        default:
            break;
        }
    }
    input.close() ;

}
