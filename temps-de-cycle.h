//
// Created by Louis Gion on 26/11/2023.
//

#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TD13_GROUPE7_TEMPS_DE_CYCLE_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TD13_GROUPE7_TEMPS_DE_CYCLE_H

#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TD13_GROUPE7_TEMPS_DE_CYCLE_H



// Structure pour représenter une opération avec son temps d'exécution
struct Operation {
    int id;
    float temps;
};

// Structure pour représenter une station de travail
struct Station {
    float tempsTotal; // Temps total d'exécution sur la station
    int operations[MAX_OPS]; // Tableau des indices des opérations attribuées à la station
    int nbOperations; // Nombre d'opérations attribuées à la station
};

void lireOperations(struct Operation operations[], int *nbOperations);
float lireTempsCycle();
void optimiserStations(struct Operation operations[], int nbOperations, struct Station stations[], int *nbStations, float tempsCycle);
void afficherResultats(struct Station stations[], int nbStations, struct Operation operations[]);

