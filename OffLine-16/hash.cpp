#include<iostream>
#include<math.h>
typedef long long int ll ;
const ll MIN = -1e18 ;

ll hashValue(std:: string s) {
    const ll p = 31;
    const ll m = 1e9 + 9;
    ll hash_value = 0;
    ll p_pow = 1;
    for (char c : s) {
        hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    /*ll hash_value = 0 ;
    for(char c: s) {
        hash_value  = hash_value + (c - 'a' + 1) ;
    }*/

    return hash_value;
}

ll hashValue2(std :: string s){
    ll hash=5381 ;
    for( ll i = 0; i < s.size() ; i++){
        hash = ((hash<<5)+hash) + s[i] ;
    }
    return hash ;
}


struct node {
    std :: string key ;
    ll           value ;
    node* next ;

    node(std::string key , ll value) {
        this->key = key ;
        this->value = value ;
        this->next = nullptr ;
    }

    node(){
        this->value = MIN ;
        next = nullptr ;
    }

} ;

struct tNode{
    std::string key ;
    ll value ;
    bool isEmpty ;
    bool isDeleted ;
    tNode(){
        key = "" ;
        isEmpty = true ;
        isDeleted = false ;
    }

    void set(std::string s , ll val , bool x , bool y) {
        key = s ; value  = val ;
        isEmpty = x ; isDeleted = y ;
    }
};


class HashMap{
    node** __hashTable ;
    ll n ;
    node* searchNode(std:: string s) {
        ll hash = hashValue(s) % n ;
        node* ptr = __hashTable[hash];
        ptr = ptr->next ;
        while (ptr != nullptr) {
            if (ptr->key.compare(s) == 0)  {
                return ptr ;
            }
            ptr = ptr->next;
        }
        //std :: cout <<"nullptr returning" <<'\n' ;
        return nullptr ;
    }

public:
    HashMap(ll n) {
        this->n  = n ;
        __hashTable = new node*[n] ;
        for(ll i = 0 ; i< n ; i++) __hashTable[i] = new node ;
    }
    void insert(std::string key,ll value){
        ll hash = hashValue(key) % n ;
        node* temp = new node(key,value) ;
        node* ptr = __hashTable[hash] ;
        //std :: cout <<hash << '\n' ;

        node* found = searchNode(key) ;


        while(ptr->next != nullptr) {
            if(ptr->next == found) {
                ptr->value = value ;
                //std::cout <<"repeated"<< '\n' ;
                return ;
            }
            if(value >= ptr->value && value <= ptr->next->value){
                temp->next = ptr->next ;
                ptr->next = temp;
                break;
            }
            ptr=ptr->next;
        }
        if(ptr->next == nullptr) ptr->next = temp ;

    }

    void remove(std :: string s) {
        ll hash = hashValue(s) % n ;
        node* ptr = __hashTable[hash];
        node* temp = ptr ;

        //finding the required node
        while (ptr->next != nullptr) {
            ptr = ptr->next ;
            if(ptr->key.compare(s) == 0)   break;
            temp = ptr ;
        }
        //link between temp and ptr->next
        if (temp != ptr) {
            temp->next = ptr->next ;
            delete ptr ;
        }
    }

    bool search(std:: string s) {
        return ((searchNode(s) != nullptr) ? true : false) ;
    }

    void clear(){
        node* temp , *ptr;
        for(ll i = 0 ;i < n ; i++){
            temp = __hashTable[i] ;
            while(temp != nullptr){
                ptr=temp;
                temp = temp->next;
                delete ptr;
            }
        }
    }
    void print() {
        for(ll i = 0 ; i < n ; i++) {
            std :: cout << __hashTable[i]->key << '\n' ;
        }
    }

    ~HashMap() {
        clear() ;

        delete [] __hashTable ;
    }

};

class LinearHashMap {
    tNode* __hashTable ;
    ll n ;

public:
    LinearHashMap(ll n) {
        this->n  = n ;
        __hashTable = new tNode[n] ;
    }
    std::pair<ll,ll> insert(std::string key, ll value) {

        ll hash = hashValue(key) % n ;
        ll x ;
        ll probe = 0 ;
        for(ll i = 0 ; i< n ;i++) {
            probe++ ;
            x = (i+hash) %n ;
            if((__hashTable + (x))->isEmpty == true){
                //std :: cout <<"repeated"<<'\n' ;
                (__hashTable + (x))->key = key ;
                (__hashTable + (x))->value = value ;
                (__hashTable+(x))->isDeleted = false ;
                (__hashTable+(x))->isEmpty = false ;
                return std::make_pair(true , probe) ;
            }
        }
        return std::make_pair(false , probe) ;
    }
    std::pair<bool,ll> remove(std :: string key) {
        ll hash = hashValue(key) % n ;
        ll x ;
        ll probe  = 0 ;

        for(ll i = 0 ; i< n ;i++) {
            probe++ ;
            x = (i+hash) %n ;
            if((__hashTable+(x))->isEmpty == false && (__hashTable + (x))->key == key){
                //std::cout <<"remove done"<<std::endl;
                (__hashTable+(x))->key = "" ;
                (__hashTable+(x))->isEmpty = true ;
                (__hashTable+(x))->isDeleted = true ;
                return std::make_pair(true , probe) ;
            }
        }
        return std::make_pair(false , probe) ;
    }

    std::pair<bool,ll> search(std::string key) {
        ll hash = hashValue(key) % n ;
        ll x ;
        ll probe  = 0 ;
        for(ll i = 0 ; i< n; i++) {
            probe++ ;
            x = (i+hash) %n ;
            if((__hashTable+(x))->isEmpty == true && (__hashTable+(x))->isDeleted == false) {

                return std::make_pair(false , probe) ;
            }
            else if((__hashTable + (x))->key == key) {
                return std::make_pair(true , probe) ;
            }
        }
        return std::make_pair(false , probe) ;
    }

    void clear() {
        delete []__hashTable ;
    }

    ~LinearHashMap(){
        clear() ;
    }
} ;

class QuadHashMap {
    tNode* __hashTable ;
    ll n ;


public:
    QuadHashMap(ll n) {
        this->n  = n ;
        __hashTable = new tNode[n] ;
    }
    std::pair<bool,ll> insert(std::string key, ll value) {

        ll hash = hashValue(key) % n ;
        ll x ;
        ll probe  = 0 ;
        for(ll i = 0 ; i< n ;i++) {
            probe++ ;
            x = (hash+29*i + 37*i*i) %n ;
            if((__hashTable + (x))->isEmpty == true){
                //std :: cout <<"repeated"<<'\n' ;
                (__hashTable + (x))->key = key ;
                (__hashTable + (x))->value = value ;
                (__hashTable+(x))->isDeleted = false ;
                (__hashTable+(x))->isEmpty = false ;
                return std::make_pair(true , probe) ;
            }
        }
        return std::make_pair(false  , probe) ;
    }
    std::pair<bool,ll> remove(std :: string key) {
        ll hash = hashValue(key) %n ;
        ll x ;
        ll probe  = 0 ;
        for(ll i = 0 ; i< n ;i++) {
            probe++ ;
            x = (hash + 29*i + 37*i*i) %n ;
            if((__hashTable+(x))->isEmpty == false && (__hashTable + (x))->key == key){
                (__hashTable+(x))->key = "" ;
                (__hashTable+(x))->isEmpty = true ;
                (__hashTable+(x))->isDeleted = true ;
                return std::make_pair(true , probe) ;
            }
        }
        return std::make_pair(false , probe) ;
    }

    std::pair<bool, ll> search(std::string key) {
        ll hash = hashValue(key) % n ;
        ll x  ;
        ll probe  = 0;

        for(ll i = 0 ; i< n ;i++) {
            probe++ ;
            x = (hash+29*i + 37*i*i) %n ;
            if((__hashTable+(x))->isEmpty == true && (__hashTable+(x))->isDeleted == false) {
                return std::make_pair(false , probe) ;
            }
            else if((__hashTable + (x))->key == key) {
                return std::make_pair(true , probe) ;
            }
        }
        return std::make_pair(false , probe) ;
    }

    void clear() {
        delete []__hashTable ;
    }

    ~QuadHashMap(){
        clear() ;
    }
} ;

class DHashMap {
    tNode* __hashTable ;
    ll n ;
public:
    DHashMap(ll n) {
        this->n  = n ;
        __hashTable = new tNode[n] ;
    }
    std::pair<bool,ll> insert(std::string key, ll value) {
        ll hash1 = hashValue(key) %n ;
        ll hash2 = (hashValue2(key) %(n-1) ) +1 ;
        ll x ;
        ll probe =  0;
        for(ll i = 0 ; i < n ; i++) {
            probe++ ;
            x = (hash1 + i*hash2)%n ;
            if((__hashTable + (x))->isEmpty == true){
                //std :: cout <<"repeated"<<'\n' ;
                (__hashTable + (x))->key = key ;
                (__hashTable + (x))->value = value ;
                (__hashTable+(x))->isDeleted = false ;
                (__hashTable+(x))->isEmpty = false ;

                //(__hashTable + (x))->set(key , value , false , false) ;
                return std::make_pair(true , probe) ;
            }
        }
        return std::make_pair(false , probe) ;
    }
    std::pair<bool,ll> remove(std :: string key) {
        ll hash1 = hashValue(key) %n ;
        ll hash2 = (hashValue2(key) %(n-1) ) +1 ;
        ll x ;
        ll probe  = 0 ;
        for(ll i = 0 ; i < n ; i++) {
            probe++ ;
            x = (hash1 + i*hash2)%n ;
            if((__hashTable+(x))->isEmpty == false && (__hashTable + (x))->key == key){
                (__hashTable+(x))->key = "" ;
                (__hashTable+(x))->isEmpty = true ;
                (__hashTable+(x))->isDeleted = true ;
                return std::make_pair(true , probe) ;
            }
        }
        return std::make_pair(false , probe) ;
    }

    std::pair<bool,ll> search(std::string key) {
        ll hash1 = hashValue(key) %n ;
        ll hash2 = (hashValue2(key) %(n-1) ) +1 ;
        ll x ;
        ll probe = 0 ;
        for(ll i = 0 ; i < n ; i++) {
            probe++ ;
            x = (hash1 + i*hash2)%n ;
            if((__hashTable+(x))->isEmpty == true && (__hashTable+(x))->isDeleted == false) {
                return std::make_pair(false , probe) ;
            }
            else if((__hashTable + (x))->key == key) {
                return std::make_pair(true , probe) ;
            }
        }
        return std::make_pair(false , probe) ;
    }

    void clear() {
        delete []__hashTable ;
    }


    ~DHashMap(){
        clear() ;
    }
} ;

