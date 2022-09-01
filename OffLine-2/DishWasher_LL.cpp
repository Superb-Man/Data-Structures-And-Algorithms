#include<iostream>
#include"ArrStack.h"
#include"LLStack.h"

struct Dish{
    int course_duration;
    int cleaning_time ;//ending time for this dish and popping time for the next current dish
    int item ;
    int id ;
};
int main(){
    int n, x , items[100];
    LLStack<Dish> dirtyStack, cleanStack ;
    
    std::cin>> n >> x ; 
    for(int i = 1 ; i<= x ;i++){
        std:: cin >> items[i] ;
    }
    int time = 0, poptime = -1 ;
    int k, t ,s ,i = 0 ,guests[100] ,size = 0;

    while(true){
        std::cin >> k >> t >> s ;

        Dish dirtydish ;
        dirtydish.item = s ;
        dirtydish.id = k ;
        if(s == x) guests[size++] = k ;

        while(dirtyStack.length() && (poptime < t || k==0)){
            Dish dish = dirtyStack.pop() ;
            int item = dish.item ;
            time+= items[item] -1 ;
            dish.cleaning_time = time ;
            cleanStack.push(dish) ;
            poptime = time++ ;
        }
        if(k == 0) break ;
        if(poptime > t || t== 0){
            dirtyStack.push(dirtydish) ;
        }

        else if(poptime >= t && t!=0) {
            dirtyStack.push(dirtydish) ;
        }
        else if(poptime < t){
            dirtyStack.push(dirtydish) ;
            poptime = time = t ;
        }
    }
    time-- ;

    std::cout <<"----------------------------" <<'\n' ;
    
    while(cleanStack.length()){
        Dish dish = cleanStack.pop() ;
        dirtyStack.push(dish) ;
    }

    std::cout << time <<'\n' ;


    while(dirtyStack.length()){
        Dish dish = dirtyStack.pop() ;
        std:: cout << dish.cleaning_time ;
        cleanStack.push(dish) ;
        if(dirtyStack.length() != 0) std::cout <<',' ;
    }
    std::cout <<'\n' ;



    if(size == n) std::cout <<"Y" <<'\n' ;
    else std::cout <<"N" <<'\n' ;

    for(int i = size-1 ; i >= 0 ; i--){
        std::cout << guests[i] ;
        if(i!= 0) std::cout <<',' ;
    }
    std::cout << '\n' ;

    return 0 ;


}