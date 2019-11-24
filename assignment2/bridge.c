#include <stdio.h>
#include "common.h"
#include "graph.c"

void findBridges(int vertex, int visited[], GRAPH *g, int discovery[], int low[], int parent[], int *time)
{
    visited[vertex] = TRUE; // mark the vertex as true
    (*time)++;
    discovery[vertex] = low[vertex] = (*time);
    adjListNode *iter;
    for (iter = g->array[vertex].head; iter != NULL; iter = iter->next)
    {
        int v = iter->data;
        
        if (!visited[v]) 
        {
            parent[v] = vertex;
            findBridges(v, visited, g, discovery, low, parent, time);
            low[vertex] = MIN(low[vertex], low[v]);

            if(low[v] > discovery[vertex])
                printf("%d -- %d\n",vertex, v);
        }
        else if(v != parent[vertex])
        {
            low[vertex] = MIN(low[vertex], discovery[v]);
        }
    }
}

int main(int argc, char const *argv[])
{
    if (argc < 2)
        ERR_MESG("Number of vertices not given as input\n");
    int i;
    int time = 0;
    GRAPH *g;
    //int source;
    int vertices = atoi(argv[1]);
    g = createGraph(vertices);

    // sample # test case 1
    /*
    addEdge(g, 0, 1);
    addEdge(g, 1, 0);
    addEdge(g, 0, 2);
    addEdge(g, 2, 0);
    addEdge(g, 1, 2);
    addEdge(g, 2, 1);
    addEdge(g, 1, 6);
    addEdge(g, 6, 1);
    addEdge(g, 1, 3);
    addEdge(g, 3, 1);
    addEdge(g, 1, 4);
    addEdge(g, 4, 1);
    addEdge(g, 3, 5);
    addEdge(g, 5, 3);
    addEdge(g, 4, 5);
    addEdge(g, 5, 4);
    */
    // sample # test case 2
    /*
    addEdge(g, 0, 1);
    addEdge(g, 1, 0);

    addEdge(g, 1, 3);
    addEdge(g, 3, 1);

    addEdge(g, 2, 3);
    addEdge(g, 3, 2);

    addEdge(g, 2, 0);
    addEdge(g, 0, 2);

    addEdge(g, 3, 4);
    addEdge(g, 4, 3);

    addEdge(g, 4, 5);
    addEdge(g, 5, 4);

    addEdge(g, 5, 6);
    addEdge(g, 6, 5);

    addEdge(g, 6, 7);
    addEdge(g, 7, 6);

    addEdge(g, 6, 8);
    addEdge(g, 8, 6);

    addEdge(g, 8, 9);
    addEdge(g, 9, 8);

    addEdge(g, 9, 10);
    addEdge(g, 10, 9);

    addEdge(g, 10, 12);
    addEdge(g, 12, 10);

    addEdge(g, 8, 10);
    addEdge(g, 10, 8);

    addEdge(g, 6, 11);
    addEdge(g, 11, 6);

    addEdge(g, 11, 12);
    addEdge(g, 12, 11);
    
    addEdge(g, 11, 13);
    addEdge(g, 13, 11);
    */
    // sample test case 3
    /*
    addEdge(g, 0, 1);
    addEdge(g, 1, 0);

    addEdge(g, 1, 2);
    addEdge(g, 2, 1);

    addEdge(g, 2, 3);
    addEdge(g, 3, 2);

    addEdge(g, 2, 4);
    addEdge(g, 4, 2);

    addEdge(g, 4, 3);
    addEdge(g, 3, 4);

    addEdge(g, 1, 5);
    addEdge(g, 5, 1);

    addEdge(g, 0, 6);
    addEdge(g, 6, 0);

    addEdge(g, 5, 6);
    addEdge(g, 6, 5);

    addEdge(g, 6, 7);
    addEdge(g, 7, 6);

    addEdge(g, 7, 8);
    addEdge(g, 8, 7);

    addEdge(g, 7, 9);
    addEdge(g, 9, 7);

    addEdge(g, 8, 9);
    addEdge(g, 9, 8);
    */

    // sample test case 4
    addEdge(g, 0, 1);
    addEdge(g, 1, 0);

    addEdge(g, 0, 2);
    addEdge(g, 2, 0);

    addEdge(g, 1, 3);
    addEdge(g, 3, 1);

    addEdge(g, 1, 4);
    addEdge(g, 4, 1);

    addEdge(g, 2, 5);
    addEdge(g, 5, 2);

    addEdge(g, 2, 6);
    addEdge(g, 6, 2);

    addEdge(g, 6, 7);
    addEdge(g, 7, 6);

    addEdge(g, 6, 8);
    addEdge(g, 8, 6);

    addEdge(g, 7, 9);
    addEdge(g, 9, 7);

    addEdge(g, 7, 10);
    addEdge(g, 10, 7);

    addEdge(g, 8, 11);
    addEdge(g, 11, 8);

    addEdge(g, 11, 12);
    addEdge(g, 12, 11);

    int *visited = Malloc(vertices, int);
    int *discovery = Malloc(vertices, int);
    int *parent = Malloc(vertices, int);
    int *low = Malloc(vertices, int);

    for (i = 0; i < g->vertices; i++)
    {
        visited[i] = FALSE;
        parent[i] = -1;
    }
    for (i = 0; i < vertices; i++)
        if (visited[i] == FALSE)
            findBridges(i, visited, g, discovery, low, parent, &time);

    return 0;
}
