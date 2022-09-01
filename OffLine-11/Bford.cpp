#include<iostream>
#include<vector>
#include<queue>
using namespace std ;
typedef long long int ll ;
const ll MAX = 1e17 ;


void printPath(ll last, vector<ll>&parent) {
    if(parent[last]==-1)
    {
        cout<<last ;
        return;
    }
    printPath(parent[last],parent) ;
    cout<<" -> "<< last ;
}

void bFord(ll n, ll m, ll src, ll t, vector<pair<ll,pair<ll,ll>>> &g){
    vector<ll> d(n+5,MAX) , p(n+5,-1) ;
    d[src] = 0 ;
    bool flag , cycle ;
    for(ll i = 0 ; i< n ; i++){
        flag = false , cycle = false ;
        ll prev = d[t] ;
        for(ll j = 0 ; j< m ; j++){
            ll u = g[j].second.first ;
            ll v = g[j].second.second ;
            ll c = g[j].first ;
            if(d[u] != MAX && d[u] + c < d[v]) {
                d[v] = d[u] + c ;
                p[v] = u ;
                flag = true ;
            }
            if(d[t] != prev)    cycle = true ;
        }
    }
    if(flag) {
        cout <<"The graph contains a negative cycle"<<endl;
        return ;
    }
    if(cycle){
        //cout << "Contains a cycle in path from source , No shortest path" ;
        return ;
    }
    cout <<"The graph does not contain a negative cycle " << endl;
    cout <<"Shortest path cost: "<< d[t] << endl;
    printPath(t, p) ;
}

int main(){
    ll n, m , src , t ;
    cin >> n >> m ;
    vector<pair<ll,pair<ll,ll>>> g ;
    for(ll i = 0 ; i < m ; i++){
        ll u, v, c ;
        cin >> u >> v >> c ;
        g.push_back({c,{u,v}}) ;

    }
    cin >> src >> t ;
    bFord(n,m,src,t,g) ;

}