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


void Dijkstra(ll src, ll t , ll n , vector<pair<ll,ll>> *g){
    ll cost = 0 ;
    vector<ll>p(n+5,-1) ,d(n+1, MAX);
    vector<bool>vis(n+1, false) ;
    priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>> q;
    q.push({0, src}) ;
    d[src] = 0 ;
    while(!q.empty()) {
        auto x = q.top() ;
        q.pop() ;
        ll u = x.second ;
        cost+=x.first ;
        if(t == u) break ;
        if(!vis[u]) {
            vis[u] = true ;
            for(auto v : g[u]) {
                ll y = v.first;
                ll w = v.second;
                if(d[u] + w < d[y]) {
                    d[y] = d[u] + w ;
                    q.push({d[y], y});
                    p[y]  = u ;
                }
            }
        }
    }
    if(p[t] == -1) {
        cout <<"Not Reachable" ;
        return ;
    }
    cout << "Shortest path cost: " << d[t] << endl ;
    printPath(t,p) ;
}

int main(){
    int n, m , src, t ;
    cin >> n >> m ;
    vector<pair<ll,ll>> g[n+2] ;
    for(ll i = 0 ; i < m ; i++){
        ll u,v,c ;
        cin >> u >> v >> c ;
        g[u].push_back(make_pair(v,c)) ;
    }
    cin >> src >> t ;
    Dijkstra(src,t,n,g) ;

}