#include<bits/stdc++.h>
#include<algorithm>
#include<vector>
using namespace std ;
const float inf = 1e18*(1.0) ;

// Idea taken from Dasgupta's book

class DSU{
    int     n ;
    int*    parent ;

public :

    DSU(int n){
        this->n = n ;
        this->parent = new int[n+5] ;
        init() ;
    }
    void init(){
        for(int i  = 0 ; i <= n ; i++){
            parent[i] = -1 ; // Every vertex is a parent of itself, but using -1
        }
    }
    int find_set(int u){
        if(parent[u] >= 0) return parent[u] = find_set(parent[u]) ;
        return u ;
    }

    bool Union(int u, int v){
        int x = find_set(u) ;
        int y = find_set(v) ;
        if (x != y) {
            if (parent[x] >= parent[y])   std::swap(x, y) ;
            parent[x] = parent[x] + parent[y]; //negatively increasing
            parent[y] = x ;

            return true ;
        }

        return false ;
    }
};
struct edge{
    int     u ;
    int     v ;
    float   cost ;
    edge(int u, int v, float cost){
        this-> u    = u ;
        this-> v    = v ;
        this-> cost = cost ;
    }
    bool operator < (const edge &e) const{
        return e.cost < cost ;
    }
} ;

void Prim(priority_queue<edge>&pq, vector<bool>&vis,vector<pair<int,float>>*adj,vector<edge>&prim){
    float w = 0 ;
    pq.push(edge(0,0,inf)) ;
    while(!pq.empty()){
        edge e = pq.top() ;
        pq.pop() ;
        if(vis[e.v] == false){
            vis[e.v] = true ;
            if(e.u != e.v) {
                prim.push_back(e) ;
                w+=e.cost ;
            }
            for(auto x : adj[e.v]){
                if(vis[x.first] == false) pq.push(edge(e.v,x.first,x.second)) ;
            }
            /*for (int i = 0 ; i< adj[e.v].size() ; i++) {
                if(vis[adj[e.v][i]] == false) pq.push(edge(e.v,adj[e.v][i],adj[e.v][i])) ;
            }*/
        }
    }
    cout << "Cost of the minimum spanning tree : " << w << endl;
    cout <<"List of edges selected by Prim's : {" ;
    for(int i = 0 ; i< prim.size(); i++){
        cout << "(" <<prim[i].u <<","<<prim[i].v << ")" ;
        if(i != prim.size()-1) cout <<"," ;
    }
    cout <<"}"<< endl;
}

void Kruskal(vector<edge>&G,vector<edge>&kruskal, DSU& ds){
    sort(G.begin(), G.end());
    for (int i = G.size() - 1 ; i >= 0 ; i--) {
        int u = G[i].u ;
        int v = G[i].v ;
        if(ds.Union(u,v)) kruskal.push_back(G[i]) ;
    }
    cout <<"List of edges selected by Kruskal's : {" ;
    for(int i = 0 ; i< kruskal.size(); i++){
        cout << "(" <<kruskal[i].u <<","<<kruskal[i].v << ")" ;
        if(i != kruskal.size()-1) cout <<"," ;
    }
    cout <<"}"<< endl;
}

int main(){
    freopen("mst.in","r",stdin) ;
    int n , q ;
    float cost = 0 ;
    cin >> n >> q ;
    DSU ds(n) ;
    vector<edge> G,prim,kruskal ;
    vector<pair<int,float>>adj[n+5] ;
    vector<bool>vis(n+5,false) ;
    priority_queue<edge> pq ;
    while(q--){
        int a, b ;
        double c ;
        std :: cin >> a >> b >> c ;
        G.push_back(edge(a,b,c)) ;
        adj[a].push_back(make_pair(b,c));
        adj[b].push_back(make_pair(a,c));
    }
    Prim(pq,vis,adj,prim) ;
    Kruskal(G,kruskal,ds) ;

    return 0 ;
}
