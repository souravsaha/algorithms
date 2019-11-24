#include "graph.h"

adjListNode *newNode(int nodeName)
{
    adjListNode *newNode = Malloc(1, adjListNode);
    newNode->data = nodeName;
    newNode->next = NULL;
    return newNode;
}

adjListNode *newNodeWithWeight(int nodeName, int weight)
{
    adjListNode *newNode = Malloc(1, adjListNode);
    newNode->data = nodeName;
    newNode->weight = weight;   
    newNode->next = NULL;
    return newNode;
}

GRAPH *createGraph(int vertices)
{
    GRAPH *g = Malloc(1, GRAPH);
    g->vertices = vertices;
    g->array = Malloc(g->vertices, adjList);
    int i;
    for (i = 0; i < g->vertices; i++)
        g->array[i].head = NULL;
    return g;
}

void addEdge(GRAPH *g, int source, int dest)
{
    assert(source < g->vertices || dest < g->vertices);
    adjListNode *node = newNode(dest);
    node->next = g->array[source].head;
    g->array[source].head = node;
}

void addEdgeWeight(GRAPH *g, int source, int dest, int weight)
{
    assert(source < g->vertices || dest < g->vertices);
    adjListNode *node = newNodeWithWeight(dest, weight);
    node->next = g->array[source].head;
    g->array[source].head = node;
}