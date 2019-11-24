#include <stdio.h>
#include "common.h"
#include "graph.c"

void dfs(int vertex, int visited[], GRAPH *g)
{
    visited[vertex] = TRUE;
    printf("%d ", vertex);
    adjListNode *iter;
    for (iter = g->array[vertex].head; iter != NULL; iter = iter->next)
    {
        if (visited[iter->data] == FALSE)
            dfs(iter->data, visited, g);
    }
}
void topologicalSort(int vertex, int visited[], GRAPH *g, int stack[], int *index)
{
    visited[vertex] = TRUE;
    adjListNode *iter;
    for (iter = g->array[vertex].head; iter != NULL; iter = iter->next)
    {
        //printf("current node : %d\n", iter->data);
        if (visited[iter->data] == FALSE)
            topologicalSort(iter->data, visited, g, stack, index);
    }
    stack[(*index)++] = vertex;
}

GRAPH *createReverseGraph(GRAPH *g)
{
    GRAPH *g_reverese = Malloc(1, GRAPH);
    g_reverese->vertices = g->vertices;
    g_reverese->array = Malloc(g_reverese->vertices, adjList);
    int i;
    for (i = 0; i < g_reverese->vertices; i++)
        g_reverese->array[i].head = NULL;

    for (i = 0; i < g_reverese->vertices; i++)
    {
        adjListNode *iter;
        for (iter = g->array[i].head; iter != NULL; iter = iter->next)
        {
            addEdge(g_reverese, iter->data, i);
        }
    }
    return g_reverese;
}

void stronglyConnectedComponent(GRAPH *g)
{
    int *visited = Malloc(g->vertices, int);
    int *stack = Malloc(g->vertices, int);
    int i;
    int index = 0;
    for (i = 0; i < g->vertices; i++)
        visited[i] = FALSE;

    for (i = 0; i < g->vertices; i++)
        if (visited[i] == FALSE)
            topologicalSort(i, visited, g, stack, &index);

    /* get the transpose of the graph */
    GRAPH *g_reverse = createReverseGraph(g);
    for (i = 0; i < g->vertices; i++)
        visited[i] = FALSE;

    for (i = index - 1; i >= 0; i--)
    {
        if (visited[stack[i]] == FALSE)
        {
            dfs(stack[i], visited, g_reverse);
            printf("\n");
        }
    }
}

int main(int argc, char const *argv[])
{
    if (argc < 2)
        ERR_MESG("Number of vertices not given as input\n");

    GRAPH *g;
    int vertices = atoi(argv[1]);
    g = createGraph(vertices);
    // Test case 1
    /*
    addEdge(g, 1, 0);
    addEdge(g, 0, 2);
    addEdge(g, 2, 1);
    addEdge(g, 3, 2);
    addEdge(g, 2, 4);
    addEdge(g, 4, 3);
    addEdge(g, 3, 5);
    addEdge(g, 4, 6);
    addEdge(g, 5, 6);
    addEdge(g, 6, 7);
    addEdge(g, 7, 5);
    addEdge(g, 6, 8);
    addEdge(g, 8, 7);
    addEdge(g, 1, 9);
    addEdge(g, 4, 9);
    addEdge(g, 9, 14);
    addEdge(g, 8, 14);
    addEdge(g, 14, 15);
    addEdge(g, 15, 14);
    addEdge(g, 9, 10);
    addEdge(g, 9, 12);
    addEdge(g, 10, 11);
    addEdge(g, 11, 12);
    addEdge(g, 12, 10);
    addEdge(g, 12, 13);
    addEdge(g, 11, 13);
    addEdge(g, 14, 13);
    */

    // Test case 2
        
    addEdge(g, 0, 1);
    addEdge(g, 1, 2);
    addEdge(g, 1, 3);
    addEdge(g, 1, 4);
    addEdge(g, 4, 1);
    addEdge(g, 2, 5);
    addEdge(g, 5, 2);
    addEdge(g, 4, 5);
    addEdge(g, 4, 6);
    addEdge(g, 5, 7);
    addEdge(g, 6, 7);
    addEdge(g, 6, 9);
    addEdge(g, 9, 8);
    addEdge(g, 8, 6);
    addEdge(g, 7, 10);
    addEdge(g, 10, 11);
    addEdge(g, 11, 9);
    

    stronglyConnectedComponent(g);
    return 0;
}