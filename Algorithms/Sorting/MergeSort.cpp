#include<iostream>
#include<stdlib.h>
#include<vector>

using namespace std ;

int merge_array(int* arr,int left,int middle,int right){
    int in_c = 0 ;
    int n = middle - left + 1;
    int m = right - middle;

    int* arrayA= new int[n] ;
    int* arrayB = new int[m] ;

    //storing leftside sorted array in temp array
    for(int i = 0; i < n; i++)
        arrayA[i] = arr[left+i] ;

    //storing rightside sorted array in temp array
    for(int i = 0 ; i < m ; i++)
        arrayB[i] = arr[middle+1+i] ;

    //merging two temp arrays in a third one
    int i = 0, j= 0 , k = left;
    while(i < n && j < m)
    {
        if(arrayA[i] > arrayB[j])
        {
            arr[k++] = arrayB[j++] ;
            in_c = in_c + n-i ;
        }
        else arr[k++] = arrayA[i++] ;
    }

    for(; i < n ; i++)
        arr[k++] = arrayA[i];
    for(; j < m ; j++)
        arr[k++] = arrayB[j];

    return in_c ;
}

int mergeSort(int* arr , int left , int right){
    int in_c =0 ;
    int middle = (left + right)/ 2;

    if(left < right) {
        in_c+=mergeSort(arr, left, middle) ;
        in_c+= mergeSort(arr, middle + 1, right) ;

        in_c+= merge_array(arr, left, middle, right) ;
    }

    return in_c ;
}

int main()
{
    int n,i;
    cin >> n ;
    int *arr;
    arr=(int *)malloc(n*sizeof(int));
    for(i=0;i<n;i++) cin >> arr[i] ;
    cout << mergeSort(arr,0,n-1) << endl;
    for(i=0;i<n;i++) cout << arr[i] <<" " ;
    return 0;
}
