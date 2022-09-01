#include<iostream>
#include<queue>
#include<cstdio>
#include<stdlib.h>

using namespace std;


int dis[10005],parent[10005] ;


void initialize(int siz){
    for(int i = 0 ; i <=siz; i++){
        parent[i] = -1 ;
        dis[i] = -1 ; //Not visited for each test case
    }
}

int minMove(int *board, int die_face, int cell){
    //breadth first search
    initialize(cell) ;

    std::queue<int>queries ;
    int src = 1 ;
    dis[src] = dis[src]+1 ;
    queries.push(src) ;

    while(!queries.empty()){
        int vertex = queries.front() ;
        int distance = dis[vertex]+1 ;


        queries.pop() ;

        for(int i = vertex+1 ; i <=vertex+die_face ; i++){
            if(i > cell) break ;
            int prnt = vertex ,pos = i ;

            //if there are continuous/Consecutive ladders or snakes
            //Just go to the last end point
            while(board[pos] != pos){

                if(dis[pos] ==-1){
                    parent[pos] = prnt ;
                    dis[pos] = distance ;
                }
                else
                    break ;
                prnt = pos ;
                pos = board[pos] ;
            }

            if(dis[pos] == -1){
                parent[pos] = prnt ;
                dis[pos] = distance ;
                queries.push(pos) ;
            }

        }
    }

    return dis[cell] ;

}

void reachable(int cell){
    int cnt = 0;
    for(int i = 1 ;i <=cell ; i++){
        if(dis[i] == -1) {
            cnt++ ;
            std::cout <<i <<" " ;
        }
    }
    if(cnt) std::cout <<'\n' ;
    if(!cnt) std::cout <<"All reachable\n" ;
}

void printPath(int cell){
    if(parent[cell]==-1)
    {
        std::cout<<cell;
        return;
    }
    printPath(parent[cell]);
    std::cout<<" -> "<<cell;
}


int main(){
    freopen ("input.txt","r",stdin);
    freopen ("output.txt","w",stdout);
    int t ;
    std::cin >> t ;
    while(t--){
        int n,X,l,s ;
        std::cin >> n >> X ;

        int *board = new int[X+1] ;
        for(int i = 0 ; i<=X ;i++) board[i] = i ;

        std::cin >> l ;
        while(l--){
            int start,en ;
            std::cin >> start >> en ;
            board[start] = en ;
        }
        std::cin >> s ;
        while(s--){
            int start,en ;
            std::cin >> start >> en ;
            board[start] = en ;
        }
        std::cout << minMove(board,n,X) <<'\n' ;
        if(dis[X] != -1) {
            printPath(X) ;
            std::cout <<'\n';
        }
        else std::cout <<"No solution\n" ;

        reachable(X) ;

        delete [] board ;


    }

    fclose(stdout);

    return 0 ;
}
