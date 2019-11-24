#include <stdio.h>
#include "common.h"
#include "graph.c"
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
void displayStack(int *stack, int index)
{
    int i;
    for(i = index-1; i >= 0 ; i--)
        printf("%d ", stack[i]);
    printf("\n");
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
    addEdge(g, 5, 2);
    addEdge(g, 5, 0);
    addEdge(g, 4, 0);
    addEdge(g, 4, 1);
    addEdge(g, 2, 3);
    addEdge(g, 3, 1);
    */
    // Test case 2
    /*
    addEdge(g, 0, 2);
    addEdge(g, 1, 0);
    addEdge(g, 1, 3);
    addEdge(g, 3, 2);
    addEdge(g, 2, 4);
    addEdge(g, 2, 5);
    */
    // Test case 3
    
    addEdge(g, 0, 3);
    addEdge(g, 1, 3);
    addEdge(g, 1, 4);
    addEdge(g, 2, 4);
    addEdge(g, 3, 5);
    addEdge(g, 4, 6);
    addEdge(g, 3, 6);
    addEdge(g, 3, 7);
    addEdge(g, 2, 7);
    

    int *visited = Malloc(vertices, int);
    int *stack = Malloc(vertices, int);
    int i; 
    int index = 0;
    for (i = 0; i < vertices; i++)
        visited[i] = FALSE;

    for (i = 0; i < vertices; i++)
        if (visited[i] == FALSE)
            topologicalSort(i, visited, g, stack, &index);
    displayStack(stack, index);
    printf("\n");

    return 0;
}
