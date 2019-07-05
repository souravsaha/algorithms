/*-----------------------------------
Name: Sourav Saha
Roll number: 1833
Program description: Recurse and Iterative Merge Sort routine
Acknowledgements: Arijit Bishnu
------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "common.h"
//#define N 10
#define MAX_NUM 10000
#define AVG_COUNT 20
/* Merge function : 
   merges 2 subarray array[start to mid]  and array[mid+1 to end]
*/
void merge(long int *array, long int start, long int mid, long int end, long int *swap_count, long int *comparison_count)
{
    long int leftIndex = mid - start + 1;
    long int rightIndex = end - mid;
    long int *left = Malloc(leftIndex, long int);
    long int *right = Malloc(rightIndex, long int);
    long int i, j, index;

    // copy data from start to middle
    for (i = 0; i < leftIndex; i++)
    {
        (*swap_count)++;
        left[i] = array[start + i];
    }
    // copy data from middle to end
    for (j = 0; j < rightIndex; j++)
    {
        (*swap_count)++;
        right[j] = array[mid + 1 + j];
    }
    i = 0, j = 0, index = start;
    /* copy while any of the array is not empty */
    while (i < leftIndex && j < rightIndex)
    {   
        (*comparison_count)++;
        (*comparison_count)++;
        if (left[i] <= right[j])
            array[index++] = left[i++];

        else
            array[index++] = right[j++];
    }
    /* copy the remaining */
    while (i < leftIndex)
    {
        (*comparison_count)++;
        array[index++] = left[i++];
    }
    while (j < rightIndex)
    {
        (*comparison_count)++;
        array[index++] = right[j++];
    }
    free(left);
    free(right);
}

void merge_sort_util_recur(long int *array, long int start, long int end, long int *swap_count, long int *comparison_count)
{
    if (start < end)
    {
        (*comparison_count)++;
        /* find middle */
        long int mid = start + (end - start) / 2;
        /* recursively solve for array[start to mid] */
        merge_sort_util_recur(array, start, mid, swap_count, comparison_count);
        /* recursively solve for array[mid+1 to end] */
        merge_sort_util_recur(array, mid + 1, end, swap_count, comparison_count);
        /* combine the subarray */
        merge(array, start, mid, end, swap_count, comparison_count);
    }
}
/* display the array */
void display(long int *array, long int n)
{
    long int i;
    printf("\n");
    for (i = 0; i < n; i++)
        printf("%ld  ", array[i]);
    printf("\n");
}
/*
void merge_sort_recur()
{
    int *array = Malloc(N, int);
    int start = 0;
    int end = N - 1;
    int i;
    for (i = 0; i < N; i++)
        array[i] = rand() % MAX_NUM;
    display(array, N);
    merge_sort_util_recur(array, start, end);
    display(array, N);
}*/
/* iterative version of merge sort */
void merge_sort_iter(long int *array, long int len, long int *swap_count, long int *comparison_count)
{
    //int *array = Malloc(N, int);
    long int start = 0;
    long int end;
    long int size, mid;
    //for (i = 0; i < N; i++)
    //    array[i] = rand() % MAX_NUM;
    //display(array, N);
    /* merge subarray of size to 2, then 4, 8... so on*/
    for (size = 1; size <= len - 1; size = 2 * size)
    {
        //(*comparison_count)++;
        /* pick the start position of each sub array */
        for (start = 0; start < len - 1; start += 2 * size)
        {
            (*comparison_count)++;            
            //mid = start + size - 1; // middle will left most start plus middle
            end = MIN(start + (2 * size - 1), len - 1);
            mid = start + (end-start)/ 2;
            merge(array, start, mid, end, swap_count, comparison_count);
        }
    }
    //display(array, N);
}

int main(int argc, char const *argv[])
{
    /*
    char ch;

    printf("Merge Sort :\n");
    printf("Which version you want to run? Press i for iterative one and r for the recursive one\n");
    scanf("%c", &ch);

    switch (ch)
    {
    case 'i':
        merge_sort_iter();
        break;
    case 'r':
        merge_sort_recur();
        break;
    default:
        printf("Wrong option choosen. Please run the program again\n");
        break;
    }
    */

    long int arrayLength = 0, i;
    FILE *fp;
    srand(time(NULL));
    fp = fopen("mergeSortTime.dat", "w");
    if (fp == NULL)
        ERR_MESG("Unable to create file\n");
    /* generate different size array */
    for (arrayLength = 100; arrayLength < 100000; arrayLength += 100)
    {
        long double t0_count = 0.0, t1_count = 0.0;
        long int swap_count_rec = 0, comparison_count_rec = 0;
        long int swap_count_iter = 0, comparison_count_iter = 0;
        long double swap_number_rec = 0, comparison_number_rec = 0;
        long double swap_number_iter = 0, comparison_number_iter = 0;

        /* take the avg count */
        for (i = 0; i < AVG_COUNT; i++)
        {
            //clock_t t0, t1;
            long int *array1 = Malloc(arrayLength, long int);
            long int *array2 = Malloc(arrayLength, long int);
            long int j;

            for (j = 0; j < arrayLength; j++)
            {
                long int temp = rand() % MAX_NUM;
                array1[j] = temp;
                array2[j] = temp;
            }

            clock_t t0 = clock();
            merge_sort_util_recur(array1, 0, arrayLength - 1, &swap_count_rec, &comparison_count_rec);
            clock_t t1 = clock();
            t0_count += ((long double)(t1 - t0)) / CLOCKS_PER_SEC;

            clock_t t2 = clock();
            merge_sort_iter(array2, arrayLength, &swap_count_iter, &comparison_count_iter);
            clock_t t3 = clock();
            t1_count += ((long double)(t3 - t2)) / CLOCKS_PER_SEC;

            comparison_number_rec += comparison_count_rec;
            comparison_number_iter += comparison_count_iter;
            swap_number_rec += swap_count_rec;
            swap_number_iter += swap_count_iter;
            
            comparison_count_rec = 0;
            comparison_count_iter = 0;
            swap_count_rec = 0;
            swap_count_iter = 0;


            free(array1);
            free(array2);
        }
        t0_count = t0_count / AVG_COUNT;
        t1_count = t1_count / AVG_COUNT;

        fprintf(fp, "%ld  %Lf  %Lf %Lf %Lf %Lf %Lf %f\n", arrayLength, t0_count, t1_count, swap_number_rec, swap_number_iter, comparison_number_rec, comparison_number_iter, arrayLength * log(arrayLength));
    }
    fclose(fp);
    return 0;
}
