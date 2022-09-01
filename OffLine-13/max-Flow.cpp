#include<bits/stdc++.h>
using namespace std ;
typedef long long int ll ;

const ll INF = 1e18 ;
vector<bool>vis(10500, false) ;
map<ll,string> mp ;

ll bfs(ll s, ll d , vector<ll>&p, vector<vector<ll> >&c , vector<ll>* e){
    ll u , flow , new_flow ;
    fill(p.begin(),p.end(),-1);


    queue<pair<ll,ll> >q;
    q.push({s,INF});
    p[s] = -2;

    while(!q.empty()){
        u = q.front().first ;
        flow = q.front().second ;
        q.pop();
        for(auto v : e[u]){
            if(p[v] == -1 && c[u][v] != 0){
                p[v] = u ;
                new_flow = min(flow ,c[u][v]);
                if(v == d){
                    return new_flow;
                }
                q.push({v,new_flow});
            }
        }
    }

    return 0;
}

ll edmond_karp(ll s ,ll d ,vector<ll>&p, vector<vector<ll> >&c , vector<ll>* e){
    ll flow = 0, new_flow , cur , prev;

    while(true) {
        new_flow = bfs(s, d, p , c , e) ;
        if(!new_flow) break ;
        flow = flow + new_flow;
        cur = d ;
        while(cur != s){
            prev = p[cur] ;
            c[prev][cur]-=new_flow ;
            c[cur][prev]+=new_flow ;
            cur = prev ;
        }
    }
    return flow ;
}

void makeGraph(vector<ll>* e , ll u , ll v) {
    e[u].push_back(v) ;
    e[v].push_back(u) ;
}

void dfs(ll u ,const vector<vector<ll> >&c , vector<ll>* e){
    vis[u] = true;
    for(auto v : e[u]){
        if(vis[v] == false && c[u][v] > 0) {
            dfs(v, c, e);
        }
    }
}

void print(vector<ll>& ans , vector<ll>& w, vector<ll>& left , vector<vector<ll> >& g , ll t){
    double avg = 0 , tot = 0 , rem = 0 ;
    for(ll i = 0 ; i < ans.size() ; i++) {
        tot+=w[ans[i]] ;
        for(ll j = i+1; j < ans.size() ; j++){
            rem+=g[ans[i]][ans[j]];
        }
    }
    cout << mp[t]<<" is eliminated." <<endl;
    cout << "They can win at most "
         << w[t] << "+" <<left[t] << "=" << w[t] + left[t] << " games." <<endl;

    for(ll i = 0; i < ans.size() ; i++){
        cout << mp[ans[i]];
        if(i != ans.size()-1)
            cout << " and ";
    }
    avg = ((tot+rem)*1.0)/ans.size() ;
    cout << " have won a total of " << tot << " games." << endl
         << "They play each other " << rem << " times." << endl
         << "So on average, each of the teams in this group wins "
         << tot + rem<<"/"<<ans.size() << "=" << avg <<" games." << endl
         << endl;
    ans.clear();
}

void clear(ll s, ll d , vector<ll>* e, vector<vector<ll> >& c) {
    for(ll i = s ; i <= d ; i++){
        e[i].clear();
        vis[i] = false;
        for(ll j = s ; j <= d ; j++){
            c[i][j] = 0;
        }
    }
}

int main() {
    freopen("input.txt","r",stdin);
    //freopen("out","w",stdout);

    string st;
    vector<vector<ll> > g(105 , vector<ll>(105,0)) , c(5010 , vector<ll>(5010, 0)) ;
    vector<ll>w(105,0) , l(105,0) , left(105,0) ;
    vector<ll>p(10200,0) , e[10200] ;
    ll n ;
    cin >> n ;
    ll s = 0;
    // nc2 + n + 1 , for simplicity ......
    ll d = n*n + n ;
    for(ll i = 1;i <= n;i++){
        cin >> st >> w[i] >> l[i] >> left[i];
        mp[i] = st ;

        for(ll j = 1; j <= n ;j++) {
            ll x ;
            cin >> x ;
            g[i][j] = x ;
        }
    }

    for(ll t = 1 ; t <=n ; t++) {
        ll flow = 0;
        vector<ll> ans ;

        for(ll i = 1 ; i <= n ; i++){
            if(i != t)  makeGraph(e, i , d) ;

            for(ll j=i+1 ; j <= n ; j++){
                if(i != t && j != t) {
                    makeGraph(e, s, i * n + j) ; //making connections with src to match
                    makeGraph(e, i * n + j , i) ; //making connection with match to club
                    makeGraph(e, i * n + j , j) ; // a match can contain maximum two teams

                    c[s][i * n + j] = g[i][j];
                    c[i * n + j][i] = INF ; //initially Infinite
                    c[i * n + j][j] = INF ; //initially infinite

                    flow+=g[i][j];
                }
            }

        }

        for(ll i = 1 ; i <= n ; i++){
            if(i != t ){
                c[i][d] = w[t] + left[t] - w[i] ; // assuming t will win all the reamining matches
                if(c[i][d] < 0){
                    ans.push_back(i);
                    break;
                }
            }
        }

        if(ans.size() != 0) { // that means we have found a loser team :')
            print(ans , w ,left , g , t);
            clear(s , d , e , c);
        }
        else {

            ll max_flow = edmond_karp(s, d , p , c , e) ;
            //cout << max_flow << endl ;

            if(max_flow != flow){
                dfs(s , c, e) ;
                for(ll i = 1 ; i <= n; i++){
                    if(vis[i] == true )  ans.push_back(i) ;
                }
                print(ans , w, left, g , t);
            }
            clear(s ,d , e, c);
        }
    }

}
