#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define ll long long int
int strmp(int *p,int *q)
{
    for(;*p==*q;p++,q++)
    {
        if(*p=='\0') return 0;
    }
    return *p-*q;
}
void swap(int *arr,int p,int q)
{
    int temp=*(arr+q);
    *(arr+q)=*(arr+p);
    *(arr+p)=temp;
}
void q_sort(int *arr,int left,int right)
{
    int i,h;
    if(left>=right) return;
    swap(arr,left,(left+right)/2);
    h=left;
    for(i=left+1;i<=right;i++)
    {
        if(strmp(arr+i,arr+left)<0)
        {
            swap(arr,++h,i);
        }
    }
    swap(arr,left,h);
    q_sort(arr,left,h-1);
    q_sort(arr,h+1,right);
}
int main()
{
    int n;
    scanf("%d", &n);
    int *arr;
    arr=(int *)malloc(n*sizeof(int));
    for(int i=0;i<n;i++) scanf("%d", arr+i);
    q_sort(arr,0,n-1);
    for(int i=0;i<n;i++) printf("%d  ", *(arr+i));
}
