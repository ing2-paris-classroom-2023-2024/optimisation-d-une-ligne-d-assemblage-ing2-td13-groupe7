#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_OPS 100 // Nombre maximal d'opérations
#define MAX_STATIONS 100
#include <limits.h>

///---------------------------------------------structures---------------------------------------------///
// Structure pour représenter une opération avec son temps d'exécution
struct Operation {
    char nom[10];
    int temps;
    int debut; // temps de debut dexecution
};
// Structure pour représenter un graphe orienté avec les dépendances entre les opérations
struct Graph {
    struct Operation operations[MAX_OPS];
    int dependances[MAX_OPS][MAX_OPS]; // Matrice d'adjacence
    int nbOperations;
};
// Structure pour représenter une station de travail
struct Station {
    int tempsTotal; // Temps total d'exécution sur la station
    int *operations; // Tableau des opérations attribuées à la station
    int nbOperations; // Nombre d'opérations attribuées à la station
};
///------------------------------------------------------------------------------------------///



///---------------------------------------------fichiers---------------------------------------------///
// Fonction pour lire les opérations et leurs temps d'exécution depuis operations.txt
void lireOperations(struct Operation operations[MAX_OPS]) {
    FILE* file = fopen("operations.txt", "r");
    int i = 0;
    while (fscanf(file, "%s %d", operations[i].nom, &operations[i].temps) == 2) {
        i++;
    }
    fclose(file);
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
//////------------------------------------------------------------------------------------------///


///---------------------------------------------BFS---------------------------------------------///
// Initialiser le graphe
void initialiserGraph(struct Graph* graph) {
    graph->nbOperations = 0;
    for (int i = 0; i < MAX_OPS; ++i) {
        graph->operations[i].temps = 0;
        graph->operations[i].debut = -1;
        for (int j = 0; j < MAX_OPS; ++j) {
            graph->dependances[i][j] = 0;
        }
    }
}
// Ajouter une opération au graphe
void ajouterOperation(struct Graph* graph, char nom[10], int temps) {
    if (graph->nbOperations < MAX_OPS) {
        strcpy(graph->operations[graph->nbOperations].nom, nom);
        graph->operations[graph->nbOperations].temps = temps;
        graph->nbOperations++;
    } else {
        printf("Nombre maximal d'opérations atteint.\n");
    }
}
// Ajouter une dépendance entre deux opérations
void ajouterDependance(struct Graph* graph, int opParent, int opEnfant) {
    if (opParent < MAX_OPS && opEnfant < MAX_OPS) {
        graph->dependances[opParent][opEnfant] = 1;
    } else {
        printf("Opération invalide.\n");
    }
}
// Appliquer l'algorithme BFS pour calculer le temps de cycle
int calculerTempsCycle(struct Graph* graph) {
    int tempsTotal = 0;

    // Initialiser le temps de début d'exécution à -1 pour toutes les opérations
    for (int i = 0; i < graph->nbOperations; ++i) {
        graph->operations[i].debut = -1;
    }

    // File pour le parcours BFS
    int file[MAX_OPS];
    int front = 0, rear = 0;

    // Parcourir toutes les opérations pour trouver celles sans dépendances
    for (int i = 0; i < graph->nbOperations; ++i) {
        int aDesDependances = 0;

        for (int j = 0; j < graph->nbOperations; ++j) {
            if (graph->dependances[j][i] == 1) {
                aDesDependances = 1;
                break;
            }
        }

        // Si l'opération n'a pas de dépendances, l'ajouter à la file
        if (!aDesDependances) {
            file[rear++] = i;
        }
    }

    // BFS
    while (front < rear) {
        int currentOp = file[front++];

        // Mettre à jour le temps de début d'exécution si nécessaire
        if (graph->operations[currentOp].debut == -1) {
            graph->operations[currentOp].debut = tempsTotal;
        }

        // Mettre à jour le temps total
        tempsTotal = graph->operations[currentOp].debut + graph->operations[currentOp].temps;

        // Ajouter les opérations suivantes à la file
        for (int i = 0; i < graph->nbOperations; ++i) {
            if (graph->dependances[currentOp][i] == 1) {
                // Mettre à jour le temps de début d'exécution si nécessaire
                if (graph->operations[i].debut == -1) {
                    graph->operations[i].debut = tempsTotal;
                }
                file[rear++] = i;
            }
        }
    }

    return tempsTotal;
}
///------------------------------------------------------------------------------------------///



///---------------------------------------------optimisation---------------------------------------------///
// Fonction pour distribuer les opérations sur un nombre optimal de stations
int optimiserNombreStations(struct Graph *graph, struct Station *stations, int *stationAssignments, int tempsCycle) {
    int numStations = 0;

// Triez les opérations par temps d'exécution décroissant
    for (int i = 0; i < graph->nbOperations - 1; ++i) {
        for (int j = 0; j < graph->nbOperations - i - 1; ++j) {
            if (graph->operations[j].temps < graph->operations[j + 1].temps) {
                // Échangez les opérations
                struct Operation temp = graph->operations[j];
                graph->operations[j] = graph->operations[j + 1];
                graph->operations[j + 1] = temp;
            }
        }
    }


    // Distribuez les opérations aux stations en utilisant le List Scheduling
    for (int i = 0; i < graph->nbOperations; ++i) {
        int minCompletionTime = INT_MAX;
        int bestStation = -1;

        // Trouvez la station avec le temps total d'exécution minimal
        for (int j = 0; j < numStations; ++j) {
            int completionTime = stations[j].tempsTotal + graph->operations[i].temps;
            if (completionTime < minCompletionTime) {
                minCompletionTime = completionTime;
                bestStation = j;
            }
        }

        // Si aucune station n'est trouvée, créez une nouvelle station
        if (bestStation == -1) {
            bestStation = numStations;
            ++numStations;
        }

        // Attribuez l'opération à la station
        stations[bestStation].tempsTotal += graph->operations[i].temps;
        stations[bestStation].operations[stations[bestStation].nbOperations++] = i;
        stationAssignments[i] = bestStation;
    }

    return numStations;
}
///------------------------------------------------------------------------------------------///

///---------------------------------------------affichage---------------------------------------------///
// Fonction pour afficher les résultats
void afficherResultats(struct Graph *graph, struct Station *stations, int *stationAssignments, int tempsTotal, int numStations) {
    printf("Temps total de cycle : %d\n", tempsTotal);

    for (int i = 0; i < graph->nbOperations; ++i) {
        printf("Opération %s attribuée à la station %d\n", graph->operations[i].nom, stationAssignments[i]);
    }

    printf("\nRépartition des opérations sur les stations :\n");

    for (int i = 0; i < numStations; ++i) {
        printf("Station %d : ", i);

        for (int j = 0; j < stations[i].nbOperations; ++j) {
            printf("%s ", graph->operations[stations[i].operations[j]].nom);
        }

        printf("\n");
    }
}
///------------------------------------------------------------------------------------------///

///---------------------------------------------memoire---------------------------------------------///
// Fonction pour libérer la mémoire allouée pour les structures de données dynamiques
void libererMemoire(struct Graph *graph, struct Station *stations, int *stationAssignments) {
    // Libérer la mémoire pour les opérations dans le graphe
    for (int i = 0; i < graph->nbOperations; ++i) {
        // Ajustez cela en fonction de la structure de données réelle que vous utilisez
        // par exemple, si vous utilisez malloc pour les noms, libérez-les ici
        // free(graph->operations[i].nom);
    }

    // Libérer la mémoire pour les structures de données graph, stations et stationAssignments
    free(graph);
    free(stations);
    free(stationAssignments);
}
///------------------------------------------------------------------------------------------///



///---------------------------------------------main_optimisation---------------------------------------------///
int main() {
    printf("oui");

    struct Graph *graph = malloc(sizeof(struct Graph));
    struct Station *stations = malloc(sizeof(struct Station) * MAX_STATIONS);
    int *stationAssignments = malloc(sizeof(int) * MAX_OPS);
    // ... (Initialisation des structures et autres préparations)

///---------------------------------------------structures---------------------------------------------///
// Structure pour représenter une opération avec son temps d'exécution
    struct Operation {
        char nom[10];
        int temps;
        int debut; // temps de debut dexecution
    };
// Structure pour représenter un graphe orienté avec les dépendances entre les opérations
    struct Graph {
        struct Operation operations[MAX_OPS];
        int dependances[MAX_OPS][MAX_OPS]; // Matrice d'adjacence
        int nbOperations;
    };
// Structure pour représenter une station de travail
    struct Station {
        int tempsTotal; // Temps total d'exécution sur la station
        int *operations; // Tableau des opérations attribuées à la station
        int nbOperations; // Nombre d'opérations attribuées à la station
    };
///------------------------------------------------------------------------------------------///

    // Lecture des opérations depuis operations.txt
    lireOperations(graph->operations);

    // Lecture du temps de cycle depuis temps_cycle.txt
    int tempsCycle = lireTempsCycle();

    // Calcul du temps de cycle et répartition des opérations sur les stations
    int tempsTotal = calculerTempsCycle(graph);
    int numStations = optimiserNombreStations(graph, stations, stationAssignments, tempsCycle);

    // Affichage des résultats
    afficherResultats(graph, stations, stationAssignments, tempsTotal, numStations);

    // Libération de la mémoire
    libererMemoire(graph, stations, stationAssignments);

    return 0;
}
///------------------------------------------------------------------------------------------///
