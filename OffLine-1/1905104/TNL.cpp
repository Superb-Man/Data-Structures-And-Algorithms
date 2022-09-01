#include<iostream>
#include"LL.h"
#include"Arr.h"

template <typename T>
void printTerminals(List<T>& list , int k){
    for(int i = 0 ; i < k ;i++){
        if(list.Search(i) >= 0) std::cout << i ;
            if(i != k-1) std::cout <<"," ; 
    }
    std::cout <<'\n' ;
}

int main(){
    int k, L;
    std::cin >> k ;

    LList<int>listRS, listBS, listTS ;
    for(int i = 0 ; i< k ;i++){
        listRS.append(i) ;
    }

    std::cin >> L ;
    for(int i = 0 ; i< L ;i++){
        int st ;
        std::cin >> st ;
        listBS.append(st) ;
    }

    std::cin >> L ;
    for(int i = 0 ; i< L ;i++){
        int st ;
        std::cin >> st ;
        listTS.append(st) ;
    }
    int T ;
    std::cin >> T ;

    switch (T)
    {
    case 1:
        printTerminals(listRS, k) ;
        printTerminals(listBS, k) ;
        printTerminals(listTS, k) ;
        break;
    
    default:
        break;
    }

    return 0 ;

}