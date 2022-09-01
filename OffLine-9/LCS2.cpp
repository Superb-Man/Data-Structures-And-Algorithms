#include<iostream>

void LCSfinder(std::string S1, std::string S2) {
    int n = S1.length() ;
    int m = S2.length() ;
    int x,y,len = 0 ;
    int lcs [n+1][m+1] ;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i == 0 || j == 0)   lcs[i][j] = 0; //1st row and 1st column value = 0
            else if (S1[i - 1] == S2[j - 1])    //if matches increase the previous cell value by 1
                lcs[i][j] = lcs[i - 1][j - 1] + 1;
            else
                lcs[i][j] = 0 ; //new substring can start from next move
            if(len < lcs[i][j]){
                x = i ;
                y = j ;
                len = lcs[i][j] ;
            }
        }
    }

    for(int i = 0 ; i <= n ;i++ ){
        for(int j = 0 ; j<= m ;j++){
            std::cout << lcs[i][j] <<" " ;
        }
        std::cout << '\n' ;
    }

    int length = len ;
    char str[length + 1] ;
    str[length] = '\0';
    int i = x, j = y;
    while(i > 0){
        str[length - 1] = S1[i-1] ;
        length-- ;
        i-- ;
    }

    std:: cout << len << '\n' << str << '\n' ;
}

int main() {
    std::string S1,S2 ;
    std :: cin >> S1 >> S2 ;
    LCSfinder(S1,S2) ;
}
