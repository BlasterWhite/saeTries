#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define N 10

typedef int tableau[N];

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
    printf("        TRI PAR TAS        \n\n");
    printf("Temps CPU du tri : %3fs\n\n", temps);
    printf("Nombre de comparaisons : %ld\n\n", comparaison);
    printf("Nombre de Permutation : %ld\n\n", permutation);
}

void permute(int *v1, int *v2) {
    int tmp;
    tmp = *v1;
    *v1 = *v2;
    *v2 = tmp;
}

void tamiser(tableau t, int noeud, int n, long *nbComp, long *nbPerm) {
    int fils;
    fils = 2*noeud + 1;
    *nbComp = *nbComp + 1;
    if (fils < n && t[fils+1] > t[fils]) {
        fils = fils + 1;
    }    
    *nbComp = *nbComp + 1;
    if (fils <= n && t[noeud] < t[fils]) {
        *nbPerm = *nbPerm + 1;
        permute(&t[noeud], &t[fils]);
        tamiser(t, fils, n,&*nbComp, &*nbPerm);
    }    
}

void triParTas(tableau t, long *nbComp, long *nbPerm) {
    for (int i = N/2-1; i >= 0; i--)
    {
        tamiser(t, i, N-1,&*nbComp, &*nbPerm);
    }
    for (int i = N-1; i >= 0; i--)
    {
        *nbPerm = *nbPerm + 1;
        permute(&t[0], &t[i]);
        tamiser(t,0,i-1,&*nbComp, &*nbPerm);
        //printf("COUCOU\n");
    }   
}

void afficheTab(tableau t) {
    for (int i = 0; i < N; i++)
    {
        printf("%d\n", t[i]);
    }
}

int main() {
    tableau tab = {10, 15, 5, 25, 35, 40, 50, 45, 20, 30};
    afficheTab(tab);
    clock_t t1;
    t1 = 0;
    long nbComp, nbPerm;
    debutMesuresPerf(t1, &nbComp, &nbPerm);
    triParTas(tab, &nbComp, &nbPerm);
    finMesuresPerf(t1, nbComp, nbPerm);
    printf("=======================================\n");
    afficheTab(tab);
    return EXIT_SUCCESS;
}
