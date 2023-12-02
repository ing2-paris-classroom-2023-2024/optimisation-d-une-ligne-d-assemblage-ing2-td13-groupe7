//
// Created by Louis Gion on 26/11/2023.
//

#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TD13_GROUPE7_TEMPS_DE_CYCLE_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TD13_GROUPE7_TEMPS_DE_CYCLE_H

#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TD13_GROUPE7_TEMPS_DE_CYCLE_H

// TimeCycle.h
#ifndef TIME_CYCLE_H
#define TIME_CYCLE_H

#include "graph.h"

float readTimeCycle(const char* filename);
void bfs(Graph* graph, bool visited[], float timeCycle);
void readOperationTimes(Graph* graph, const char* filename);

#endif // TIME_CYCLE_H
