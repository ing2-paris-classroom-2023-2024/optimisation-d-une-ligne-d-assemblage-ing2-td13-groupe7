#include "exclusions.h"
#include <stdio.h>
#include <stdlib.h>
void readExclusionPairs(Graph* graph, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier des paires d'exclusion");
        exit(EXIT_FAILURE);
    }

    int op1, op2;
    while (fscanf(file, "%d %d", &op1, &op2) == 2) {
        if (op1 >= 1 && op1 < MAX_OPERATIONS && op2 >= 1 && op2 < MAX_OPERATIONS) {
            graph->exclusionMatrix[op1][op2] = graph->exclusionMatrix[op2][op1] = true;
        }
    }

    fclose(file);
}