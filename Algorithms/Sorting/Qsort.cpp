#include<iostream>
#include<stdlib.h>

using namespace std ;

int partition(int *arr,int left,int right)
{
    int pivot=arr[right];
    int i=left -1 ;

    for(int j=left; j < right;j++){
        if( arr[j]<pivot ){
            i++;
            swap( arr[i],arr[j] );
        }
    }
    swap(arr[i+1],arr[right]);
    return i+1;
}
void q_sort(int *arr,int left,int high)
{
    if(left<high){
        int j=partition(arr,left,high);
        q_sort(arr,left,j-1);
        q_sort(arr,j+1,high);
    }
}
int main()
{
    int n,i;
    cin >> n ;
    int *arr;
    arr=(int *)malloc(n*sizeof(int));
    for(i=0;i<n;i++) cin >> arr[i] ;
    q_sort(arr,0,n-1);
    for(i=0;i<n;i++) cout << arr[i] <<" " ;
    return 0;
}
/**
10
10 8 9 12 7 13 22 15 21 4
*/
//./Algorithms/Sorting/Qsort.exe
