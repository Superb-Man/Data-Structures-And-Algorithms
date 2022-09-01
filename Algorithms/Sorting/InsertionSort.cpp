#include<iostream>
#include<stdlib.h>

using namespace std ;

void insertionSort(int* arr, int size ){
    for(int i = 1 ; i < size ; i++){
        int key = arr[i] ;
        int j = i-1 ;
        while(arr[j] > key && j>=0){
            arr[j+1] = arr[j] ;
            j-- ;
        }
        arr[j+1] = key ; 
    } 
}

int main()
{
    int n,i;
    cin >> n ;
    int *arr;
    arr=(int *)malloc(n*sizeof(int));
    for(i=0;i<n;i++) cin >> arr[i] ;
    insertionSort(arr,n);
    for(i=0;i<n;i++) cout << arr[i] <<" " ;
    return 0;
}
/**
10
10 8 9 12 7 13 22 15 21 4
*/
//./Algorithms/Sorting/InsertionSort.exe