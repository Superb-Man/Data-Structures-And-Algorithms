#include<iostream>
#include<vector>
#include<stdlib.h>
#include"heap.h"

int main(){
    vector<int> v ;
    Heap h(16) ;
    for(int i = 1 ; i <= 20 ;i++){
        int x =rand()%100 ;
        std::cout << "_myheap trying to Insert : " << x << '\n' ;
        v.push_back(x) ;
        h.insert(x) ;

    }

    while(h.size()){
        int del = h.getMax() ;
        std::cout << del <<" ";
        h.deleteKey() ;
    }
    std::cout <<'\n' ;


    //Heap heapp(v) ;
    heapsort(v) ;
    for(int i = 0 ; i < v.size() ;i++) std::cout << v[i] <<" " ;


    /*while(!_myheap.isempty()) {
        std::cout << "_myheap Top element : " << _myheap.top() <<'\n' ;
        _myheap.pop() ;
    }

    yourheap.push(76) ;

    while(!yourheap.isempty()) {
        std::cout << "yourheap Top element : " << yourheap.top() <<'\n' ;
        yourheap.pop() ;
    }*/

}
// ./OffLine-2/main.exe
