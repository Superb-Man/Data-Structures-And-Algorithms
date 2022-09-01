#include<iostream>
#include"DLL.h"
#include"Arr.h"
//#include"SLL.H"

template<typename T>
void print(List<T> &list){
    int cur = list.currPos() ;
    int size = list.length() ;
    std:: cout <<"<" ;
    if(size != 0){
        list.moveToStart() ;
        int i = 0 ;
        while( i++ < size){
            if(cur == i-1) std::cout <<"| " ;
            std::cout << list.getValue() <<"+" << i-1 <<" " ;
            list.next() ;
        }
        list.moveToPos(cur) ;
    }
    std::cout <<">\n" ;


}


int main(){
    int ara[6] ;
    for(int i = 0 ; i< 6; i++){
        ara[i] = i*i+1 ;
    }
    ArrList<int>lii,li(ara,6,65) ;
    lii.insert(65) ;
    lii.insert(765) ;
    lii.insert(76) ;
    std::cout << lii.getValue() <<"\n";
    print(lii) ;
    li.insert(77) ;
    print(li) ;
    li.moveToEnd() ;
    print(li) ;
    /*while(li.length()){
        std::cout <<li.remove()<<" " ;
    }*/
    li.moveToPos(3) ;

    //li.prev() ;
    //li.print() ;
    print(li) ;
    //std::cout <<li.remove() <<" Removed" <<'\n' ;
    print(li) ;
    //li.next() ;
    std::cout <<li.remove() <<" Removed\n" ;
    print(li) ;
    li.moveToEnd() ;
    print(li) ;
    std::cout <<li.remove() <<" Removed\n" ;
    //li.print() ;
    print(li) ;
    li.insert(9) ;
    std::cout << li.currPos() <<" \n" ;
    //li.print() ;
    //print(li) ;
    std::cout << li.getValue() <<'\n' ;
    //li.moveToStart() ;
    //std::cout << li.remove() <<"\n";
    li.moveToPos(3) ;
    //li.remove() ;
    print(li) ;
    li.prev() ;
    print(li) ;
    //li.print() ;
    li.prev() ;
    print(li) ;
    //li.print() ;
    int siz = 0;
    int cur = li.currPos() ;
    li.moveToStart() ;
    while(siz++ < li.length()){
        if(siz-1 == cur) std::cout <<"| " ;
        std:: cout <<li.getValue() <<"+"<<li.currPos() <<" " ;
        li.next() ;//li.next() ;
    }
    std::cout << std::endl ;
    li.moveToPos(cur) ;
    //li.print() ;
    print(li) ;
    //std:: cout << li.remove() <<" Removed\n" ;
    print(li) ;
    //li.print() ;
    std::cout << li.Search(288) <<'\n' ;
    //li.moveToPos(0) ;
    print(li) ;
    //li.print() ;
    li.next() ;
    li.prev() ;
    //print(li) ;
    std:: cout << li.remove() <<" Removed\n" ;
    print(li) ;
    li.moveToStart() ;
    std::cout << li.remove() <<" Removed\n" ;
    //li.print() ;
    li.clear() ;
    li.clear() ;
    //li.print() ;
    print(li) ;
    li.append(765) ;
    //print(li) ;
    //print(lii) ;
    //li.print() ;
    //lii.print() ;
}
/*
76
<| 76+0 765+1 65+2 >
<| 77+0 1+1 2+2 5+3 10+4 17+5 26+6 >
<| 77+0 1+1 2+2 5+3 10+4 17+5 26+6 >
<77+0 1+1 2+2 | 5+3 10+4 17+5 26+6 >
<77+0 1+1 2+2 | 5+3 10+4 17+5 26+6 >
5 Removed
<77+0 1+1 2+2 | 10+3 17+4 26+5 >    
10 Removed
<77+0 1+1 2+2 | 17+3 26+4 >
3 
9
<77+0 1+1 2+2 | 9+3 17+4 26+5 >     
<77+0 1+1 | 2+2 9+3 17+4 26+5 >
<77+0 | 1+1 2+2 9+3 17+4 26+5 >
77+0 | 1+1 2+2 9+3 17+4 26+5   
<77+0 | 1+1 2+2 9+3 17+4 26+5 >
<77+0 | 1+1 2+2 9+3 17+4 26+5 >
-1
<77+0 | 1+1 2+2 9+3 17+4 26+5 >
1 Removed
<77+0 | 2+1 9+2 17+3 26+4 >
77 Removed
<>
*/