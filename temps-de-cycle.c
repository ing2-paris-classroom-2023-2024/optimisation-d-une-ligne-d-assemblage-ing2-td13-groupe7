//
// Created by Louis Gion on 26/11/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_OPS 100 // Nombre maximal d'opérations
#define MAX_STATIONS 100



void lireOperations(struct Operation operations[], int *nbOperations) {
    FILE *file = fopen("operations.txt", "r");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier operations.txt");
        exit(EXIT_FAILURE);
    }

    while (fscanf(file, "%d %f", &operations[*nbOperations].id, &operations[*nbOperations].temps) == 2) {
        (*nbOperations)++;
    }

    fclose(file);
}

float lireTempsCycle() {
    FILE *file = fopen("cycle.txt", "r");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier temps_cycle.txt");
        exit(EXIT_FAILURE);
    }

    float tempsCycle;
    if (fscanf(file, "%f", &tempsCycle) != 1) {
        printf("Erreur lors de la lecture du temps de cycle.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fclose(file);
    return tempsCycle;
}

void optimiserStations(struct Operation operations[], int nbOperations, struct Station stations[], int *nbStations, float tempsCycle) {
    for (int i = 0; i < nbOperations; i++) {
        if (*nbStations == 0 || stations[*nbStations - 1].tempsTotal + operations[i].temps > tempsCycle) {
            // Créer une nouvelle station si nécessaire
            stations[*nbStations].tempsTotal = operations[i].temps;
            stations[*nbStations].operations[0] = i;
            stations[*nbStations].nbOperations = 1;
            (*nbStations)++;
        } else {
            // Ajouter l'opération à la station actuelle
            int stationIndex = *nbStations - 1;
            stations[stationIndex].tempsTotal += operations[i].temps;
            stations[stationIndex].operations[stations[stationIndex].nbOperations] = i;
            stations[stationIndex].nbOperations++;
        }
    }
}

void afficherResultats(struct Station stations[], int nbStations, struct Operation operations[]) {
    printf("Répartition des opérations sur les stations :\n");
    for (int i = 0; i < nbStations; i++) {
        printf("Station %d (Temps total: %.2f): ", i + 1, stations[i].tempsTotal);
        for (int j = 0; j < stations[i].nbOperations; j++) {
            int opIndex = stations[i].operations[j];
            printf("%d (%.2f) ", operations[opIndex].id, operations[opIndex].temps);
        }
        printf("\n");
    }
}

int main() {
    struct Operation operations[MAX_OPS];
    int nbOperations = 0;
    lireOperations(operations, &nbOperations);

    float tempsCycle = lireTempsCycle();
    if (tempsCycle <= 0) {
        printf("Temps de cycle invalide.\n");
        return 1;
    }

    struct Station stations[MAX_STATIONS];
    memset(stations, 0, sizeof(stations)); // Initialisation des stations
    int nbStations = 0;
    optimiserStations(operations, nbOperations, stations, &nbStations, tempsCycle);

    afficherResultats(stations, nbStations, operations);
    return 0;
}