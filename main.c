#include "Graph.h"
#include "precedences.h"
#include "temps-de-cycle.h"
#include "exclusions.h"
#include <stdio.h>

int main() {

        Graph* graph = createGraph(MAX_OPERATIONS);

        printf("Choisissez les contraintes a appliquer :\n");
        printf("1: Exclusion seulement\n");
        printf("2: Temps de cycle et precedence\n");
        printf("3: Toutes les contraintes\n");
        int choice;
        scanf("%d", &choice);

        graph->applyExclusionConstraint = (choice == 1 || choice == 3);
        graph->applyTimeConstraint = (choice == 2 || choice == 3);
        graph->applyPrecedenceConstraint = (choice == 2 || choice == 3);


        readPrecedenceRelations(graph, "C:/Users/nicol/OneDrive/Bureau/precedences.txt"); //utilisation du chemin d'acces car il y a moins de problèmes
    readOperationTimes(graph, "C:/Users/nicol/OneDrive/Bureau/operations.txt");
    readExclusionPairs(graph, "C:/Users/nicol/OneDrive/Bureau/exclusions.txt");
    graph->timeCycle = readTimeCycle("C:/Users/nicol/OneDrive/Bureau/temps_cycle.txt");


        bool visited[MAX_OPERATIONS] = {false};
        bfs(graph);       // Appel de la fonction bfs


    return 0;
}
