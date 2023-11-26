//
// Created by mleon on 26/11/2023.
//

#include "contrainte_exclusion.h

int exclusionConstraint(int operations[NUM_OPERATIONS], int stations[NUM_STATIONS][NUM_OPERATIONS]) {
    for (int i = 0; i < NUM_OPERATIONS; i++) {
        for (int j = i + 1; j < NUM_OPERATIONS; j++) {
            for (int k = 0; k < NUM_STATIONS; k++) {
                if (stations[k][i] && stations[k][j]) {
                    printf("Les opérations %d et %d sont affectées à la même station %d", i, j, k);
                    return 0;
                }
            }
        }
    }
    printf("Aucune paire d'opérations exclues n'est affectée à la même station");
    return 1;
}
