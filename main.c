#include "graph.h"
#include "precedences.h"
#include "temps-de-cycle.h"
#include "exclusions.h"

int main() {
    Graph* graph = createGraph(MAX_OPERATIONS);


    readPrecedenceRelations(graph, "C:/Users/nicol/OneDrive/Bureau/precedences.txt");
    readOperationTimes(graph, "C:/Users/nicol/OneDrive/Bureau/operations.txt");
    readExclusionPairs(graph, "C:/Users/nicol/OneDrive/Bureau/exclusions.txt");
    float timeCycle = readTimeCycle("C:/Users/nicol/OneDrive/Bureau/temps_cycle.txt");


    bool visited[MAX_OPERATIONS] = {false};  // Initialisation du tableau visited
    bfs(graph, visited, timeCycle);         // Appel de la fonction bfs


    return 0;
}
