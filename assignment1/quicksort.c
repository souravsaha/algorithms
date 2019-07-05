/*-----------------------------------
Name: Sourav Saha
Roll number: 1833
Program description: Recurse and Iterative Quick Sort routine
Acknowledgements: Arijit Bishnu
------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "common.h"
#define N 10
#define MAX_NUM 10000
#define AVG_COUNT 20
void swap(long int *x, long int *y)
{
    long int temp = *x;
    *x = *y;
    *y = temp;
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
long int partition(long int *array, long int start, long int end, long int *swap_count, long int *comparison_count)
{
    /* pivot is choosen as the end of the array */
    long int pivot = array[end];
    /* pick index of the smaller element*/
    long int smallIndex = (start - 1);  
    long int i;

    for (i = start; i <= end - 1; i++)
    {
        (*comparison_count)++;
        /* if the current elements is smaller than or equal to the pivot */
        if (array[i] <= pivot)
        {
            /* increment the index of smaller number*/
            smallIndex++;
            (*swap_count)++;
            swap(&array[smallIndex], &array[i]);
        }
    }
    (*swap_count)++;
    swap(&array[smallIndex + 1], &array[end]);
    return (smallIndex + 1);
}

void quick_sort_util_recur(long int *array, long int start, long int end, long int *swap_count, long int *comparison_count)
{
    long int partIndex;
    if (start < end)
    {
        (*comparison_count)++;
        /* get the pivot and partition the array */
        partIndex = partition(array, start, end, swap_count, comparison_count);
        /* recursively sort from start to partitionIndex and partitionIndex+1 to end */
        quick_sort_util_recur(array, start, partIndex - 1, swap_count, comparison_count);
        quick_sort_util_recur(array, partIndex + 1, end, swap_count, comparison_count);
    }
}

void quick_sort_recur()
{
    long int *array = Malloc(N, long int);
    long int start = 0;
    long int end = N - 1;
    long int i;
    for (i = 0; i < N; i++)
        array[i] = rand() % MAX_NUM;
    display(array, N);
    //quick_sort_util_recur(array, start, end);
    display(array, N);
}
/* iterative routine for quick sort*/
void quick_sort_util_iter(long int *array, long int start, long int end, long int *swap_count, long int *comparison_count)
{
    /* create a temp stack */
    long int *stack = Malloc(start - end + 1, long int);
    long int top = 0;
    /* push the initial start and end index into the stack */
    stack[top++] = start;
    stack[top] = end;
    /* proceed while stack is not empty */
    while (top >= 0)
    {
        //(*comparison_count)++;
        /* pop the satrt and end position from the stack */
        end = stack[top--];
        start = stack[top--];
        /* get the pivot and place it to it's correct position */
        long int partIndex = partition(array, start, end, swap_count, comparison_count);
        /* if some element exists on the left side of pivot index, push that left 
        index into the stack */
        
        if (partIndex - 1 > start)
        {
            (*comparison_count)++;
            stack[++top] = start;
            stack[++top] = partIndex - 1;
        }
        /* if there exists some element on the right side of pivot index, push  
        that right index into the stack */
        
        if (partIndex + 1 < end)
        {
            (*comparison_count)++;
            stack[++top] = partIndex + 1;
            stack[++top] = end;
        }
    }
    free(stack);
}
void quick_sort_iter()
{
    long int *array = Malloc(N, long int);
    long int start = 0;
    long int end = N - 1;
    long int i;
    for (i = 0; i < N; i++)
        array[i] = rand() % MAX_NUM;
    display(array, N);
    //quick_sort_util_iter(array, start, end);
    display(array, N);
}

int main(int argc, char const *argv[])
{
    /*
    char ch;

    printf("Quick Sort :\n");
    printf("Which version you want to run? Press i for iterative one and r for the recursive one\n");
    scanf("%c", &ch);

    switch (ch)
    {
    case 'i':
        quick_sort_iter();
        break;
    case 'r':
        quick_sort_recur();
        break;
    default:
        printf("Wrong option choosen. Please run the program again\n");
        break;
    }
    */

    long int arrayLength = 0, i;
    FILE *fp;
    srand(time(NULL));

    fp = fopen("quickSortTime.dat", "w");
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
            quick_sort_util_recur(array1, 0, arrayLength - 1, &swap_count_rec, &comparison_count_rec);
            clock_t t1 = clock();
            t0_count += ((long double)(t1 - t0)) / CLOCKS_PER_SEC;
            clock_t t2 = clock();
            quick_sort_util_iter(array2, 0, arrayLength - 1, &swap_count_iter, &comparison_count_iter);
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
        comparison_number_rec = comparison_number_rec/AVG_COUNT;
        comparison_number_iter = comparison_number_iter/AVG_COUNT;
        swap_number_rec = swap_number_rec/AVG_COUNT; 
        swap_number_iter = swap_number_iter/AVG_COUNT;
        fprintf(fp, "%ld  %Lf  %Lf %Lf %Lf %Lf %Lf\n", arrayLength, t0_count, t1_count, swap_number_rec, swap_number_iter, comparison_number_rec, comparison_number_iter);
    }
    fclose(fp);
    return 0;
}
