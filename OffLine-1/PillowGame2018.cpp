#include<iostream>
#include<string>
#include"Arr.h"
#include"DLL.h"

class Player{

private:

    int reflex_time ;
    std::string name ;

public:
    Player(){

    }

    Player(int reflex_time , std::string &name){
        this->reflex_time = reflex_time ;
        this->name = name ;
    }
    Player(const Player& p){
        this->reflex_time = p.reflex_time ;
        this->name = p.name ;
    }

    ~Player(){

    }

    int get_reflexTime(){
        return reflex_time ;
    }

    std::string get_name(){
        return name ;
    }

    int operator==(const Player& p){
        return p.name == name ;
    }

};
void update(char dir, List<Player>& playerList){
    if(dir == 'F') {
        if(playerList.currPos() != playerList.length()-1)
            playerList.next() ;
        else
            playerList.moveToStart() ;
    }
    else if(dir == 'B') {
        if(playerList.currPos() != 0)
            playerList.prev() ;
        else
            playerList.moveToEnd() ;
    }
}

int playtime(int runtime ,int t, char dir ,List<Player>&playerList){
    while(runtime < t){
        runtime+=playerList.getValue().get_reflexTime() ;
        if(runtime >= t) {
            runtime-=playerList.getValue().get_reflexTime() ;
            return runtime ;
        }
        update(dir,playerList) ;
    }

    return runtime ;
}

void print(char dir , List<Player>& playerList){
    int size = playerList.length() ;
    while(size--){
        std::cout << playerList.getValue().get_name() ; 
        if(size !=0) std::cout << "," ;
        update(dir,playerList) ;
    }
    std::cout <<'\n' ;
}

int main(){
    int n ;
    std::cin >> n ;
    LList<Player>playerList ;
    for(int i = 1 ;i <=n  ;i++){
        int x ;
        std::string name ="Player " ;
        std::cin >> x ;
        name+=std::to_string(i) ;
        playerList.append(Player(x, name)) ;
    }

    char dir ='F' ;
    int runtime = 0 ;
    while(true){
        int t , x;
        char q ;
        std::cin >> t >> q ;
        std::string name ;


        switch (q)
        {
        case 'M':
            if(playerList.length() == 1) continue ;
            runtime = playtime(runtime, t, dir, playerList) ;
            runtime = t ;
            //std::cout <<runtime <<" Removed\n" ;
            //std::cout <<playerList.getValue().get_reflexTime() << '\n' ;
            if(dir == 'F'){
                if(playerList.currPos() != playerList.length()-1){
                    std::cout << playerList.remove().get_name() <<" hasbeen eliminated at time t = " <<t <<'\n' ;
                }
                else {
                    std::cout << playerList.remove().get_name() <<" hasbeen eliminated at time t = " <<t <<'\n' ;
                    playerList.moveToStart() ;
                }
            }
            if(dir == 'B'){
                if(playerList.currPos() != 0){
                    std::cout << playerList.remove().get_name() <<" hasbeen eliminated at time t = " <<t <<'\n' ;
                    playerList.prev() ;
                }
                else {
                    std::cout << playerList.remove().get_name() <<" hasbeen eliminated at time t = " <<t <<'\n' ;
                    playerList.moveToEnd() ;
                }
            }

            break ;

        case 'R':
            if(playerList.length() == 1) continue ;
            runtime = playtime(runtime, t, dir, playerList) ;
            //std::cout <<playerList.getValue().get_name() <<"JHFGVBHSDBC\n" ;
            //runtime = t ;
            if(dir == 'F') dir ='B' ;
            else dir ='F' ;


            break ;

        case 'I' :
            std::cin >> x ;
            if(playerList.length() == 1) continue ;
            n++ ;
            name = "Player "+std::to_string(n) ;
            runtime = playtime(runtime, t, dir, playerList) ;
            if(dir == 'F'){
                playerList.insert(Player(x, name)) ;
                playerList.next() ;

            }
            else{
                playerList.next() ;
                playerList.insert(Player(x, name)) ;
                playerList.prev() ;
            }

            break ;

        case 'P':
            if(playerList.length() ==1 ) continue ;
            runtime = playtime(runtime, t, dir, playerList) ;
            std::cout << playerList.getValue().get_name() <<" is holding the pillow at t = " <<t <<'\n' ;
            if(runtime+playerList.getValue().get_reflexTime() == t) {
                runtime = t ;
                update(dir, playerList) ;
            }
            break ;

        case 'F':
            if(playerList.length() > 1) runtime = playtime(runtime, t, dir, playerList) ;
            std::cout <<"Game Over : " ;
            if(playerList.length() == 1) {
                std::cout <<playerList.getValue().get_name() <<" wins "<<'\n' ;
            }
            else{
                std::cout << playerList.getValue().get_name() <<" is holding the pillow at t = " <<t <<'\n' ;
                std::cout << "Pillow Passing Sequence : " ;
                print(dir,playerList) ;

                return 0 ;
            }
            break;

        default:
            break;
        }

    }
}
