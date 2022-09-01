#ifndef LLStack_H
#define LLStack_H

#include<iostream>
#include<assert.h>
#include"Stack.h"

template<typename T>
struct node{
    node<T>* next ;
    T  item ;

    node(){
        this->next = NULL ;
    }

    node(T item){
       this->next = NULL ;
       this->item  = item ;
    }
};

template <typename T>
class LLStack: public Stack<T>{

private:
    node<T>* top ;
    int size ;

public:
    LLStack(){
        top = NULL ;
        size = 0 ;
    }
    LLStack(T* array , int lenarray , int memory = 0){
        top = NULL ;
        size = 0 ;
        for(int i = 0 ; i< lenarray ;i++) push(array[i]) ;
    }

    ~LLStack(){
        if(top) clear() ;
        //std::cout << "Memory Freed\n" ;
    }

    void clear(){
        while(top){
            node<T>* temp = top ;
            top = top->next ;

            delete temp ;
        }
        size  = 0 ;
    }

    void push(const T& item){
        node<T>* temp = new node<T>(item) ;
        if(top == NULL){
            top = temp ;
            size++ ;
            return ;
        }
        temp->next = top ;
        top = temp ;

        size++ ;
    }

    T pop(){
        if(top == NULL) std::cout <<"null" <<'\n' ;
        if(top){
            node<T>* temp = top ;
            T t_item = top->item ;
            top = top->next ;
            delete temp ;
            size-- ;

            return t_item ;
        }
    }

    int length()const{
        return size ;
    }

    T& topValue()const{
        assert(size > 0);
        return top->item ;
    }
    void setDirection(int _dir){
        //Nothing ;
    }

};
#endif
