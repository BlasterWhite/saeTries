#include<stdlib.h>
#include<stdio.h>
#include <time.h>
#include<string.h>

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

void bulle_croiss (t_tab_chaine t) {
     int i = 0; // indice du nombre d"éléments déjà trié
     int trie = 0; // Dit si le trie est fini
     t_chaine temp; // variable temporaire pour l'echange de place
     while (trie == 0) {
         trie = 1;
         for (int a = 1; a < TAB_MAX-i; a++) {
             if (strcmp(t[a],t[a-1]) < 0) {
                 //printf("%d\n",a);
                 trie = 0; // Dit que le trie n'est pas terminé si il y a du changement
                 strcpy(temp,t[a]);
                 strcpy(t[a],t[a-1]);
                 strcpy(t[a-1],temp);
             }
         }
         i = i+1;
     }
}

int main() {
    t_tab_chaine t;
    remplir_tab(t);
    bulle_croiss(t);
    afficher(t);
    printf("%d\n", TAB_MAX);
    return EXIT_SUCCESS;
}