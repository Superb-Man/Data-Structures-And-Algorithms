#include<iostream>
#include"LQueue.h"
#include"ArrQueue.h"

int main(){
    ArrQueue<int>lq ;
    std::cout <<lq.length() <<'\n' ;
    for(int i = 0 ; i< 10 ;i++){
        lq.enqueue(i*i+1) ;
    }
    std::cout <<lq.length() <<'\n' ;
    while(lq.length() > 7){
        std::cout << lq.leaveQueue() <<" " ;
    }
    std::cout <<lq.length() <<'\n' ;
}