#include<iostream>
#include"ArrQueue.h"
#include"LQueue.h"

template <typename T>
void print(Queue<T>& q1){
    ArrQueue<T> q2(q1.length()) ;
    std::cout << "<";
    while(q1.length()){
        std::cout << q1.frontValue() ;
        q2.enqueue(q1.dequeue()) ;
        if(q1.length()) std::cout <<',' ;
    }
    std::cout <<">" ;
    std::cout <<'\n' ;

    while(q2.length()){
        q1.enqueue(q2.dequeue()) ;
    }

}

int main(){
    int ara[100] , n ;
    std::cin >> n;
    ArrQueue<int>intQueue(n) ;
    for(int i = 0 ; i< n; i++)
    {
        std::cin>> ara[i] ;
        intQueue.enqueue(ara[i]) ;
    }
    print(intQueue) ;
    while(true){
        int query , item ;
        std:: cin >> query >> item ;
        if(query == 0) return 0 ;
        switch (query)
        {
        case 1:
            intQueue.clear();
            print(intQueue);
            std::cout << -1 <<'\n' ;
            break;
        case 2:
            intQueue.enqueue(item) ;
            print(intQueue) ;
            std::cout << -1<<'\n' ;
            break ;
        case 3:
            if(!intQueue.length()){
                item = -1 ;
            }
            item = intQueue.dequeue() ;
            print(intQueue) ;
            std::cout << item <<'\n' ;
            break ;
        case 4:
            print(intQueue) ;
            std::cout << intQueue.length() <<'\n' ;
            break ;
        case 5:
            print(intQueue) ;
            std::cout << intQueue.frontValue() <<'\n' ;
            break ;
        case 6:
            print(intQueue) ;
            std::cout << intQueue.rearValue() <<'\n' ;
            break ;
        case 7:
            if(!intQueue.length()){
                item = -1 ;
            }
            else item = intQueue.leaveQueue() ;
            print(intQueue) ;
            std::cout << item <<'\n' ;
            break ;
        default:
            break;
        }
    }

}
