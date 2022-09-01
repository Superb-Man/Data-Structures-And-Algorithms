#include<iostream>
#include<algorithm>

int a[101] ;
typedef long long int ll ;

ll findCost(int *arr, ll n,ll k) {
    ll cnt = 0 , j =0 , cost = 0 ;
    for(ll i = n-1 ; i >= 0 ; i--){
        cnt  = (j == 0) ? cnt+1 : cnt ;
        j = (j+1)% k ;
        cost+= a[i]*cnt ;
    }

    return cost ;

}

int main(){
    ll n,k;
    
    std::cin >> n>> k ;
    for(ll i =0 ; i < n ;i++)
        std::cin >> a[i] ;

    std::sort(a,a+n) ;

    std::cout << findCost(a,n,k) << '\n' ;

}