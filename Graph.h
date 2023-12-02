//
// Created by nicol on 02/12/2023.
//

#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TD13_GROUPE7_GRAPH_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TD13_GROUPE7_GRAPH_H

#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TD13_GROUPE7_GRAPH_H
#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

#define MAX_OPERATIONS 36

typedef struct {
    bool adjMatrix[MAX_OPERATIONS][MAX_OPERATIONS];
    int inDegree[MAX_OPERATIONS];
    bool exists[MAX_OPERATIONS];
    float operationTime[MAX_OPERATIONS];
    bool exclusionMatrix[MAX_OPERATIONS][MAX_OPERATIONS];
    int V;
} Graph;

Graph* createGraph(int V);
void addEdge(Graph* graph, int src, int dest);

#endif // GRAPH_H
