#ifndef GRAPH_H
#define GRAPH_H
#include <stdio.h>
#include "common.h"
#define TRUE 1
#define FALSE 0

typedef struct adjListNode
{
    int data;
    int weight;
    struct adjListNode *next;
}adjListNode;

typedef struct adjList
{
    struct adjListNode *head;
}adjList;

typedef struct edge
{
    int source, destination, weight;
} edge;

typedef struct graph
{
    int vertices;
    int edges;
    struct adjList* array;
    struct edge* edgeList;
}GRAPH;

extern adjListNode *newNode(int nodeName);
extern GRAPH *createGraph(int vertices);
extern void addEdge(GRAPH *g, int source, int dest);
extern void addEdgeWeight(GRAPH *g, int source, int dest, int weight);
//extern void displayGraph(GRAPH* g);


#endif