#include<iostream>
#include"LLStack.h"
#include"ArrStack.h"

int main(){
    int *ar = new int[18] ;
    ArrStack<int>mystack(ar,18,-1) ;
    //mystack.setDirection() ;
    for(int i = 0 ; i< 6 ;i++){
        mystack.push(i*i+1);
    }
    std::cout << mystack.length() <<'\n' ;
    while(mystack.length()){
        std::cout << mystack.pop() <<" " ;
    }
    mystack.clear() ;

}
