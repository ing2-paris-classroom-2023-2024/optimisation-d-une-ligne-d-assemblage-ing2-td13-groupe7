#include <stdio.h>
#include <stdlib.h>

#define MAX_OPERATIONS 100 // Nombre maximal d'opérations

// Fonction pour lire les temps de chaque opération depuis un fichier texte
void lireTempsOperations(int tempsOperations[], int nbOperations) {
    FILE *fichier = fopen("chemin/vers/le/fichier_temps_operations.txt", "r");
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier des temps d'operations.\n");
        return; // Erreur de lecture du fichier
    }

    for (int i = 1; i <= nbOperations; ++i) {
        fscanf(fichier, "%d", &tempsOperations[i]);
    }

    fclose(fichier);
}

// Fonction pour lire le temps de cycle depuis un fichier texte
int lireTempsCycleMax() {
    int tempsMax = 0;
    FILE *fichier = fopen("chemin/vers/le/fichier_temps_cycle_max.txt", "r");
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier du temps de cycle max.\n");
        return -1; // Erreur de lecture du fichier
    }

    fscanf(fichier, "%d", &tempsMax);
    fclose(fichier);
    return tempsMax;
}

// Fonction pour calculer le temps total d'un cycle
int calculerTempsCycle(int tempsOperations[], int nbOperations, int tempsCycle) {
    int tempsTotal = 0;

    // Calcul du temps total en additionnant les temps de chaque opération
    for (int i = 1; i <= nbOperations; ++i) {
        tempsTotal += tempsOperations[i];
    }

    // Ajout du temps de cycle entre les opérations
    tempsTotal += (nbOperations - 1) * tempsCycle;

    return tempsTotal;
}

int main() {
    int tempsOperations[MAX_OPERATIONS]; // Tableau pour stocker les temps nécessaires pour chaque opération
    int nbOperations = 0; // Nombre d'opérations
    int tempsCycleMax = 0; // Temps de cycle maximal pour une station

    // ... (logique pour obtenir le nombre d'opérations, les temps de chaque opération et le temps de cycle maximal depuis les fichiers texte)

    lireTempsOperations(tempsOperations, nbOperations);
    tempsCycleMax = lireTempsCycleMax();

    int tempsTotalCycle = calculerTempsCycle(tempsOperations, nbOperations, tempsCycleMax);
    printf("Le temps total pour un cycle est : %d\n", tempsTotalCycle);

    return 0;
}
