#include<iostream>

template<typename T>
class MyStack{
private: 
    int defaultsize ;
    int size ;
    int incr ;
    int top1 ;
    int top2 ;
    T*  arr ;

public:

    MyStack(int _size = MAX_SIZE) {
        top1 = size = 0 ;
        defaultsize = _size ;
        top2 = defaultsize -1 ;
        arr = new T[defaultsize] ;
        incr = defaultsize ;
    }
    ~MyStack(){
        delete []arr ;
        std :: cout <<"Memory Freed" <<'\n' ;
    }

    void clear(){
        delete []arr ;
        top1 = size = 0;
        defaultsize = incr = MAX_SIZE ;
        arr = new T[defaultsize] ;
        top2 = defaultsize -1 ;
    }
    void push1


};