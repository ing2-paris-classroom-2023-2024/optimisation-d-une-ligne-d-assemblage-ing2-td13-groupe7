//
// Created by Louis Gion on 26/11/2023.
//

#include "temps-de-cycle.h"
#include <stdio.h>
#include <limits.h>

#define MAX_STATIONS 100

// Fonction pour calculer le nombre optimal de stations et les affectations associées
int optimisationNombreStations(int operations[], int num_operations, int temps_de_cycle, int station_assignments[]) {
    int num_stations;
    int min_stations = INT_MAX;
    int temp_station_assignments[MAX_STATIONS];

    // Générer toutes les permutations possibles des opérations (à compléter)

    // Pour chaque permutation possible
    // (Note : Cela dépend de la manière dont les opérations sont stockées et triées)
    // Exemple : for each permutation in possible_permutations

    // Réinitialiser les variables
    int nombre_stations_actuel = 0;
    int temps_total_stations[MAX_STATIONS] = {0};

    // Distribuer les opérations selon la permutation actuelle
    for (int i = 0; i < num_operations; ++i) {
        // Trouver la station optimale pour l'opération i directement ici
        int station_optimale = 0;
        int temps_min = temps_total_stations[0] + operations[i];

        // Parcourir les stations pour trouver la station optimale
        for (int j = 1; j < MAX_STATIONS; ++j) {
            int temps_actuel = temps_total_stations[j] + operations[i];
            if (temps_actuel < temps_min && temps_actuel <= temps_de_cycle) {
                temps_min = temps_actuel;
                station_optimale = j;
            }
        }

        // Mettre à jour les variables
        temps_total_stations[station_optimale] += operations[i];
        nombre_stations_actuel = (nombre_stations_actuel > station_optimale) ? nombre_stations_actuel : (station_optimale + 1);

        // Enregistrer l'affectation
        temp_station_assignments[i] = station_optimale;
    }

    // Mettre à jour la meilleure solution si nécessaire
    if (nombre_stations_actuel < min_stations) {
        min_stations = nombre_stations_actuel;

        // Copier les affectations temporelles dans le tableau final
        for (int i = 0; i < num_operations; ++i) {
            station_assignments[i] = temp_station_assignments[i];
        }
    }
    // Fin de la boucle sur les permutations

    return min_stations;
}
