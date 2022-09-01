#include<iostream>
#include<vector>
typedef long long int ll ;
const ll INF = 1e18 ;

using namespace std ;

void print_Matrix(vector<vector<ll> >& d, ll n){
    cout << "Shortest distance matrix" << endl;
    for (ll i = 0; i < n ; i++) {
        for (int j = 0; j < n ; j++) {
            if (d[i][j] == INF)
                cout << "INF"<< " ";
            else
                cout << d[i][j] << " ";
        }
        cout << endl;
    }
}

vector<vector<ll> > Extend_SP(vector<vector<ll> >& a , ll n){
    vector<vector<ll> > c(n+5, vector<ll>(n+5,INF)) ;
    for(ll i = 0 ; i< n ;i++){
        for(ll j = 0 ; j< n ;j++){
            for(ll k = 0 ; k <n ; k++){
                if(a[i][k] == INF || a[k][j] == INF) continue ;
                if(c[i][j] > a[i][k] + a[k][j]){
                    c[i][j] = a[i][k] + a[k][j] ;
                }
            }
        }
    }

    return c ;
}

void Matrix_Mul(const vector<vector<ll> >& w, ll n) {
    ll m = 1 ;
    vector<vector<ll> > c = w ;
    while(m < n){
        c = Extend_SP(c,n) ;
        m = 2*m ;
    }
    print_Matrix(c,n) ;


}


void Floyd_Warshall(vector<vector<ll> >& w , ll n) {
    vector<vector<ll> > d = w ;
    for (ll k = 0; k < n; k++) {
        for (ll i = 0; i < n; ++i) {
            for (ll j = 0; j < n; ++j) {
                if (d[i][k] < INF && d[k][j] < INF)
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
                    //p[i][j] = p[k][j] ;
                    //next[i][j] = next[i][k] ;
            }
        }
    }
    print_Matrix(d,n) ;
}

int main() {
    freopen ("in.txt","r",stdin) ;
    ll n , t ;
    cin >> n >> t ;

    vector<vector<ll> >d(n+5, vector<ll>(n+5,INF)) ;
    for(ll i = 0 ; i < n ;i++){
        d[i][i] = 0 ;
    }
    while(t--){
        ll u, v, c ;
        cin >> u >> v >> c ;
        d[u-1][v-1] = c ;
    }
    Floyd_Warshall(d,n) ;
    Matrix_Mul(d,n) ;

}