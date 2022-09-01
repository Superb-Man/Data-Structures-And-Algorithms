#include<stdio.h>
#include<stdlib.h>
int mx=-1000000000;
int max(int x,int y)
{
    if(x>=y) return x;
    else return y; 
}
int main()
{
    int *p;
    int n,sum=0,i;
    scanf("%d", &n);
    p=(int *)malloc(n*sizeof(int));
    for(i=0;i<n;i++)
    {
        scanf("%d", p+i);
    }
    for(i=0;i<n;i++)
    {
        sum+=*(p+i);
        mx=max(sum,mx);
        if(sum<0) sum=0;
    }
    printf("%d", mx);
}
