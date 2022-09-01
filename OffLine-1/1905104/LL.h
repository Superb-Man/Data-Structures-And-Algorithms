#ifndef LL_h
#define LL_h

#include<iostream>
#include<stdlib.h>
#include<assert.h>
#include"List.h"

template<class T>
struct node{
    node<T>* prev ;
    node<T>* next ;
    T  item ;

    node(){
        this->next = NULL ;
        this->prev = NULL ;
    }

    node(T item){
        this->prev = NULL ;
       this->next = NULL ;
       this->item  = item ;
    }
};

template< class T >
class LList: public List<T>{

private: 
    int size ; 
    node<T> *head,*tail,*cur;

public:
    /**
     * constructor for initialization or an empty linked list
     * Only a dummy node
     */
    LList() {
        size = 0 ;
        head = tail = cur = new node<T> ;
    }

    LList(T* _arr , int _size = 0 , int _memorysize = 0){
        size = 0 ;
        head = tail = cur = new node<T> ;
        int i = 0 ;
        while(i++ < _size){
            append(_arr[i-1]) ;
        }
    }

    // Destructor 
    ~LList(){
        if(head->next) clear() ; // if the list is not clear
        delete head ;
        //std::cout <<"Memory freed" <<'\n' ;
        
    }

    void clear(){
        while(head){
            cur = head ;
            head = head->next ;
            delete cur ;
        }
        
        head = tail = cur = new node<T> ;

        size = 0 ;
    }

    /**
     * @param item -> Inserts an element at the current location.
     * No return type
     * O(1)
     */
    void insert(const T& item){
        node<T>* temp = new node<T>(item) ;
        temp->prev = cur ;
        temp->next = cur->next ;
        cur->next = temp ;
        if(cur->next->next) cur->next->next->prev = temp ;
        ++size ; 
    }

    /**
     * @param item -> insert an element at the end of the list
     * No return type
     * O(1)
     */

    void append(const T& item){
        node<T>* temp = new node<T>(item) ;
        tail->next = temp ;
        temp->prev = tail ;
        tail = temp ;

        ++size ;
    }

    /**
     * Remove current node
     * @return  the element of that current node
     * O(1)
     */

    T remove(){
        assert(cur->next != NULL) ;
        node<T>* temp = cur->next ;
        T item = cur->next->item ;
        if (tail == cur->next) tail = cur ;
        cur->next = cur->next->next ;
        if(cur->next) cur->next->prev = cur ;
        delete temp ;

        if(!cur->next) prev() ;
        size-- ;
        
        return item ;
    }

    void moveToStart() {
        if(cur != head) cur = head ; // current set to dummy node of the list
    }

    void moveToEnd(){
        if(tail->prev) cur = tail->prev ;
    }

    /**
     * set the current node to previous one
     * O(1)
     */
    void prev(){
        if(!cur->prev ) return ;
        cur = cur->prev ;
        
        
    }

    void next(){
        if(cur->next && cur->next != tail) cur = cur->next ;
    }

    int length() const{
        return size ;
    }

    int currPos(){
        if(cur == head) return 0 ;
        int i = 0 ;
        node<T>* temp = head ;
        while(temp != cur) {
            temp = temp->next ;
            i++ ;
        }

        return i ;
    }

    /**
     * @param idx the index that the current node needs to be set 
     * No return type 
     * 
     */

    void moveToPos(int idx){
        assert(idx > 0 || idx < size) ;

        cur = head ;
        for(int i = 0 ; i < idx ;i++ ){
            if(cur == tail) continue ;
            cur = cur->next ;
        }
        
    }

    /**
     *
     * @return current node element
     */ 
    T getValue() const{
        assert(size > 0) ;
        return cur->next->item ;
    }
    
    /**
     * @param item -> may be in the list or not 
     * @return the position of the given item
     * 
     */

    int Search(const T& item){
        node<T>* temp = head->next ;
        int i = 0 ;
        while(temp) {
            if(temp->item == item) return i ;
            temp = temp->next ; i++ ;
        }
        return -1 ;  
        
    }


};

#endif