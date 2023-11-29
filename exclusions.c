#include <stdio.h>
#include <stdlib.h>

#define MAX_OPERATIONS 100 // Nombre maximal d'opérations
#define MAX_COLORS 100 // Nombre maximal de couleurs

int exclusions[MAX_OPERATIONS][MAX_OPERATIONS]; // Matrice d'exclusions
int stations[MAX_OPERATIONS]; // Tableau pour stocker les stations attribuées à chaque opération
int nbOperations = 0; // Nombre d'opérations

// Fonction pour lire les exclusions à partir du fichier texte
void lireExclusions() {
    FILE *fichier = fopen("C:/Users/nicol/OneDrive/Bureau/exclusions.txt","r");
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.");
        return;
    }

    int operationA, operationB;
    while (fscanf(fichier, "%d %d", &operationA, &operationB) == 2) {
        exclusions[operationA][operationB] = 1;
        exclusions[operationB][operationA] = 1;
        nbOperations = operationA > nbOperations ? operationA : nbOperations;
        nbOperations = operationB > nbOperations ? operationB : nbOperations;
    }

    fclose(fichier);
}

// Fonction pour attribuer les stations aux opérations
int colorationGraphe() {
    int i, j, k;
    int couleur[MAX_OPERATIONS];

    // Initialisation des couleurs
    for (i = 0; i < MAX_COLORS; ++i) {
        couleur[i] = 0;
    }

    for (i = 1; i <= nbOperations; ++i) {
        stations[i] = -1; // Initialisation de la station à -1 pour indiquer qu'elle n'est pas attribuée
    }

    for (i = 1; i <= nbOperations; ++i) {
        int couleurDisponible[MAX_COLORS];
        for (j = 0; j < MAX_COLORS; ++j) {
            couleurDisponible[j] = 1;
        }

        for (j = 1; j <= nbOperations; ++j) {
            if (exclusions[i][j] && stations[j] != -1) {
                couleurDisponible[couleur[stations[j]]] = 0;
            }
        }

        for (k = 0; k < MAX_COLORS; ++k) {
            if (couleurDisponible[k]) {
                couleur[i] = k;
                break;
            }
        }

        if (stations[i] == -1) {
            stations[i] = couleur[i]; // Attribuer une station à l'opération basée sur la couleur
        }
    }

    // Recherche du nombre de couleurs utilisées, c'est-à-dire le nombre de stations
    int maxStations = 0;
    for (i = 1; i <= nbOperations; ++i) {
        if (couleur[i] > maxStations) {
            maxStations = couleur[i];
        }
    }

    // Affichage des opérations réparties dans chaque station
    for (i = 0; i <= maxStations; ++i) {
        printf("Station %d : ", i + 1);
        for (j = 1; j <= nbOperations; ++j) {
            if (stations[j] == i) {
                printf("%d ", j);
            }
        }
        printf("\n");
    }

    return maxStations + 1; // Ajouter 1 car les couleurs commencent à partir de 0
}

int main() {
    lireExclusions();
    int nbStations = colorationGraphe();
    printf("Le nombre minimum de stations necessaires est : %d\n", nbStations);

    return 0;
}
