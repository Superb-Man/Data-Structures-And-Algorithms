#include<iostream>
#include<stdlib.h>

using namespace std ;

int randomized_partition(int *arr,int left,int right)
{

    int random = left + rand() % (right-left) ;
    swap(arr[random],arr[right]) ;
    int pivot = arr[right] ;
    int i=left,j=right;
    while(i<j)
    {
        while(arr[j] >= pivot)//arr[i]<=pivot
        {
            j-- ;
        }
        while(arr[i] < pivot)//arr[j]>pivot
        {
            i++ ;
        }
        if(i<j)
        swap(arr[i],arr[j]);
        //printf("Swapping %d and %d \n",arr[j] ,arr[i]) ;
    }
    swap(arr[right],arr[i]);
    //printf("Swapping %d and %d \n",arr[j] ,arr[left]) ;
    return i;
}
void randomized_Qsort(int *arr,int left,int right)
{
    if(left<right){
        int j=randomized_partition(arr,left,right);
        randomized_Qsort(arr,left,j-1);
        randomized_Qsort(arr,j+1,right);
    }
}
int main()
{
    int n =10,i;
    int arr[10]={10,8,9,12,7,13,22,15,21,4} ;
    randomized_Qsort(arr,0,n-1);
    for(i=0;i<n;i++) cout << arr[i] <<" " ;
    return 0;
}
/**
10
10 8 9 12 7 13 22 15 21 4
*/
//./Algorithms/Sorting/RandomizedQsort.exe
