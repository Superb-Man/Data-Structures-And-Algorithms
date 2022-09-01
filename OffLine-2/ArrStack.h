#ifndef ArrStack_H
#define ArrStack_H

#include<iostream>
#include<assert.h>
#include"Stack.h"
#define MAX_SIZE 10

template <typename T>
class ArrStack: public Stack<T>{

private: 
    int defaultsize ;
    int dir ;
    int incr ;
    int top ;
    T*  arr ; 
    bool isAllocated ;

    void copy( T* a, T* b ,int _bsize, int _dir = 1) {
        if(_dir == 1){
            for(int i =  0 ; i< _bsize ;i++)  a[i] = b[i] ;
        }
        else{
            for(int i = _bsize-1 ;i >=0 ;i--)   a[i] = b[i] ;
        }
    }

    void update() {
        int size = length() ;
        T* _arr = new T[size] ;
        copy(_arr , arr, size, dir) ;
        
        delete [] arr ;

        defaultsize+=incr;
        arr = new T[defaultsize] ;
        
        copy(arr,_arr, defaultsize, dir) ;

        delete [] _arr ;
    }

public:

    ArrStack(T* array ,int _size,int _dir = 1){
        arr = array ;
        defaultsize = incr = _size ;
        isAllocated = false ;
        setDirection(_dir) ;
    }

    ArrStack(int _size = MAX_SIZE) {
        defaultsize = incr =_size ;
        arr = new T[defaultsize] ;
        isAllocated = true ;
        setDirection() ;
    }
    ~ArrStack(){
        if(isAllocated == true) delete []arr ;
        //std :: cout <<"Memory Freed" <<'\n' ;
    }

    void clear(){
        if(isAllocated == true){
            delete [] arr ;
            defaultsize = incr = MAX_SIZE ;
            setDirection(dir) ;
            arr = new T[defaultsize] ;
        }
    }

    void push(const T& item){
        if(isAllocated == true && length() == defaultsize) {
            update() ;
        }
        arr[top] = item ;
        dir == 1? top++ : top-- ;
    }
    T pop(){
        return dir == 1? arr[--top] : arr[++top] ;
    }

    int length()const{
        return dir == 1? top : defaultsize - top -1 ;
    }
    T& topValue() const{
        return arr[top-dir] ;
    }
    void setDirection(int _dir = 1){
        dir = _dir ;
        top = dir == 1? 0 : defaultsize -1 ;
    }

};

#endif