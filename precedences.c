#include "precedences.h"
#include <stdio.h>
#include <stdlib.h>

void readPrecedenceRelations(Graph* graph, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier des relations de précédence");
        exit(EXIT_FAILURE);
    }

    int src, dest;
    while (fscanf(file, "%d %d", &src, &dest) == 2) {
        if (src >= 1 && src < MAX_OPERATIONS && dest >= 1 && dest < MAX_OPERATIONS) {
            addEdge(graph, src, dest);
        }
    }

    fclose(file);
}
