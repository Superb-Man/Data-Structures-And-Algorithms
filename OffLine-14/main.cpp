#include<bits/stdc++.h>
#include<ctime>
#include"BinHeap.h"
#include"FibHeap.h"
using namespace std ;
const ll MAX = 1e18 ;
ll cost = 0 ;
float tim ;
ll length ;


struct myPair{
    ll first  ;
    ll second ;
    myPair() {

    }
    myPair(ll f, ll s) {
        first = f ; second = s ;
    }

    /*int operator-(int y){
        return second - y ;
    }*/
    bool operator> (const myPair& mp){
        return second >= mp.second ;
    }
    bool operator< (const myPair& mp) {
        return second <= mp.second ;
    }

    bool operator==(const myPair& mp) {
        return second == mp.second ;
    }

};
void Dijkstra(ll src , ll t , ll n , vector<myPair>*g) {
    //int cost = 0 ;
    clock_t time = clock();
    length = 0 ;
    vector<ll>d(n+2 ,MAX) ;
    vector<ll>p(n+5,-1) ;
    vector<bool>vis(n+2 , false) ;
    BinNode<myPair>** nodes = new BinNode<myPair>*[n+5] ;
    //nodes.push_back(NULL) ;
    Heap<myPair>heap(n) ;
    //nodes[0] = NULL ;
    for(ll i = 1 ; i<= n ; i++) {
        myPair mp ;
        mp.first = i ;
        mp.second = MAX ;
        if(i == src) mp.second = 0 ;
        //cout << "getting error" << endl ;
        nodes[i] = heap.insert(mp) ;
    }
    //cout << heap.getMin()->key.second << endl;
    for(ll i = 1 ; i <= n ;i++) {
        myPair a = heap.extractMin() ;
        ll u = a.first ;
        ll dis = a.second ;
        d[u] = dis ;
        //cout << u << " "<<d[u] <<endl;
        vis[u] = true ;
        for(auto v : g[u]) {
            if(vis[v.first] == false) {
                //cout << v.first << endl;
                BinNode<myPair>* ptr = nodes[v.first] ;
                //cout << ptr <<" "<< nodes[v.first] << endl;
                if(v.second + dis < ptr->key.second) {
                    v.second = v.second + dis ;
                    p[v.first] = u ;
                    //cout << v.second << endl;
                    //cout <<"lolilol"<< endl;
                    heap.decreaseKey(ptr , v) ;
                    //cout <<"lol"<<endl;
                }
            }
        }
        /*for(int j = 0 ; j < n ;j++) {
            cout <<nodes[j]->key.first << " " << nodes[j]->key.second << endl;
        }*/
    }

    /*for(ll i = 1 ; i <=  n; i++){
        cout << d[i] <<" " ;
    }*/
    cout <<d[t] << " ";
    delete []nodes ;
    tim = float(clock() - time) / CLOCKS_PER_SEC;
    //cout << tim << " " << endl;


}

void DijkstraFib(ll src , ll t , ll n , vector<myPair>*g) {
    clock_t time = clock();
    //cost = 0 ;
    //length = 0 ;
    vector<ll>p(n+1 , -1) ;
    vector<ll>d(n+1 ,MAX) ;
    vector<bool>vis(n+1 , false) ;
    FibHnode<myPair>** nodes = new FibHnode<myPair>*[n+1] ;
    FibHeap<myPair>heap ;

    for(ll i = 0 ; i< n ; i++) {
        myPair mp ;
        mp.first = i ;
        mp.second = MAX ;
        if(i == src) mp.second = 0 ;
        //cout << "getting error" << endl ;
        nodes[i] = heap.insert(mp) ;
        //cout << nodes[i]->key.second << endl;
    }
    for(ll i = 0 ; i < n ;i++) {
        ll u = heap.getMin().first ;
        ll dis=heap.extractMin().second ;
        //cout << dis << endl;
        d[u] = dis ;
        //cout << u << " "<<d[u] <<endl;
        //cost+=d[u] ;
        vis[u] = true ;
        for(myPair v : g[u+1]) {
            //myPair v = g[u+1][j] ;
            if(vis[v.first-1] == false) {
                //cout << v.first << endl;
                FibHnode<myPair>* ptr = nodes[v.first-1] ;
                if(v.second + dis < ptr->key.second) {
                    v.second = v.second + dis ;
                    p[v.first-1] = u ;
                    v.first = v.first - 1 ;
                    //cout << v.second << endl;
                    heap.decreaseKey(nodes[v.first] ,v) ;
                }
            }
        }
        /*for(int j = 0 ; j < n ;j++) {
            cout <<nodes[j]->key.first << " " << nodes[j]->key.second << endl;
        }*/
    }
    length = 0;
    for(ll i = t ; p[i] != -1 ; i = p[i]){
        length++ ;
    }
    cost = d[t] ;
    tim = float(clock() - time) / CLOCKS_PER_SEC ;
    //cout << tim << " " ;
    cout << cost << " " << endl ;
    delete []nodes ;


}

int main() {
    freopen("heap1.txt","r",stdin) ;
    ll n, m , src, t ;
    cin >> n >> m ;
    vector<myPair>gg[n+2] ;
    for(int i = 0 ; i < m ; i++){
        ll u,v,c ;
        cin >> u >> v >> c ;
        u++ ; v++ ;
        //g[u].push_back(myPair(v,c)) ;
        gg[u].push_back(myPair(v,c)) ;
    }
    /*for(auto v : g[0]) {
        cout <<v.first <<" " ;
    }*/
    cout << endl;

    //cin >> src >> t ;
    freopen("heap2.txt","r",stdin) ;
    freopen("outputtt.txt","w", stdout) ;
    ll cas = 1 ;
    src = 1 ; t = n ;
    cin >> cas ;
    while(cas--) {
        cin >> src >> t ;
        Dijkstra(src,t,n,gg) ;
        float bin_time = tim ;
        DijkstraFib(src-1,t-1,n,gg) ;
        float fib_time = tim ;
        cout << length <<" "<<cost <<" "<< bin_time <<" "<<fib_time << endl;
    }
}
