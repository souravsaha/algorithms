#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "graph.c"

typedef struct subset
{
    //struct subset *parent; // parent or representative of subset
    //char value[MAX_WORD];  // value of the set
    int rank; // rank of the set
    int parent;
} subset;

/* find the parent */
int find(subset s[], int element)
{
    if (s[element].parent != element)
        s[element].parent = find(s, s[element].parent);

    return s[element].parent;
}
/* union of 2 sets */
void unionOperation(subset s[], int x, int y)
{
    int x_root = find(s, x);
    int y_root = find(s, y);

    if (s[x_root].rank < s[y_root].rank)
        s[x_root].parent = y_root;
    else if (s[x_root].rank > s[y_root].rank)
        s[y_root].parent = x_root;
    else
    {
        s[y_root].parent = x_root;
        s[x_root].rank++;
    }
}

int compareEdges(const void* a, const void* b)
{
    struct edge* a1 = (struct edge *)a;
    struct edge* b1 = (struct edge *)b;
    
    if (a1->weight > b1->weight)
        return 1;
    else if(a1->weight < b1->weight)
        return -1;
    else 
        return 0;
}

void krushkal_mst(GRAPH *g)
{
    int vertices = g->vertices;
    int edgeCount = 0;
    int edgeIndex = 0;
    int i;
    edge *spanningTree = Malloc(vertices, edge);
    /*
    for( i = 0; i < g->edges; i++)
        printf("%d %d %d\n", g->edgeList[i].source, g->edgeList[i].destination, g->edgeList[i].weight);
    */ 
    qsort(g->edgeList, g->edges, sizeof(g->edgeList[0]), compareEdges);
    /*
    printf("After Sorting \n");
    for (i = 0; i < g->edges; i++)
        printf("%d %d %d\n", g->edgeList[i].source, g->edgeList[i].destination, g->edgeList[i].weight);
    */
    subset *s = Malloc(vertices, subset);

    for (i = 0; i < vertices; i++)
    {
        s[i].parent = i;
        s[i].rank = 0;
    }

    while (edgeCount < vertices - 1)
    {
        edge nextEdge = g->edgeList[edgeIndex++];
        //printf("%d %d\n",nextEdge.source, nextEdge.destination );
        int x = find(s, nextEdge.source);
        int y = find(s, nextEdge.destination);
        if (x != y)
        {
            spanningTree[edgeCount++] = nextEdge;
            unionOperation(s, x, y);
        }
    }
    printf("Krushkal Spanning Tree: \n");
    for (i = 0; i < edgeCount; i++)
    {
        printf("sourc %d -------------- destination %d => weight %d \n", spanningTree[i].source, spanningTree[i].destination, spanningTree[i].weight);
    }
}

int main(int argc, char const *argv[])
{
    if (argc < 2)
        ERR_MESG("Number of vertices not given as input\n");

    GRAPH *g;
    //int source;
    int vertices = atoi(argv[1]);
    int edges = atoi(argv[2]);
    g = createGraph(vertices);
    g->edges = edges;
    int i;
    // Test Case 1
    g->edgeList = Malloc(edges, edge);

    for (i = 0; i < edges; i++)
        scanf("%d %d %d", &g->edgeList[i].source, &g->edgeList[i].destination, &g->edgeList[i].weight);
    
    //for( i = 0; i < edges; i++)
    //    printf("%d %d %d\n", g->edgeList[i].source, g->edgeList[i].destination, g->edgeList[i].weight);
    
    //source = 0;
    krushkal_mst(g);
    return 0;
}