#include<iostream>
#include<stdlib.h>
#include<list>

using namespace std ;

class Comparator {

public:
    template<typename T>
    bool operator() (const T& value1 ,const T& value2)const{
        return value1 < value2 ;
    }

} ;

template <typename E, typename C> // merge-sort Slist
void mergeSort(list<E>& Slist, const C& less) { 
    typedef typename list<E>::iterator Itor; // sequence of elements
    int n = Slist.size();
    if (n <= 1) return; // already sorted
    list<E> S1, S2;
    Itor p = Slist.begin();
    for (int i = 0; i < n/2; i++) S1.push_back(*p++); //first half copying
    for (int i = n/2; i < n; i++) S2.push_back(*p++); //second half copying
    Slist.clear(); //clearing out list contents
    mergeSort(S1, less); 
    mergeSort(S2, less);
    merge(S1, S2, Slist, less); 
}

template <typename E, typename C> 
void merge(list<E>& S1, list<E>& S2, list<E>& Slist, const C& less) { 
    typedef typename list<E>::iterator Itor; 
    Itor p1 = S1.begin();
    Itor p2 = S2.begin();
    while(p1 != S1.end() && p2 != S2.end()) { 
    	if(less(*p1, *p2)) Slist.push_back(*p1++);
    	else Slist.push_back(*p2++);
    }
    
    while(p1 != S1.end()) Slist.push_back(*p1++);
    while(p2 != S2.end()) Slist.push_back(*p2++);
}

int main(){
    list<int>li ;
    li.push_back(76) ;
    li.push_back(746) ;
    li.push_back(71) ;
    li.push_back(66) ;
    li.push_back(6989) ;
    
    Comparator lesser ;
    
    mergeSort(li,lesser) ;
    
    for(list<int>::const_iterator it = li.begin(); it!=li.end() ;it++) {
        
        cout << *it << '\n' ;
    }
}
