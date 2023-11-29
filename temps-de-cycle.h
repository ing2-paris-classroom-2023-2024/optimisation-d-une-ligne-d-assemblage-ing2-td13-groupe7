//
// Created by Louis Gion on 26/11/2023.
//

#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TD13_GROUPE7_TEMPS_DE_CYCLE_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TD13_GROUPE7_TEMPS_DE_CYCLE_H

#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TD13_GROUPE7_TEMPS_DE_CYCLE_H


void lireOperations(struct Operation operations[MAX_OPS]);
int calculerTempsCycle(struct Operation operations[MAX_OPS], int nbOperations, int limiteTempsCycle);
int lireTempsCycle();
void genererPermutations(int operations[], int num_operations, int index, int station_assignments[], int temps_total_stations[], int temps_de_cycle, int* min_stations);
int optimisationNombreStations(int operations[], int num_operations, int temps_de_cycle, int station_assignments[]);
int* assignerStations(int operations[], int num_operations, int time_cycle);
