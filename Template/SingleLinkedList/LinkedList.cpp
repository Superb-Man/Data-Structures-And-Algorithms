/*
 * Author : Kazi Istiak Uddin Toriqe
 * implementing Single linked list with necessary methods
 */


#include<iostream>

template<class T>
struct node{
    node<T>* next ;
    T  data ;
    node(T data){
       next = NULL ;
       this->data  = data ;
    }
};

template< class T >
class list{

private: 
    int size ; 
    node<T> *head,*tail ;

public:
    
    /*
    * normal constructor list()
    * copy constructor list(list& mylist)
    */

    list(){
        this->size = 0 ;
        this->head = NULL ;
        this->tail = NULL ;
    }

    list(list& mylist){
        this->size = 0 ;
        this->head = NULL ;
        this->tail = NULL ;

        node<T>* temp =  mylist._getfront();
        
        while(temp){
            this->add(temp->data) ;
            temp = temp->next ; 
        }
    }

    
    /*
    ** ALL METHODS **
    * @ void add(T data)
    * @ void add(int idx, T data)
    * @ void deletefrombeg()
    * @ void deletefromend()
    * @ void deleteinmiddle()
    * @ node<T>*& _getfront()
    * @ int _size()
    * @ bool isempty()
    * @ void remove(int idx)
    * @ void remove(T data)
    * @ void remove(node<T>*& nod)
    * @ bool contains(T data)
    */


    /*
     * adding a new node to the list with vale
     * @param data of any type
     */
    void add(T data){
        /*
         * Alloacating the space required for a node
         * assigining a value to data variable
         * assiging next pointer to NULL
         */
        node<T>* temp = new node<T>(data);
        /*
         * This part is to join the nodes.
         * Then create the linked list .
         * Chking if the head is set to NULL or not.
         * If head is set to NULL , we assign the temp node to head.
         * It will also be the tailing node.
         * If head is not NULL , then our linked list is created..
         * Now we just have to add the nodes at the end of the list.
         */
        if(head == NULL){
            head = temp ;
            tail = head ;
            ++size ;
            return ;
        }

        tail->next = temp ;
        tail = tail->next ;
        ++size ;
    }

    
    /*
     * adding a new node to the list with value with specific position
     * @param the inserting positionn idx
     * @param data of any type
     */
    void add(int idx , T data){
        if(idx > size+1 || idx < 1){
            std::cout <<"Invalid Position" <<'\n' ;
            return ;
        }
        
        if(idx == size+1){
            add(data) ;
            ++size ;
            return ;
        }
        
        node<T>* prev = head ;
        
        while(idx--){
            if(idx == 0){
                /*
                 * creating a new node ;
                 */
                node<T>* temp = new node<T>(data) ;
                /*
                 * linking temp with prev->next ;
                 * swap the value 
                 * link prev->next with temp
                 * we have actually created the node after the given position and  swapped the value of temp and prev ;
                 */
                temp->next = prev->next ;
                std::swap(temp->data , prev->data) ;
                prev->next = temp ;
                ++size ;
                return ;
            }
            prev = prev->next ;
        }
        
        /*
        if(idx==1){
            node<T>* temp = new node<T>(data) ;
            temp->next = head ;
            head = temp ;
            ++size ;
            return ;
        }

        node<T>* prev = head ;
        idx-- ;
        while(idx-- > 1){
            prev = prev->next ;
        }
        
        node<T>* temp = new node<T>(data) ;
        temp->next = prev->next;
        prev->next = temp ;
        ++size ;
        */
    }
    
    void deletefrombeg(){
        node<T>* temp = head ;
        if(head == NULL) return ;
        head = head->next ;
        std::cout << "Deleting from beginning : " << temp->data <<'\n' ;
        delete temp ;
        size-- ;
    }
    
    void deleteinmiddle(){
        node<T> *temp , *cnt , *temp2 ;

        if(head == NULL) return ;
        
        if(head->next == NULL)  {
            delete head ;
            size-- ;
            return ;
        }

        temp  = cnt = head ;
        temp2 = NULL ;
        
        while(cnt->next != NULL) {
            temp2 = temp ;
            cnt = cnt->next->next ;
            temp = temp->next ;
            if(cnt == NULL) break ;
            
        }
        temp2->next = temp->next ;
        std::cout << "Deleting from middle : " << temp->data <<'\n' ;
        delete temp ;
        size-- ;

    }

    void deletefromend(){
        node<T> *temp ;
        if(head == NULL) return ;
        
        /*Only one node remains*/
        if(head->next == NULL){
            temp = head ;
            head = NULL ;
            tail = NULL ;
            delete temp ;
            size-- ;
            return ;
        }
        /*
         * multiple nodes
         */
        temp = head ;
        while(temp->next != NULL){
            tail = temp  ;
            temp = temp->next ;
        }
        tail->next = NULL ;
        
        std::cout << "Deleting from end : " << temp->data <<'\n' ;
        delete temp ;
        size-- ;
    }


    node<T>*& _getfront() {
        return head ;
    }
    
    int _size(){
        return size ;
    }
    
    bool isempty(){
        return !size ;
    }
    /* @ idx - which position needs to be deleted
     * if not satisfied on the beginning conditions call the overloaded remove for a node 
     * O(n) complexity
     */
    void remove(int idx){
        if(idx > size+1 || idx < 1){
            std::cout <<"Invalid Position" <<'\n' ;
            return ;
        }
        
        if(idx==1){
            deletefrombeg() ;
            return ;
        }
        
        if(idx == size){
            deletefromend() ;
            return ;
        }
        
        

        node<T>* temp = head ;
        /*
         * 1 indexing.
         */
        while(idx--){
            temp = temp->next ;
            if(idx == 1){
                remove(temp) ;
                return ;
            }
        }
    }
    
    /* @ data of any type - which position needs to be deleted
     * if not satisfied on the beginning conditions call the overloaded remove for a node 
     * O(n) complexity
     */
     
    void remove(T data){
        if(head->data == data){
            deletefrombeg() ;
            return ;
        }
        
        node<T>* temp = head ;
        while(temp->data != data){
            temp = temp->next ;
            if(temp == NULL) {
                std::cout << "No such element" <<'\n' ;
                return ;
            }
        }
        
        if(temp->next == NULL){
           deletefromend() ;
           return ;
        }
        
        
        remove(temp) ;
    }
    
    /* @param nod is the current node needs to be deleted.
     * make a temp node pointing to the next linked node of the required node
     * swap the value
     * then link the requied next node to the temp->next
     * delete the temp node
     * O(1) complexity
     */ 

    void remove(node<T>* nod){
        node<T>* temp = nod->next ;
        nod->data = temp->data ;
        nod->next = temp->next ;
        delete temp ;
        size-- ;
    }
    
    bool contains(T data){
        node<T>*temp = head ;
        while(temp){
            if(temp->data == data){
                return true ;
            }
            temp = temp->next ;
        }
        
        return false ;
    }
    
    
    void print(){
        std::cout << "List elements : " ;
        node<T>* temp = head ;
        while(temp != NULL){
            //std::cout << head->data << " " << tail->data <<std::endl ;
            std::cout << temp->data << "->" ;
            temp = temp->next ;
        }
        std::cout << "NULL" ;
        std::cout <<'\n' ;
    }
    
    void printHT(){
        std::cout << "Head and Tail : " ;
        std::cout << head->data << " " << tail->data <<std::endl ;
    }

};

template<class T>
node<T>* merge(node<T>* temp, node<T>* temp2){
    
    node<T>* merged ;

    if(temp == NULL) return temp2 ;
    if(temp2 == NULL) return temp ;

    /*
    *If the first node data is smaller or equal than the 2nd node then 
    *recursively call for the next pointer location for the first one and 2nd one remains unchanged
    *update the new merged node ;
    */
    if(temp->data <= temp2->data){
        merged = temp ;
        merged->next = merge(temp->next,temp2) ;
    }

    /*
    *Vice versa
    */
    else{
        merged = temp2 ;
        merged->next = merge(temp,temp2->next) ;
    }

    return merged ;
}

template<class T>
void middlenode(node<T>* start , node<T>*& head , node<T>*& tail){
    node<T> *mid , *cnt ;
    mid   = start ;
    cnt   = start->next ;
    while(cnt != NULL) {
        cnt = cnt->next ;
        
        if(cnt != NULL){
            mid = mid->next ;
            cnt = cnt->next ;
        }
            
    }
    head = start ;
    tail = mid->next;

    mid->next = NULL ;
}

template<class T>
void mergesort(node<T>*& ilist_node){
    
    node<T>* start = ilist_node ;
    node<T>*head , *tail ;
    if(start == NULL || start->next == NULL){
        //std::cout << "nullptr" << '\n' ;
        return ;
    }

    middlenode(start,head,tail) ;
    mergesort(head) ;
    mergesort(tail) ;
    
    ilist_node =merge(head,tail) ;
}

int main(){
    list<double>ilist;
    ilist.add(1) ;
    ilist.add(22) ;
    ilist.add(14) ;
    ilist.add(8) ;
    ilist.add(67) ;
    ilist.add(32) ;
    ilist.add(6) ;
    ilist.add(5,10) ;
    ilist.print() ;
    ilist.remove(6) ;//idx
    
    mergesort(ilist._getfront()) ;
    ilist.print() ;
    ilist.deletefromend() ;
    ilist.printHT() ;
    //ilist.deletefrombeg() ;
    ilist.print() ;
    ilist.deleteinmiddle() ;
    ilist.print() ;
    ilist.printHT() ;
    
    list<std::string>strlist ;
    strlist.add("Toriqe") ;
    strlist.add("Lamiya") ;
    strlist.add("Tuhin") ;
    strlist.add("Tareq") ;
    strlist.add("Tanvir") ;
    strlist.add("Sallu Vai") ;
    list<std::string>slist = strlist ;
    mergesort(strlist._getfront()) ;
    strlist.remove("Sallu Vai") ;
    strlist.contains("Tuhin") ? std::cout << "true" <<'\n' : std::cout << "false" <<'\n' ; 
    ilist.isempty() ? std::cout << "true" <<'\n' : std::cout << "false" <<'\n' ; 
    //strlist.deletefromend() ;
    //strlist.deleteinmiddle() ;
    strlist.print() ;
    slist.print() ;
}
/*
 * List elements : 1->22->14->8->10->67->32->6->NULL
 * List elements : 1->6->8->10->14->22->32->NULL
 * Deleting from end : 32
 * Head and Tail : 1 22
 * List elements : 1->6->8->10->14->22->NULL
 * Deleting from middle : 10
 * List elements : 1->6->8->14->22->NULL
 * Head and Tail : 1 22
 * true
 * false
 * List elements : Lamiya->Tanvir->Tareq->Toriqe->Tuhin->NULL
 * List elements : Toriqe->Lamiya->Tuhin->Tareq->Tanvir->Sallu Vai->NULL
 */
