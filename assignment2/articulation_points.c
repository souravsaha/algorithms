#include <stdio.h>
#include "common.h"
#include "graph.c"

void findArticulationPoints(int vertex, int visited[], GRAPH *g, int discovery[], int low[], int parent[], int articulationPoint[], int *time)
{
    int childCount = 0;
    //printf("Here\n");
    visited[vertex] = TRUE; // mark the vertex as true
    (*time)++;
    discovery[vertex] = low[vertex] = (*time);
    adjListNode *iter;
    for (iter = g->array[vertex].head; iter != NULL; iter = iter->next)
    {
        int v = iter->data;
        //printf("in for loop\n");
        if (!visited[v]) 
        {
            childCount++;
            parent[v] = vertex;
            findArticulationPoints(v, visited, g, discovery, low, parent, articulationPoint, time);
            low[vertex] = MIN(low[vertex], low[v]);

            // if node u is root of DFS tree and has two or more children
            if(parent[vertex] == -1 && childCount > 1 )
            {
                //printf("articulation point %d\n", vertex);
                articulationPoint[vertex] = TRUE;
            }
            // if u is not root
            if(parent[vertex] != -1 && low[v] >= discovery[vertex])
            {
                //printf("articulation point %d\n", vertex);
                articulationPoint[vertex] = TRUE; 
            }
        }
        else if(v != parent[vertex])
            low[vertex] = MIN(low[vertex], discovery[v]);
    } 
}

int main(int argc, char const *argv[])
{
    if (argc < 2)
        ERR_MESG("Number of vertices not given as input\n");
    int i;
    int time = 0;
    GRAPH *g;
    int vertices = atoi(argv[1]);
    g = createGraph(vertices);

    // sample # test case 1
    /*
    addEdge(g, 0, 1);
    addEdge(g, 1, 0);
    addEdge(g, 1, 2);
    addEdge(g, 2, 1);
    addEdge(g, 2, 0);
    addEdge(g, 0, 2);
    addEdge(g, 1, 3);
    addEdge(g, 3, 1); 
    addEdge(g, 1, 4);
    addEdge(g, 4, 1);
    addEdge(g, 1, 6);
    addEdge(g, 6, 1);
    addEdge(g, 3, 5);
    addEdge(g, 5, 3);
    addEdge(g, 5, 4);
    addEdge(g, 4, 5);
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
    int *articulationPoint = Malloc(vertices, int);
    int *parent = Malloc(vertices, int);
    int *low = Malloc(vertices, int);
    
    for( i = 0; i < g->vertices; i++)
    {
        visited[i] = FALSE;
        articulationPoint[i] = FALSE;
        parent[i] = -1;
        low[i] = 0;
        discovery[i] = 0;
    }
    for (i = 0; i < vertices; i++)
        if (visited[i] == FALSE)
            findArticulationPoints(i, visited, g, discovery, low, parent, articulationPoint, &time);
    printf("Articulation point in the graph: \n");
    for(i = 0; i < vertices; i++)
    {
        if (articulationPoint[i] == TRUE)
            printf("%d \n", i);
        
    }
    free(visited);
    free(discovery);
    free(articulationPoint);
    free(parent);
    free(low);
    return 0;
}
