#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include "common.h"
#include "graph.c"

// Structure to represent a min heap node
typedef struct MinHeapNode
{
    int v;
    int dist;
} MinHeapNode;

// Structure to represent a min heap
typedef struct MinHeap
{
    int size;     // Number of heap nodes present currently
    int capacity; // Capacity of min heap
    int *pos;     // This is needed for decreaseKey()
    struct MinHeapNode **array;
} MinHeap;

// A utility function to create a new Min Heap Node
MinHeapNode *newMinHeapNode(int v, int dist)
{
    struct MinHeapNode *minHeapNode =
        (struct MinHeapNode *)malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}
// A utility function to create a Min Heap
MinHeap *createMinHeap(int capacity)
{
    struct MinHeap *minHeap =
        (struct MinHeap *)malloc(sizeof(struct MinHeap));
    minHeap->pos = (int *)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array =
        (struct MinHeapNode **)malloc(capacity * sizeof(struct MinHeapNode *));
    return minHeap;
}

// A utility function to swap two nodes of min heap. Needed for min heapify
void swapMinHeapNode(struct MinHeapNode **a, struct MinHeapNode **b)
{
    struct MinHeapNode *t = *a;
    *a = *b;
    *b = t;
}
void minHeapify(struct MinHeap *minHeap, int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < minHeap->size &&
        minHeap->array[left]->dist < minHeap->array[smallest]->dist)
        smallest = left;

    if (right < minHeap->size &&
        minHeap->array[right]->dist < minHeap->array[smallest]->dist)
        smallest = right;

    if (smallest != idx)
    {
        // The nodes to be swapped in min heap
        MinHeapNode *smallestNode = minHeap->array[smallest];
        MinHeapNode *idxNode = minHeap->array[idx];

        // Swap positions
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;

        // Swap nodes
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}
int isEmpty(struct MinHeap *minHeap)
{
    return minHeap->size == 0;
}

struct MinHeapNode *extractMin(struct MinHeap *minHeap)
{
    if (isEmpty(minHeap))
        return NULL;

    // Store the root node
    struct MinHeapNode *root = minHeap->array[0];

    // Replace root node with last node
    struct MinHeapNode *lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

    // Update position of last node
    minHeap->pos[root->v] = minHeap->size - 1;
    minHeap->pos[lastNode->v] = 0;

    // Reduce heap size and heapify root
    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}
void decreaseKey(struct MinHeap *minHeap, int v, int dist)
{
    // Get the index of v in  heap array
    int i = minHeap->pos[v];

    // Get the node and update its dist value
    minHeap->array[i]->dist = dist;

    // Travel up while the complete tree is not hepified.
    // This is a O(Logn) loop
    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist)
    {
        // Swap this node with its parent
        minHeap->pos[minHeap->array[i]->v] = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);

        // move to parent index
        i = (i - 1) / 2;
    }
}

bool isInMinHeap(struct MinHeap *minHeap, int v)
{
    if (minHeap->pos[v] < minHeap->size)
        return true;
    return false;
}

void printDistanceVector(int *distances, int vertices, int source)
{
    printf("Vertex Number\t Distance from source %d\n", source);
    int i;
    for( i = 0; i < vertices; i++)
        printf("%d\t%d \n", i, distances[i]);
    
}

void dijkstra(GRAPH *g, int source)
{
    int vertices = g->vertices;
    int *distances = Malloc(vertices, int);
    // TODO repalce with standard library
    MinHeap *h = createMinHeap(vertices);
    int i;

    for (i = 0; i < g->vertices; i++)
    {
        distances[i] = INT_MAX;
        h->array[i] = newMinHeapNode(i, distances[i]);
        h->pos[i] = i;
    }
    h->array[source] = newMinHeapNode(source, distances[source]);
    h->pos[source] = source;
    distances[source] = 0;
    decreaseKey(h, source, distances[source]);
    h->size = g->vertices;

    while (h->size != 0)
    {
        MinHeapNode* heapNode = extractMin(h);
        int vertexNumber = heapNode->v;
        adjListNode *iter;
        for (iter = g->array[vertexNumber].head; iter != NULL; iter = iter->next)
        {
            int v = iter->data;
            if (isInMinHeap(h, v) && distances[vertexNumber] != INT_MAX && iter->weight + distances[vertexNumber] < distances[v])
            {
                distances[v] = distances[vertexNumber] + iter->weight;
                decreaseKey(h, v, distances[v]);
            }
        }
    }
    printDistanceVector(distances, g->vertices, source);
}

int main(int argc, char const *argv[])
{
    if (argc < 2)
        ERR_MESG("Number of vertices not given as input\n");

    GRAPH *g;
    int source;
    int vertices = atoi(argv[1]);
    int edges = atoi(argv[2]);
    g = createGraph(vertices);
    int i;
    int src, dest, weight;
    for( i = 0; i < edges; i++)
    {
        scanf("%d %d %d", &src, &dest, &weight);
        addEdgeWeight(g, src, dest, weight);
        addEdgeWeight(g, dest, src, weight);
    }
    
    source = 0;
    dijkstra(g, source);
    return 0;
}
