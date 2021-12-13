#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 250000 // peut pas faire 500k sinon trop de mémoire

typedef long T_tab[MAX];

void afficheTab(T_tab tabAlea, T_tab tabAsc, T_tab tabDesc) {
    for (long i = 0; i < MAX; i++) {
        printf("%12ld | %12ld | %12ld \n",tabAlea[i], tabAsc[i], tabDesc[i]);
    }
}

void genere_Aleatoire(T_tab tab) {
    for (long i = 0; i < MAX; i++) {
        tab[i] = rand() % RAND_MAX;
    }
}

void genere_Ascendant(T_tab tab) {
    for (long i = 0; i < MAX; i++) {
        tab[i] = i;
    }
}

void genere_Descendant(T_tab tab) {
    for (long i = 0; i < MAX; i++) {
        tab[i] = MAX-i;
    }
}

int main(void) {
    T_tab Aleatoire, Ascendant, Descendant;
    genere_Aleatoire(Aleatoire);
    genere_Ascendant(Ascendant);
    genere_Descendant(Descendant);
    srand( time( NULL ));
    afficheTab(Aleatoire, Ascendant, Descendant);
    return EXIT_SUCCESS;
}