#ifndef LQueue_H
#define LQueue_H

#include<iostream>
#include"Queue.h"

template <typename T>
struct node{
    T item ;
    node<T>* prev ;
    node<T>* next ;

    node(const T& _item){
        item = _item ;
        prev = next = NULL ;
    }
};

template<typename T>
class LQueue:public Queue<T>{

private:
    int size ;
    node<T>* head ;
    node<T>*tail ;

    T remove(bool _front = true){
        if(_front == true && head){
            node<T>* temp = head ;
            T data = temp->item ;
            
            head = head->next ;
            if(head) head->prev = NULL ;
            
            delete temp ;
            size-- ;
            return data ; 
        }
        else if(_front == false && tail){
            node<T>* temp = tail;
            T data = temp->item ;
            
            tail = tail->prev ;
            if(tail) tail->next = NULL ;
            
            delete temp ;
            size--;
            return data ; 
        }
    }
public:
    LQueue(int _size = 0 ){
        head = tail = NULL ;
        size = 0;
    }

    ~LQueue(){
        if(head) clear() ;
        //std::cout <<"Memory Freed'\n" ;
    }

    void clear(){
        while(head){
            remove(true) ;
        }
    }

    void enqueue(const T& item){
        node<T>* temp = new node<T>(item) ;
        if(head == NULL){
            head = tail = temp ;
            size++ ;
            return ;
        }
        tail->next = temp ;
        tail->next->prev = tail ;
        tail = tail->next ;
        size++ ;
    }

    T dequeue(){
        remove(true) ;
    }

    int length(){
        return size ;
    }

    T frontValue(){
        return head->item ;
    }
    
    T rearValue(){
        return tail->item ;
    }

    T leaveQueue(){
        remove(false) ;
    }
    
};

#endif