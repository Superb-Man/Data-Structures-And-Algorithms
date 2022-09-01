#include<bits/stdc++.h>
using namespace std ;

typedef long long int ll ;
ll a[200005], b[200005] ;
int main(){
    ll n, m ,k ;
    cin >> n >> m >> k;
	for (ll i = 1; i <= n; i++)
        cin >> a[i];
	for (ll i = 1; i <= m; i++)
        cin >> b[i];
	sort(a+1, a+n+1);
	sort(b+1, b+m+1);

	ll candidate = 1, apartment = 1,ans = 0 ;
	while (candidate <=n && apartment <=m){
		if (abs(a[candidate] - b[apartment]) <= k){
			candidate++ ;
            apartment++ ;
			ans++ ;
		}
		else if(a[candidate] - b[apartment] <= k)
            candidate++ ;
        else
            apartment++ ;
    }

	cout << ans << endl ;
}
