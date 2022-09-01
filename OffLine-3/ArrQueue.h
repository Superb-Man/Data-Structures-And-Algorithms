#ifndef ArrQueue_H
#define ArrQueue_H

#include<iostream>
#include"Queue.h"
#define MAX_SIZE 10
/**
 * Author - Mr Nobody.
 * Circular Queue Implementation using array
 * dequeue O(1)
 * enqueue O(1)
 * leavQqueue O(1)
 * There's a thing to handle manually , thats the size of queue.
 * As we are counting the length using modulo operation .
 * For a defaultsize n we can get maximum n+1 size , but we have n position .so any of the two size will be same that is zero. 
 * That is handled carefully   
 */

template<typename T>
class ArrQueue:public Queue<T>{

private:
    int front ;
    int rear ;
    T* arr ;
    int defaultsize ;
    int incr ;
    bool isAllocated ;

    void copy(T* newArr , T* prevArr, int prevSize){
        for(int i = 0 ; i < prevSize ;i++){
            newArr[i] = prevArr[(front+i)%defaultsize] ; 
        }
    }

    void resize(){
        
        //std::cout << "resize needed\n" ;
        defaultsize+=incr ;
        T* newArr = new T[defaultsize] ;
        copy(newArr ,arr, length()) ;

        delete [] arr ;
        //defaultsize+=incr ;
        front = 0 , rear = length() -1 ;
        arr = newArr ;
        //arr = new T[defaultsize] ;
        //copy(arr, newArr, length()) ;

        //delete [] newArr ;
    }

    T remove(bool _front = true){
        if(rear == front){
            int pos = front ;
            rear = -1 ; front = 0 ;
            return arr[pos] ;
        }
        if(_front){
            int pos = front ;
            front = (front+1)%defaultsize ;
            return arr[pos] ;
        }
        else {
            int pos = rear ;
            rear = (rear-1) % defaultsize ;
            return arr[pos] ;
        }
    }
public:
    ArrQueue(int _size = MAX_SIZE){
        defaultsize = incr = _size ;
        arr = new T[defaultsize] ;
        front = 0 ;
        rear = -1 ;
        isAllocated = false ;
    }

    ArrQueue(T*& array , int _size){
        isAllocated = true ;
        defaultsize = incr = _size ;
        arr = array ;
        front = 0 ; rear = -1 ;
    }

    ~ArrQueue(){
        if(rear !=1 && isAllocated == false) delete [] arr ;
    }
    void clear(){
        delete []arr ;
        defaultsize = incr = MAX_SIZE ;
        arr = new T[defaultsize] ;
        front = 0;
        rear = -1 ;
    }

    void enqueue(const T& item){

        if(length() == defaultsize) resize() ;

        if(rear == -1) 
        {
            rear++ ;
            arr[rear%defaultsize] = item ;
        }
        else if ((rear +1)%defaultsize != front) {
            rear = (rear+1) % defaultsize ;
            arr[rear] = item ;
        } 
    }

    T dequeue(){
        remove(true) ;
    }

    int length(){
        int modulo = (rear+defaultsize - front+1) % defaultsize ;
        return modulo == 0 && rear != -1 ? defaultsize : modulo ;  
    }

    T frontValue(){
        return arr[front] ;
    }
    
    T rearValue(){
        return arr[rear] ;
    }

    T leaveQueue(){
        remove(false) ;
    }
    
};

#endif