/*-----------------------------------
Name: Sourav Saha
Roll number: 1833
Program description: Recurse and Iterative Heap Sort routine
Acknowledgements: Arijit Bishnu
------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "common.h"
#define N 10
#define MAX_NUM 10000
#define AVG_COUNT 20

/* parent index */
long int parent(long int i)
{
    return (i - 1) / 2;
}
/* left child index */
long int leftChild(long int i)
{
    return (2 * i + 1);
}
/* right child index */
long int rightChild(long int i)
{
    return (2 * i + 2);
}
void swap(long int *x, long int *y)
{
    long int temp = *x;
    *x = *y;
    *y = temp;
}
void heapify(long int *array, long int len, long int i, long int *swap_count, long int *comparison_count)
{
    long int max = i;
    long int leftChildIndex = leftChild(i);          // left child
    long int rightChildIndex = rightChild(i);        // right child
    (*comparison_count)++;
    /* choose the child with larger key and also its within range */
    if (leftChildIndex < len && array[leftChildIndex] > array[max])
    {
        (*comparison_count)++;
        max = leftChildIndex;
    }
    if (rightChildIndex < len && array[rightChildIndex] > array[max])
    {
        (*comparison_count)++;
        max = rightChildIndex;
    }
    /* swap parent with the largest child*/
    
    if (max != i)
    {
        //(*comparison_count)++;
        (*swap_count)++;
        swap(&array[i], &array[max]);
        heapify(array, len, max, swap_count, comparison_count);
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
void heap_sort_util_recur(long int *array, long int len, long int *swap_count, long int *comparison_count)
{
    long int i;
    /* build the heap */
    for (i = len / 2 - 1; i >= 0; i--)
        heapify(array, len, i, swap_count, comparison_count);
    /* extract element from heap */
    for (i = len - 1; i >= 0; i--)
    {
        /* move the root at the end */
        (*swap_count)++;
        swap(&array[0], &array[i]);
        heapify(array, i, 0, swap_count, comparison_count);
    }
}

void heap_sort_recur()
{
    long int *array = Malloc(N, long int);
    long int i;
    for (i = 0; i < N; i++)
        array[i] = rand() % MAX_NUM;
    display(array, N);
    //heap_sort_util_recur(array, N);
    display(array, N);
}

void build_max_heap(long int *array, long int len, long int *swap_count, long int *comparison_count)
{
    long int i;
    long int j;
    for (i = 1; i < len; i++)
    {
        
        /* check if child is bigger than parent*/
        if (array[i] > array[parent(i)])
        {
            j = i; // pick the child
            (*comparison_count)++;
            /* keep on swapping parent with child until parent is smaller*/
            while (array[j] > array[parent(j)])
            {
                (*swap_count)++;
                (*comparison_count)++;
                swap(&array[j], &array[parent(j)]);
                j = parent(j);
            }
        }
    }
}

void heap_sort_util_iter(long int *array, long int len, long int *swap_count, long int *comparsion_count)
{
    build_max_heap(array, len, swap_count, comparsion_count);
    long int i;
    /* extract element from heap */
    for (i = len - 1; i > 0; i--)
    {
        (*swap_count)++;
        /* move the root at the end */
        swap(&array[0], &array[i]);
        //instead of recursive heapify run a while loop
        long int childIndex;
        long int j = 0;
        while(1)
        {
            childIndex = leftChild(j);
            //printf("%ld %ld %ld\n", childIndex, j, len);
            (*comparsion_count)++;
            /* check if left child is smaller than right child, child index point to right child*/
            if (childIndex < (i - 1) && array[childIndex] < array[childIndex + 1])
            {
                (*comparsion_count)++;
                childIndex++;
            }
            /* if parent is smaller than child, swap it */
            if (childIndex < i && array[j] < array[childIndex])
            {
                (*swap_count)++;
                (*comparsion_count)++;
                swap(&array[j], &array[childIndex]);
            }
            j = childIndex;
            if (childIndex >= i)
                break;
        }
    }
}

void heap_sort_iter()
{
    long int *array = Malloc(N, long int);
    long int i;
    for (i = 0; i < N; i++)
        array[i] = rand() % MAX_NUM;
    display(array, N);
    //heap_sort_util_iter(array, N);
    display(array, N);
}

int main(int argc, char const *argv[])
{
    /*
    char ch;
    printf("Heap Sort :\n");
    printf("Which version you want to run? Press i for iterative one and r for the recursive one\n");
    scanf("%c", &ch);

    switch (ch)
    {
    case 'i':
        heap_sort_iter();
        break;
    case 'r':
        heap_sort_recur();
        break;
    default:
        printf("Wrong option choosen. Please run the program again\n");
        break;
    }
*/
    long int arrayLength = 0, i;
    FILE *fp;
    srand(time(NULL));

    fp = fopen("heapSortTime.dat", "w");
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
            heap_sort_util_recur(array1, arrayLength, &swap_count_rec, &comparison_count_rec);
            clock_t t1 = clock();
            t0_count += ((long double)(t1 - t0)) / CLOCKS_PER_SEC;

            clock_t t2 = clock();
            heap_sort_util_iter(array2, arrayLength, &swap_count_iter, &comparison_count_iter);
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
        t0_count = t0_count/AVG_COUNT;
        t1_count = t1_count/AVG_COUNT;
        comparison_number_rec = comparison_number_rec/AVG_COUNT;
        comparison_number_iter = comparison_number_iter/AVG_COUNT;
        swap_number_rec = swap_number_rec/AVG_COUNT; 
        swap_number_iter = swap_number_iter/AVG_COUNT; 
        fprintf(fp, "%ld  %Lf  %Lf %Lf %Lf %Lf %Lf\n", arrayLength, t0_count, t1_count, swap_number_rec, swap_number_iter, comparison_number_rec, comparison_number_iter);
    }
    fclose(fp);
    return 0;
}
