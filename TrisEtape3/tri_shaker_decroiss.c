#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define TAB_MAX 150000
#define TAILLE_CHAINE 11

typedef char t_chaine[TAILLE_CHAINE];
typedef t_chaine t_tab_chaine[TAB_MAX];

char char_alea() {
    return (rand() % 26)+97; // Génération d'un nombre aléatoire de 97 à 122 (97+25 MAX) | pour le charactere ASCII
}

int nb_alea() {
    return (rand() % (TAILLE_CHAINE-5))+5; // Nombre aléatoire en 5 à 10 | Pour longueur du string
}

void remplir_tab(t_tab_chaine tab) {
    for (int i = 0; i < TAB_MAX; i++) {
        int alea = nb_alea(); // Longueur du String
        for (int j = 0; j < alea; j++) {
            tab[i][j] = char_alea(); // Génération du charactère ASCII
            if (j == alea-1) {
                tab[i][j+1] = '\0'; // Met des espaces pour la fin du String
            }            
        }
    }
}

void afficher(t_tab_chaine tab) {
    for (int i = 0; i < TAB_MAX; i++) {
        printf("%s\n",tab[i]);
    }
}

void permute(t_chaine t1, t_chaine t2) {
    //printf("PERMUTE\n");
    t_chaine temp;
    strcpy(temp, t1);
    strcpy(t1,t2);
    strcpy(t2,temp);
}

void shaker_decroiss (t_tab_chaine t) {
    int i = 0; // indice du nombre d"éléments déjà trié
    int trie = 0; // Dit si le trie est fini
    while (trie == 0) {
        trie = 1;
        for (int a = i+1; a < TAB_MAX-i; a++) { // On fait monter le plus grands nombre du tableau
           if (strcmp(t[a],t[a-1]) > 0) {
                trie = 0; // Dit que le trie n'est pas terminé si il y a du changement
                //printf("PERMUTE %d et %d\n", a, a-1);
                permute(t[a],t[a-1]);
            }
        }
        if (trie == 0) {
            for (int b = TAB_MAX-i-2; b >= i; b--) { // On fait descendre le plus petit nombre du tableau
                if (strcmp(t[b],t[b+1]) < 0) {
                    trie = 0; // Dit que le trie n'est pas terminé si il y b du changement
                    //printf("PERMUTE %d et %d\n", b, b-1);
                    permute(t[b],t[b+1]);
                }
            }
        }
        i=i+1;
    }
}

int main() {
    t_tab_chaine tab;
    srand( time( NULL ));
    remplir_tab(tab);
    //afficher(tab);
    shaker_decroiss(tab);
    afficher(tab);
    printf("%d\n", TAB_MAX);
    return EXIT_SUCCESS;
}