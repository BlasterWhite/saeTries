#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define TABLE_MAX 200000 // pour 500000 on ne peut pas trier les 3 tableau dans le même programme

typedef long int table[TABLE_MAX];

void bulle_croiss (table t, int n) {
    int i = 0; // indice du nombre d"éléments déjà trié
    int trie = 0; // Dit si le trie est fini
    int temp; // variable temporaire pour l'echange de place
    while (trie == 0) {
        trie = 1;
        for (int a = 1; a < n-i; a++) {
            if (t[a] < t[a-1]) {
                trie = 0;
                temp = t[a];
                t[a] = t[a-1];
                t[a-1] = temp;
            }
        }
        i = i+1;
    }
}

void afficheTab(table tabAlea, table tabAsc, table tabDesc) {
    for (long i = 0; i < TABLE_MAX; i++) {
        printf("%12ld | %12ld | %12ld \n",tabAlea[i], tabAsc[i], tabDesc[i]);
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
    table Aleatoire, Ascendant, Descendant;
    genere_Aleatoire(Aleatoire);
    genere_Ascendant(Ascendant);
    genere_Descendant(Descendant);
    // tri :
    bulle_croiss(Aleatoire,TABLE_MAX);
    bulle_croiss(Ascendant,TABLE_MAX);
    bulle_croiss(Descendant,TABLE_MAX);
    // affichage :
    afficheTab(Aleatoire, Ascendant, Descendant);
    
    
    return EXIT_SUCCESS;
}