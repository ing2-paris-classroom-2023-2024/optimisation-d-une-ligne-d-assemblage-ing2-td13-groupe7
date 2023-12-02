//
// Created by nicol on 02/12/2023.
//
#include "graph.h"
#include <stdlib.h>

Graph* createGraph(int V) {
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    graph->V = V;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            graph->adjMatrix[i][j] = false;
        }
        graph->inDegree[i] = 0;
        graph->exists[i] = false;
        graph->operationTime[i] = 0; // Initialiser les temps à 0
    }
    return graph;
}
void addEdge(Graph* graph, int src, int dest) {
    graph->adjMatrix[src][dest] = true;
    graph->inDegree[dest]++;
    graph->exists[src] = graph->exists[dest] = true;
}