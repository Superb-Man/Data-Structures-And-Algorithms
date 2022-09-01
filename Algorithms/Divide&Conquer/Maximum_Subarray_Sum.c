#include<iostream>
using namespace std ;

typedef long long int ll
ll maxcross(ll *p,ll l,ll m,ll h)
{
    ll lsum=0,rsum=0,rmx=-1e9+7,lmx=-1e9+7;
    for(ll i=m;i>=l;i--)
    {
        lsum+=p[i];
        lmx=max(lsum,lmx);
    }
    for(ll i=m+1;i<=h;i++)
    {
        rsum+=p[i];
        rmx=max(rmx,rsum);
    }
    return max(max(rmx,lmx),lmx+rmx);
}
ll maxsum(ll *p,ll l,ll h)
{
    if(l==h)
    {
        return p[l];
    }
    ll m=(l+h)/2;
    return max(max(maxsum(p,l,m),maxsum(p,m+1,h)),maxcross(p,l,m,h));
}
int main()
{
    ll n ;
    cin >> n ;
    ll* p = new ll[n+5] ;
    for(int i=0;i<n;i++) {
        cin >> p[i] ;
    }
    ll sum;
    sum=maxsum(p,0,n-1);
    cout << sum << endl;
    delete [] p ;
}
