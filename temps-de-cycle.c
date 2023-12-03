#include "temps-de-cycle.h"
#include "Graph.h"
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

void bfs(Graph* graph) {
    int queue[MAX_OPERATIONS], front = 0, rear = -1;
    int currentStation = 1;
    int operationsPerStation[MAX_STATIONS][MAX_OPERATIONS] = {0};
    int operationCountPerStation[MAX_STATIONS] = {0};
    float timePerStation[MAX_STATIONS] = {0.0}; // Ajout de cette déclaration
    bool visited[MAX_OPERATIONS] = {false};

    // Initialisation de la file d'attente avec toutes les opérations sans prédécesseurs
    for (int i = 1; i < graph->V; i++) {
        if ((graph->applyPrecedenceConstraint && graph->inDegree[i] == 0) || !graph->applyPrecedenceConstraint) {
            if (graph->exists[i]) {
                queue[++rear] = i;
                visited[i] = true;
            }
        }
    }

    while (front <= rear) {
        int currentVertex = queue[front++];
        bool addedToStation = false;

        // Parcourir toutes les stations existantes pour trouver une station compatible
        for (int i = 1; i <= currentStation && !addedToStation; i++) {
            bool canBeAdded = true;

            // Vérification de la contrainte de temps
            if (graph->applyTimeConstraint && (timePerStation[i] + graph->operationTime[currentVertex] > graph->timeCycle)) {
                canBeAdded = false;
            }

            // Vérification de la contrainte d'exclusion
            if (graph->applyExclusionConstraint && canBeAdded) {
                for (int j = 0; j < operationCountPerStation[i]; j++) {
                    int op = operationsPerStation[i][j];
                    if (graph->exclusionMatrix[currentVertex][op]) {
                        canBeAdded = false;
                        break;
                    }
                }
            }

            if (canBeAdded) {
                operationsPerStation[i][operationCountPerStation[i]++] = currentVertex;
                timePerStation[i] += graph->operationTime[currentVertex];
                addedToStation = true;
            }
        }

        // Si l'opération n'a pas été ajoutée, créez une nouvelle station
        if (!addedToStation) {
            currentStation++;
            operationsPerStation[currentStation][0] = currentVertex;
            operationCountPerStation[currentStation] = 1;
            timePerStation[currentStation] = graph->operationTime[currentVertex];
        }

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
        printf("avec un temps total de %.2f secondes\n", timePerStation[i]);
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
