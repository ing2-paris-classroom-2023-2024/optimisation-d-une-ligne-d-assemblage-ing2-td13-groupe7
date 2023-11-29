//
// Created by nicol on 29/11/2023.
//

#include "precedences.h"


#include <stdio.h>
#include <stdlib.h>

#define MAX_OPERATIONS 100 // Nombre maximal d'opérations

int precedences[MAX_OPERATIONS][MAX_OPERATIONS]; // Matrice des dépendances
int nbOperations = 0; // Nombre d'opérations

// Fonction pour initialiser la matrice des dépendances
void initialiserMatrice() {
    for (int i = 0; i < MAX_OPERATIONS; ++i) {
        for (int j = 0; j < MAX_OPERATIONS; ++j) {
            precedences[i][j] = 0;
        }
    }
}

// Fonction pour lire les contraintes d'exclusion à partir du fichier texte
void lireContraintesExclusion() {
    FILE *fichier = fopen("C:/Users/nicol/OneDrive/Bureau/precedences.txt", "r");
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.");
        return;
    }

    int operationA, operationB;
    while (fscanf(fichier, "%d %d", &operationA, &operationB) == 2) {
        precedences[operationA - 1][operationB - 1] = 1; // Marquer l'opération A comme précédant l'opération B
        nbOperations = operationA > nbOperations ? operationA : nbOperations;
        nbOperations = operationB > nbOperations ? operationB : nbOperations;
    }

    fclose(fichier);
}

// Fonction pour afficher le graphe de précédence
void afficherGraphePrecedence() {
    printf("Graphe de precedence :\n");
    for (int i = 0; i < nbOperations; ++i) {
        printf("Operation %d : ", i + 1);
        for (int j = 0; j < nbOperations; ++j) {
            if (precedences[i][j]) {
                printf("%d -> %d   ", i + 1, j + 1); // Afficher la relation de précédence
            }
        }
        printf("\n");
    }
}

int main() {
    initialiserMatrice();
    lireContraintesExclusion();
    afficherGraphePrecedence();

    return 0;
}
