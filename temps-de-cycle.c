#include "temps-de-cycle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STATIONS 100
float readTimeCycle(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier du temps de cycle");
        exit(EXIT_FAILURE);
    }

    float timeCycle;
    fscanf(file, "%f", &timeCycle);
    fclose(file);
    return timeCycle;
}

void bfs(Graph* graph, bool visited[], float timeCycle) {
    int queue[MAX_OPERATIONS], front = 0, rear = -1;
    int currentStation = 1;
    float currentTime = 0;
    int operationsPerStation[MAX_STATIONS][MAX_OPERATIONS] = {0};
    int operationCountPerStation[MAX_STATIONS] = {0};
    float timePerStation[MAX_STATIONS] = {0.0};

    // Initialisation de la file d'attente avec toutes les opérations sans prédécesseurs
    for (int i = 1; i < graph->V; i++) {
        if (graph->inDegree[i] == 0 && graph->exists[i]) {
            queue[++rear] = i;
            visited[i] = true;
        }
    }

    while (front <= rear) {
        int currentVertex = queue[front];

        // Vérifier si l'opération peut être ajoutée à la station actuelle
        bool canBeAdded = currentTime + graph->operationTime[currentVertex] <= timeCycle;
        for (int i = 1; i < MAX_OPERATIONS && canBeAdded; i++) {
            if (operationsPerStation[currentStation][i] && graph->exclusionMatrix[currentVertex][i]) {
                canBeAdded = false;
            }
        }

        if (canBeAdded) {
            currentTime += graph->operationTime[currentVertex];
            operationsPerStation[currentStation][operationCountPerStation[currentStation]++] = currentVertex;
            timePerStation[currentStation] += graph->operationTime[currentVertex];
            front++;
        } else {
            currentStation++;
            currentTime = 0;
            memset(operationsPerStation[currentStation], 0, sizeof(operationsPerStation[currentStation])); // Réinitialiser les opérations de la station
            continue;
        }

        printf("Operation %d a la station %d\n", currentVertex, currentStation);

        // Ajouter les opérations suivantes à la file d'attente
        for (int i = 1; i < graph->V; i++) {
            if (graph->adjMatrix[currentVertex][i] && !visited[i] && graph->exists[i]) {
                queue[++rear] = i;
                visited[i] = true;
            }
        }
    }

    // Affichage des stations et de leurs opérations
    for (int i = 1; i <= currentStation; i++) {
        printf("Station %d: ", i);
        for (int j = 0; j < operationCountPerStation[i]; j++) {
            printf("%d; ", operationsPerStation[i][j]);
        }
        printf(" avec un temps total de %.2f secondes\n", timePerStation[i]);
    }
}


void readOperationTimes(Graph* graph, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier des temps d'opération");
        exit(EXIT_FAILURE);
    }

    int operation;
    float time;
    while (fscanf(file, "%d %f", &operation, &time) == 2) {
        if (operation >= 1 && operation < MAX_OPERATIONS) {
            graph->operationTime[operation] = time;
        }
    }

    fclose(file);
}
