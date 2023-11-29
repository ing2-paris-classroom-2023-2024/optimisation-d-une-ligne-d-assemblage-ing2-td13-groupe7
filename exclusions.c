#include <stdio.h>
#include <stdlib.h>

#define MAX_OPERATIONS 100 // Nombre maximal d'opérations
#define MAX_STATIONS 100 // Nombre maximal de stations

int exclusions[MAX_OPERATIONS][MAX_OPERATIONS]; // Matrice d'exclusions
int stations[MAX_OPERATIONS]; // Tableau pour stocker les stations attribuées à chaque opération
int nbOperations = 0; // Nombre d'opérations

// Fonction pour initialiser la matrice d'exclusions
void initialiserExclusions() {
    for (int i = 0; i < MAX_OPERATIONS; ++i) {
        for (int j = 0; j < MAX_OPERATIONS; ++j) {
            exclusions[i][j] = 0;
        }
    }
}

// Fonction pour lire les exclusions à partir du fichier texte
void lireExclusions() {
    FILE *fichier = fopen("C:/Users/nicol/OneDrive/Bureau/exclusions.txt","r");
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.");
        return;
    }

    int operationA, operationB;
    while (fscanf(fichier, "%d %d", &operationA, &operationB) == 2) {
        if (operationA > nbOperations) {
            nbOperations = operationA;
        }
        if (operationB > nbOperations) {
            nbOperations = operationB;
        }
        exclusions[operationA - 1][operationB - 1] = 1;
        exclusions[operationB - 1][operationA - 1] = 1;
    }

    fclose(fichier);
}

// Fonction pour attribuer les stations aux opérations en tenant compte des exclusions
int attribuerStations() {
    int nbStations = 0;

    for (int i = 0; i < nbOperations; ++i) {
        stations[i] = -1; // Initialisation de la station à -1 pour indiquer qu'elle n'est pas attribuée

        int stationDisponible[MAX_STATIONS];
        for (int j = 0; j < MAX_STATIONS; ++j) {
            stationDisponible[j] = 1;
        }

        for (int j = 0; j < nbOperations; ++j) {
            if (exclusions[i][j] && stations[j] != -1) {
                stationDisponible[stations[j]] = 0;
            }
        }

        for (int k = 0; k < MAX_STATIONS; ++k) {
            if (stationDisponible[k]) {
                stations[i] = k; // Attribuer une station à l'opération
                if (k >= nbStations) {
                    nbStations = k + 1; // Mettre à jour le nombre de stations utilisées
                }
                break;
            }
        }
    }

    return nbStations;
}

// Fonction pour afficher les opérations réparties dans chaque station
void afficherStations(int nbStations) {
    for (int i = 0; i < nbStations; ++i) {
        printf("Station %d : ", i + 1);
        for (int j = 0; j < nbOperations; ++j) {
            if (stations[j] == i) {
                printf("%d ", j + 1);
            }
        }
        printf("\n");
    }
}

int main() {
    initialiserExclusions();
    lireExclusions();

    int nbStations = attribuerStations();
    printf("Le nombre minimum de stations necessaires est : %d\n", nbStations);

    afficherStations(nbStations);

    return 0;
}
