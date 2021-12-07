#include <stdlib.h>
#include <stdio.h>

#define MAX 10

typedef int table[MAX];

void shaker_croiss (table t) {
    int i = 0; // indice du nombre d"éléments déjà trié
    int trie = 0; // Dit si le trie est fini
    int temp; // variable temporaire pour l'echange de place
    while (trie == 0) {
        trie = 1;
        for (int a = i+1; a < MAX-i; a++) { // On fait monter le plus grands nombre du tableau
            if (t[a] < t[a-1]) {
                trie = 0;
                temp = t[a];
                t[a] = t[a-1];
                t[a-1] = temp;
            }
        }
        if (trie == 0) {
            for (int b = MAX-i-2; b >= i; b--) { // On fait descendre le plus petit nombre du tableau
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

void affiche(table t) {
    for (int i = 0; i < MAX; i++) {
        printf("%d ",t[i]);
    }
    printf("\n");
}


int main() {
    table tabloAleatoire = {55, 97, 45, 12, 3, 77, 29, 31, 82, 48}; // Liste de nombre aléatoire
    table tabloCroissant = {3, 12, 29, 31, 45, 48, 55, 77, 82, 97}; // Liste de nombre classé en ordre croissant
    table tabloDecroissant = {97, 82, 77, 55, 48, 45, 31, 29, 12, 3};// Liste de nombre classé en ordre decroissant
    printf("          TRI BULLES          \n\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("tableau avant tri : \n");
    affiche(tabloAleatoire);
    shaker_croiss(tabloAleatoire);
    printf("tableau après tri : \n");
    affiche(tabloAleatoire);
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("tableau avant tri : \n");
    affiche(tabloCroissant);
    shaker_croiss(tabloCroissant);
    printf("tableau après tri : \n");
    affiche(tabloCroissant);
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("tableau avant tri : \n");
    affiche(tabloDecroissant);
    shaker_croiss(tabloDecroissant);
    printf("tableau après tri : \n");
    affiche(tabloDecroissant);
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    return EXIT_SUCCESS;
}