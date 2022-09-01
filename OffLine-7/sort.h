#include<iostream>
#include<stdlib.h>

using namespace std ;

int partition(int*, int,int) ;
int randomized_partition(int*,int,int) ;
void quickSort(int*, int,int) ;
void randomizedQsort(int*, int,int) ;
void insertionSort(int*,int) ;
void merge_array(int*, int, int,int) ;
void mergeSort(int*, int, int) ;

/**
 * Quick sort Algorithm
 * 
 */

int partition(int *arr,int left,int right)
{
    int pivot=arr[right];
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
void quickSort(int *arr,int left,int high)
{
    if(left<high){
        int j=partition(arr,left,high);
        quickSort(arr,left,j-1);
        quickSort(arr,j+1,high);
    }
}

/**
 * Randomized QuickSort 
 */

int randomized_partition(int *arr,int left,int right)
{

    int random = left + rand() % (right-left) ;
    swap(arr[random],arr[right]) ;
    return partition(arr,left,right) ;
}
void randomizedQsort(int *arr,int left,int right)
{
    if(left<right){
        int j=randomized_partition(arr,left,right);
        randomizedQsort(arr,left,j-1);
        randomizedQsort(arr,j+1,right);
    }
}

/**
 * InsertionSort
 * 
 */


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

/**
 * MergeSort algorithm
 * 
 */

void merge_array(int* arr,int left,int middle,int right){
    int n = middle - left + 1;
    int m = right - middle;

    int arrayA [n] ;
    int arrayB [m] ;

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
        if(arrayA[i] > arrayB[j]) arr[k++] = arrayB[j++] ;
        else arr[k++] = arrayA[i++] ;
    }

    for(; i < n ; i++)
        arr[k++] = arrayA[i];
    for(; j < m ; j++)
        arr[k++] = arrayB[j];
}

void mergeSort(int* arr , int left , int right){
    int middle = (left + right)/ 2;

    if(left < right) {
        mergeSort(arr, left, middle) ;
        mergeSort(arr, middle + 1, right) ;

        merge_array(arr, left, middle, right) ;
    }
}

