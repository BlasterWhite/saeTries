#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void debutMesuresPerf(clock_t t1, long *comparaison, long *permutation) {
    t1 = clock(); // Enregistre le premier temps
    *comparaison = 0; // initialise les comparaisons à 0
    *permutation = 0; // initialise les permutations à 0
}

void finMesuresPerf(clock_t t1, long comparaison, long permutation) {
    clock_t t2; // Crée la variable temps 2
    float temps; // Variable temps

    t2 = clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("        TRI PAR MACHIN        \n\n");
    printf("Temps CPU du tri : %3fs\n\n", temps);
    printf("Nombre de comparaisons : %ld\n\n", comparaison);
    printf("Nombre de Permutation : %ld\n\n", permutation);

}

int main() {

    clock_t t1;
    t1 = 0;
    long nbComp, nbPerm;
    debutMesuresPerf(t1, &nbComp, &nbPerm);
    for (int i = 0; i < 5000; i++)
    {
        printf("%d\n", i);
        nbPerm++;
    }
    

    finMesuresPerf(t1, &nbComp, &nbPerm);
    return EXIT_SUCCESS;
}