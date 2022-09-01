#ifndef Arr_h
#define Arr_h

#include<iostream>
#include<stdlib.h>
#include<assert.h>
#include"List.h"

#define MAX_SIZE 10
template<typename T>
class ArrList : public List<T>{

private: 
    int defaultsize ;
    int size ;
    int incr ;
    int cur ;
    T*  arr ; 

    void copy( T* a, T* b ,int _bsize) {
        for(int i = 0 ; i < _bsize ;i++) a[i] = b[i] ;
    }

    void update() {
        T* _arr = new T[size] ;
        copy(_arr , arr, size) ;
        
        delete [] arr ;

        defaultsize+=incr;
        arr = new T[defaultsize] ;
        
        copy(arr,_arr, size) ;

        delete [] _arr ;
    }

public:

    ArrList(int _size = MAX_SIZE) {
        cur = size = 0 ;
        defaultsize = _size ;
        arr = new T[defaultsize] ;
        incr = defaultsize ;
    }

    ArrList(T* _arr, int _size, int _memorysize){
        size = cur = 0 ;
        defaultsize = incr = _memorysize ;
        arr = new T[defaultsize] ;
        int i = 0 ;
        while(size <_size) {
            //if(size + 1 > defaultsize) update() ;
            //arr[size++] = _arr[i++] ;

            //or just
            append(_arr[i++]);
        }

    }

    ~ArrList(){
        delete []arr ;
        //std :: cout <<"Memory Freed" <<'\n' ;
    }

    void clear(){
        delete [] arr ;
        cur = size = 0 ;
        defaultsize = incr = MAX_SIZE ;
        arr = new T[defaultsize] ;
    }

    /**
     * @param item -> Inserts an element at the current location.
     * No return type
     * O(n)
     */

    void insert(const T& item){
        if(size + 1 > defaultsize)  update() ;
        if(size == 0) {
            arr[size++] = item ;
            return ;
        }
        ++size ;
        for(int i = size-1 ; i > cur ;i--) arr[i] = arr[i-1] ; 

        arr[cur] = item ; 
    }

    /**
     * @param item -> insert an element at the end of the list
     * No return type
     * O(1)
     */

    void append(const T& item){
        if(size + 1 > defaultsize ) {
            update() ;
        }
        arr[size++] = item ;
    }

    /**
     * Remove current position element
     * @return  the element of that current position
     * O(n)
     */

    T remove(){
        assert(size > 0) ;
        T ret = arr[cur] ;

        for(int i = cur ; i< size-1 ;i++) arr[i] = arr[i+1] ;
        if(cur == size-1) cur-- ;
        size-- ;

        return ret ;
    }

    void moveToStart() {
        cur = 0 ;
    }

    void moveToEnd(){
        if(size) cur = size-1 ;
    }

    /**
     * set the current node to previous one
     * O(1)
     */

    void prev(){
        
        if(cur) cur-- ;
    }

    void next(){
        if(cur < size-1) cur++ ; 
    }

    int length() const{
        return size ;
    }

    int currPos(){
        return cur ;
    }

    /**
     * @param idx the index that the current position to be set 
     * No return type 
     * 
     */

    void moveToPos(int idx){
        assert(idx > 0 || idx < size) ; 
        cur = idx ;
        return ;
    }

    /**
     *
     * @return current  element
     */ 

    T getValue() const{
        assert(size > 0) ;
        return arr[cur] ;
    }

    /**
     * @param item -> may be in the list or not 
     * @return the position of the given item
     * 
     */
    
    int Search(const T& item){
        for(int i = 0 ; i < size ;i++){
            if(arr[i] == item) return i ;
        }
        return -1 ;  
        
    }

};

#endif
