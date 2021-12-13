#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define TABLE_MAX 500000

typedef long int table[TABLE_MAX];

void shaker_croiss (table t, int n) {
    int i = 0; // indice du nombre d"éléments déjà trié
    long int trie = 0; // Dit si le trie est fini
    long int temp; // variable temporaire pour l'echange de place
    while (trie == 0) {
        trie = 1;
        for (int a = i+1; a < n-i; a++) { // On fait monter le plus grands nombre du tableau
            if (t[a] < t[a-1]) {
                trie = 0;
                temp = t[a];
                t[a] = t[a-1];
                t[a-1] = temp;
            }
        }
        if (trie == 0) {
            for (int b = n-i-2; b >= i; b--) { // On fait descendre le plus petit nombre du tableau
                if (t[b] > t[b+1]) { 
                    trie = 0;
                    temp = t[b];
                    t[b] = t[b+1];
                    t[b+1] = temp;
                }
            }
        }
        i=i+1;
    }
}

void affiche(table t,int n) {
    for (int i = 0; i < n; i++) {
        printf("%ld \n",t[i]);
    }
    printf("\n");
}

long int random()
{
    return (rand() /(10*RAND_MAX));
}


int main() {
    srand(time(NULL));
    table t;
    for (int i = 0; i < TABLE_MAX; i++)
    {
        t[i] = random();
    }
    // tri :
    shaker_croiss(t,TABLE_MAX);
    // affichage :
    affiche(t,TABLE_MAX);
    
    
    return EXIT_SUCCESS;
}