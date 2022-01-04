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

void permute(t_chaine t1, t_chaine t2, long *permutation) {
    *permutation = *permutation +1;
    t_chaine temp;
    strcpy(temp, t1);
    strcpy(t1,t2);
    strcpy(t2,temp);
}

void shaker_croiss (t_tab_chaine t,long *permutation, long *comparaison) {
    int i = 0; // indice du nombre d"éléments déjà trié
    int trie = 0; // Dit si le trie est fini
    while (trie == 0) {
        trie = 1;
        for (int a = i+1; a < TAB_MAX-i; a++) { // On fait monter le plus grands nombre du tableau
            *comparaison = *comparaison+1;
           if (strcmp(t[a],t[a-1]) < 0) {
                //printf("PERMUTE %d et %d\n", a, a-1);
                trie = 0; // Dit que le trie n'est pas terminé si il y a du changement
                permute(t[a],t[a-1],&*permutation);
            }
        }
        if (trie == 0) {
            for (int b = TAB_MAX-i-2; b >= i; b--) { // On fait descendre le plus petit nombre du tableau
                *comparaison = *comparaison +1;
                if (strcmp(t[b],t[b+1]) > 0) {
                    //printf("PERMUTE %d et %d\n", b, b+1);
                    trie = 0; // Dit que le trie n'est pas terminé si il y b du changement
                    permute(t[b],t[b+1],&*permutation);
                }
            }
        }
        i=i+1;
    }
}

void debutMesuresPerf(clock_t t1, long *comparaison, long *permutation) {
    t1 = clock();
    *comparaison = 0;
    *permutation = 0;
}

void finMesuresPerf(clock_t t1, long comparaison, long permutation) {
    clock_t t2;
    float temps;

    t2 = clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("        TRI PAR MACHIN        \n\n");
    printf("Temps CPU du tri : %3fs\n\n", temps);
    printf("Nombre de comparaisons : %ld\n\n", comparaison);
    printf("Nombre de Permutation : %ld\n\n", permutation);

}


int main() {
    clock_t t1;
    long nbComp, nbPerm;
    t_tab_chaine tab;
    remplir_tab(tab);
    t1 =0;
    debutMesuresPerf(t1, &nbComp, &nbPerm);
    shaker_croiss(tab,&nbPerm,&nbComp);
    finMesuresPerf(t1, nbComp, nbPerm);
    afficher(tab);
    return EXIT_SUCCESS;
}