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
        //printf("current node : %d\n", iter->data);
        if (visited[iter->data] == FALSE)
            dfs(iter->data, visited, g);
        //iter = iter->next;
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
    addEdge(g, 0, 1);
    addEdge(g, 1, 0);

    addEdge(g, 0, 3);
    addEdge(g, 3, 0);

    addEdge(g, 2, 3);
    addEdge(g, 3, 2);

    addEdge(g, 2, 1);
    addEdge(g, 1, 2);

    addEdge(g, 2, 4);
    addEdge(g, 4, 2);

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

    addEdge(g, 6, 10);
    addEdge(g, 10, 6);

    addEdge(g, 9, 12);
    addEdge(g, 12, 9);

    addEdge(g, 10, 11);
    addEdge(g, 11, 10);

    addEdge(g, 11, 12);
    addEdge(g, 12, 11);
    addEdge(g, 10, 12);
    addEdge(g, 12, 10);
    addEdge(g, 8, 13);
    addEdge(g, 13, 8);
    */

    // Test case 2 
    /*
    addEdge(g, 0, 1);
    addEdge(g, 0, 5);
    addEdge(g, 2, 3);
    addEdge(g, 1, 4);
    addEdge(g, 1, 5);
    addEdge(g, 3, 4);
    addEdge(g, 5, 4);
    addEdge(g, 2, 1);
    addEdge(g, 4, 0);
    */
    // Test case 3 
    /*
    addEdge(g, 0, 1);
    addEdge(g, 1, 0);

    addEdge(g, 0, 2);
    addEdge(g, 2, 0);
    
    addEdge(g, 1, 2);
    addEdge(g, 2, 1);
    
    addEdge(g, 1, 4);
    addEdge(g, 4, 1);
    
    addEdge(g, 0, 3);
    addEdge(g, 3, 0);
    
    addEdge(g, 4, 5);
    addEdge(g, 5, 4);
    
    addEdge(g, 2, 5);
    addEdge(g, 5, 2);
    
    addEdge(g, 3, 5);
    addEdge(g, 5, 3);
    
    addEdge(g, 5, 6);
    addEdge(g, 6, 5);
    
    addEdge(g, 4, 7);
    addEdge(g, 7, 4);
    
    addEdge(g, 6, 7);
    addEdge(g, 7, 6);
    */

    // Test case 4
    
    addEdge(g, 0, 1);
    addEdge(g, 0, 2);
    addEdge(g, 1, 4);
    addEdge(g, 0, 5);
    addEdge(g, 4, 5);
    addEdge(g, 5, 1);
    addEdge(g, 2, 3);
    addEdge(g, 3, 7);
    addEdge(g, 4, 6);
    addEdge(g, 7, 6);
    addEdge(g, 5, 6);
    addEdge(g, 4, 7);
    addEdge(g, 3, 0);
    

    int *visited = Malloc(vertices, int);
    int i;
    for (i = 0; i < vertices; i++)
        visited[i] = FALSE;
    dfs(6, visited, g);
    printf("\n");
    for (i = 0; i < vertices; i++)
    {
        if (visited[i] == FALSE)
            dfs(i, visited, g);
        
        printf("\n");
    }
    return 0;
}