#include<iostream>
const int MAX_INT = 1e8+7 ;

int dp[1024] ; // As 2^10 bit_design possible
int c[10][10] ; // 2D array for cost

int calculateCost(int _bitset ,int n){

    if(_bitset == 0) return 0 ;

    if(dp[_bitset]!= 0)
        return dp[_bitset] ;

    int ans = MAX_INT ;

    for(int i = n-1 ; i >= 0 ; i--){

        if((_bitset & (1 << i)) != 0) {// i th city is not visited yet!

            int sum = 0 ;

            for(int j = n-1 ; j >= 0 ; j--){
                if((_bitset & (1 << j)) == 0){ //j th city already visited
                    sum+= c[i][j] ;
                }
            }

            ans = std :: min(ans , c[i][i] + sum + calculateCost((_bitset ^ (1 << i)), n)) ;
            //change the bitset at atmost 1 position using xor so use << operator
        }
    }

    return dp[_bitset] = ans ;


}

int main()
{
    int n ;
    std :: cin>>n;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++) {
            std :: cin >> c[i][j];
        }
    }
    std :: cout<< calculateCost((1 << n) - 1, n);

    return 0;
}
