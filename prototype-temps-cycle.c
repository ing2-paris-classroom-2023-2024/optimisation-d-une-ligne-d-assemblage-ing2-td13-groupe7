//
// Created by Louis Gion on 26/11/2023.
//

#include "prototype-temps-cycle.h"

#include <stdio.h>
#include <stdlib.h>

int* assignerStations(int operations[], int num_operations, int time_cycle) {
    int num_stations = (num_operations + time_cycle - 1) / time_cycle;
    int* station_assignments = (int*)malloc(num_operations * sizeof(int));

    // Distribution des opérations sur les stations
    for (int i = 0; i < num_operations; ++i) {
        station_assignments[i] = i % num_stations;
    }

    // Affichage des opérations assignées à chaque station
    for (int station = 0; station < num_stations; ++station) {
        printf("Station %d : ", station);

        for (int j = 0; j < num_operations; ++j) {
            if (station_assignments[j] == station) {
                printf("%d ", j);
            }
        }

        printf("\n");
    }

    return station_assignments;
}

/*
int main() {
    int num_operations = 10;
    int operations[] = {3, 5, 2, 7, 4, 6, 2, 8, 3, 4};
    int time_cycle = 3;

    int* station_assignments = assignerStations(operations, num_operations, time_cycle);

    // Libérer la mémoire allouée pour le tableau d'affectations de stations
    free(station_assignments);

    return 0;
}
*/