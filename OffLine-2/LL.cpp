#include<iostream>
#include"ArrStack.h"
#include"LLStack.h"

template <typename T>
void print(Stack<T>& st){
    LLStack<T> temp ;
    while(st.length()){
        temp.push(st.pop()) ;
    }
    std::cout << "<";
    while(temp.length()){
        std::cout << temp.topValue() ;
        st.push(temp.pop()) ;
        if(temp.length()) std::cout <<',' ;
    }
    std::cout <<">" ;
    std::cout <<'\n' ;

}

int main(){
    int n, ara[100] ;
    std::cin >> n;
    LLStack<int>intStack ;
    for(int i = 0 ; i< n; i++) 
    {
        std::cin>> ara[i] ;
        intStack.push(ara[i]) ;
    }
    print(intStack) ;
    while(true){
        int query , item ;
        std:: cin >> query >> item ;
        if(query == 0) return 0 ;
        switch (query)
        {
        case 1:
            intStack.clear();
            print(intStack);
            std::cout << -1 <<'\n' ;
            break;
        case 2:
            intStack.push(item) ;
            print(intStack) ;
            std::cout << -1<<'\n' ;
            break ;
        case 3:
            item = intStack.pop() ;
            print(intStack) ;
            std::cout << item <<'\n' ;
            break ;
        case 4:
            print(intStack) ;
            std::cout << intStack.length() <<'\n' ;
            break ;
        case 5:
            print(intStack) ;
            std::cout << intStack.topValue() <<'\n' ;
            break ;
        case 6:
            if(intStack.length() ==0){
                intStack.setDirection(item) ;
            }
            print(intStack) ;
            break; 
        default:
            break;
        }
    }

}