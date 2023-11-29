//
// Created by Louis Gion on 26/11/2023.
//



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_OPS 100 // Nombre maximal d'opérations
#define MAX_STATIONS 100

// Structure pour représenter une opération avec son temps d'exécution
struct Operation {
    char nom[10];
    int temps;
};

// Fonction pour lire les opérations et leurs temps d'exécution depuis operations.txt
void lireOperations(struct Operation operations[MAX_OPS]) {
    FILE* file = fopen("operations.txt", "r");
    int i = 0;
    while (fscanf(file, "%s %d", operations[i].nom, &operations[i].temps) == 2) {
        i++;
    }
    fclose(file);
}

// Fonction pour effectuer un BFS et calculer le temps de cycle
int calculerTempsCycle(struct Operation operations[MAX_OPS], int nbOperations, int limiteTempsCycle) {
    int tempsTotal = 0;

    for (int i = 0; i < nbOperations; i++) {
        tempsTotal += operations[i].temps;

        // Vérification du temps de cycle
        if (tempsTotal > limiteTempsCycle) {
            printf("Dépassement du temps de cycle!\n");
            return tempsTotal;
        }
    }

    return tempsTotal;
}

// Fonction pour lire le temps de cycle depuis le fichier temps_cycle.txt
int lireTempsCycle() {
    FILE* file = fopen("temps_cycle.txt", "r");
    int tempsCycle;

    if (file == NULL) {
        // Gestion de l'erreur si le fichier n'est pas ouvert correctement
        printf("Erreur lors de l'ouverture du fichier temps_cycle.txt\n");
        return -1; // Ou une autre valeur d'erreur que vous préférez
    }

    if (fscanf(file, "%d", &tempsCycle) != 1) {
        // Gestion de l'erreur si la lecture échoue
        printf("Erreur lors de la lecture du temps de cycle depuis le fichier.\n");
        tempsCycle = -1; // Ou une autre valeur d'erreur que vous préférez
    }

    fclose(file);
    return tempsCycle;
}

void genererPermutations(int operations[], int num_operations, int index, int station_assignments[], int temps_total_stations[], int temps_de_cycle, int* min_stations) {
    // (le reste du code de la fonction genererPermutations reste inchangé)
}

int optimisationNombreStations(int operations[], int num_operations, int temps_de_cycle, int station_assignments[]) {
    // (le reste du code de la fonction optimisationNombreStations reste inchangé)
}

int* assignerStations(int operations[], int num_operations, int temps_de_cycle) {
    // (le reste du code de la fonction assignerStations reste inchangé)
}

int main() {
    struct Operation operations[MAX_OPS];

    // Lecture des données
    int nbOperations = 0;
    lireOperations(operations);

    // Lecture du temps de cycle
    int limiteTempsCycle = lireTempsCycle();
    if (limiteTempsCycle == -1) {
        // Gestion de l'erreur
        return 1; // Ou une autre valeur d'erreur que vous préférez
    }

    // Calcul du temps de cycle
    int tempsCycle = calculerTempsCycle(operations, nbOperations, limiteTempsCycle);

    // Affichage du résultat
    if (tempsCycle <= limiteTempsCycle) {
        printf("Le temps de cycle respecte la limite (%d unités de temps).\n", tempsCycle);
    } else {
        printf("Le temps de cycle dépasse la limite (%d unités de temps).\n", tempsCycle);
    }

    // Assignation des stations
    int* station_assignments = assignerStations(operations, nbOperations, tempsCycle);

    // Libérer la mémoire allouée pour le tableau d'affectations de stations
    free(station_assignments);

    return 0;
}


