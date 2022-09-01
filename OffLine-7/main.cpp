#include <iostream>
#include<fstream>
#include<cstdio>
#include<ctime>
#include<algorithm>
#include "sort.h"

int main()
{
    const int TOTAL_ITERATION = 20 ;
    freopen("output.csv", "w", stdout);

    cout<<"n,Mergesort,Quicksort,Randomized Quicksort,Insertion Sort, STL sort, Quicksort with sorted input, Randomized Quicksort with sorted input"<<std::endl;

    int len[] = {5, 10, 100, 1000, 10000, 100000};

    for (int l = 0; l < 6; l++)
    {
        int n = len[l];
        int *ara = new int[n];
        int *ara2 = new int[n];

        double mergeSortTime = 0,
               quickSortTime = 0,
               randomizedQsortTime = 0,
               insertionSortTime = 0,
               sortedQsortTime = 0,
               sortedRandomizedQsortTime = 0,
               stlSortTime = 0;

        for (int iteration = 0; iteration < TOTAL_ITERATION; iteration++)
        {
            

            for (int i = 0; i < n; i++) ara[i] = rand();


            for (int i = 0; i < n; i++) ara2[i] = ara[i];
            clock_t start = clock();
            mergeSort(ara2, 0, n - 1);
            mergeSortTime += (double(clock() - start) / CLOCKS_PER_SEC);

            for (int i = 0; i < n; i++) ara2[i] = ara[i];
            start = clock();
            quickSort(ara2, 0, n - 1);
            quickSortTime += (double(clock() - start) / CLOCKS_PER_SEC);

            for (int i = 0; i < n; i++) ara2[i] = ara[i];
            start = clock();
            randomizedQsort(ara2, 0, n - 1);
            randomizedQsortTime += (double(clock() - start) / CLOCKS_PER_SEC);

            for (int i = 0; i < n; i++) ara2[i] = ara[i];
            start = clock();
            insertionSort(ara2, n);
            insertionSortTime += (double(clock() - start) / CLOCKS_PER_SEC);

            for (int i = 0; i < n; i++) ara2[i] = ara[i];
            start = clock();
            sort(ara2,ara2+n);
            stlSortTime += (double(clock() - start) / CLOCKS_PER_SEC);

            start = clock();
            quickSort(ara2, 0, n - 1);
            sortedQsortTime += (double(clock() - start) / CLOCKS_PER_SEC);
            
            start = clock();
            randomizedQsort(ara2, 0, n - 1);
            sortedRandomizedQsortTime += (double(clock() - start) / CLOCKS_PER_SEC);
        }


        mergeSortTime /= TOTAL_ITERATION;
        quickSortTime /= TOTAL_ITERATION;
        randomizedQsortTime /= TOTAL_ITERATION;
        insertionSortTime /= TOTAL_ITERATION;
        sortedQsortTime /= TOTAL_ITERATION;
        sortedRandomizedQsortTime /= TOTAL_ITERATION;
        stlSortTime /= TOTAL_ITERATION;

        delete[] ara;
        delete[] ara2;
        cout<<n<<",";


        printf("%0.5lf,",mergeSortTime*1000);
        printf("%0.5lf,",quickSortTime*1000);
        printf("%0.5lf,",randomizedQsortTime*1000);
        printf("%0.5lf,",insertionSortTime*1000);
        printf("%0.5lf,",stlSortTime*1000);
        printf("%0.5lf,",sortedQsortTime*1000);
        printf("%0.5lf\n",sortedRandomizedQsortTime*1000);
        
    }

    //cout <<"RETURN 0" <<endl; 



    return 0;
}