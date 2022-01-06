#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define TABLE_MAX 50000 // pour 500000 on ne peut pas trier les 3 tableau dans le même programme donc on a fait avec 500000 en alléatoire puis 200000 en croissant et décroissant
typedef long int table[TABLE_MAX];

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
    printf("        TRI PAR BULLES        \n\n");
    printf("Temps CPU du tri : %3fs\n\n", temps);
    printf("Nombre de comparaisons : %ld\n\n", comparaison);
    printf("Nombre de Permutation : %ld\n\n", permutation);
}


void bulle_croiss (table t, int n, long *comparaison, long *permutation) {
    int i = 0; // indice du nombre d"éléments déjà trié
    int trie = 0; // Dit si le trie est fini
    int temp; // variable temporaire pour l'echange de place
    while (trie == 0) {
        trie = 1;
        for (int a = 1; a < n-i; a++) {
            *comparaison = *comparaison + 1; // Ajout d'une comparaison
            if (t[a] < t[a-1]) {
                *permutation = *permutation + 1; // Ajot d'une permutation
                trie = 0;
                temp = t[a];
                t[a] = t[a-1];
                t[a-1] = temp;
            }
        }
        i = i+1;
    }
}

void afficheTab(table tabAlea) {
    for (long i = 0; i < TABLE_MAX; i++) {
        printf("%ld\n", tabAlea[i]);
    }
    
}

void genere_Aleatoire(table tab) {
    for (long i = 0; i < TABLE_MAX; i++) {
        tab[i] = rand() % RAND_MAX;
    }
}

void genere_Ascendant(table tab) {
    for (long i = 1; i <= TABLE_MAX; i++) {
        tab[i-1] = i;
    }
}

void genere_Descendant(table tab) {
    for (long i = 0; i < TABLE_MAX; i++) {
        tab[i] = TABLE_MAX-i;
    }
}



int main() {
    srand(time(NULL));
    table monTab;
    genere_Aleatoire(monTab);
    // tri :
    clock_t t1;
    t1 = 0;
    long nbComp, nbPerm;
    debutMesuresPerf(t1, &nbComp, &nbPerm);
    bulle_croiss(monTab,TABLE_MAX, &nbComp, &nbPerm);
    finMesuresPerf(t1, nbComp, nbPerm);    
    // affichage :
    //afficheTab(monTab);
    
    return EXIT_SUCCESS;
}