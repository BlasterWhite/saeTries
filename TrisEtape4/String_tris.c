#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#define TABLE_MAX 150000
#define TAILLE_CHAINE 11

typedef char t_chaine[TAILLE_CHAINE];
typedef t_chaine t_tab_chaine[TABLE_MAX];

void remplirTable(t_tab_chaine t) {
    for (long i = 0; i < TABLE_MAX; i++) {
        scanf("%s", t[i]);
        //printf("String N°%ld\n",i);
    }
}

void copier (t_tab_chaine dest,t_tab_chaine source) {
    for (int i = 0; i < TABLE_MAX; i++) {
        strcpy(dest[i], source[i]);
    }
}

void afficher(t_tab_chaine tab) {
    for (long i = 0; i < TABLE_MAX; i++) {
        printf("%s\n",tab[i]);
    }
}

void debutMesuresPerf(clock_t *t1, long *comparaison, long *permutation) {
    *t1 = clock(); // Enregistre le premier temps
    *comparaison = 0; // initialise les comparaisons à 0
    *permutation = 0; // initialise les permutations à 0
}

void finMesuresPerf(clock_t t1, long comparaison, long permutation, char nom[]) {
    clock_t t2; // Crée la variable temps 2
    float temps; // Variable temps
    t2 = clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("        TRI %s CROISSANT        \n\n", nom);
    printf("Temps CPU du tri : %3fs\n\n", temps);
    printf("Nombre de comparaisons : %ld\n\n", comparaison);
    printf("Nombre de Permutation : %ld\n\n", permutation);
}

/***************************************************************************************
 *                                                                                     *
 *                                   TRI BULLES                                        *
 *                                                                                     *
 * ************************************************************************************/
void bulle_croiss (t_tab_chaine t, long *comparaison, long *permutation) {
     int i = 0; // indice du nombre d"éléments déjà trié
     int trie = 0; // Dit si le trie est fini
     t_chaine temp; // variable temporaire pour l'echange de place
     while (trie == 0) {
         trie = 1;
         for (int a = 1; a < TABLE_MAX-i; a++) {
             *comparaison = *comparaison + 1;
             if (strcmp(t[a],t[a-1]) < 0) {
                 //printf("%d\n",a);
                 trie = 0; // Dit que le trie n'est pas terminé si il y a du changement
                 *permutation = *permutation + 1; // Ajout d'une comparaison
                 strcpy(temp,t[a]);
                 strcpy(t[a],t[a-1]);
                 strcpy(t[a-1],temp);
             }
         }
         i = i+1;
     }
}

/***************************************************************************************
 *                                                                                     *
 *                                   TRI SHAKER                                        *
 *                                                                                     *
 * ************************************************************************************/
void permute(t_chaine t1, t_chaine t2) {
    t_chaine temp;
    strcpy(temp, t1);
    strcpy(t1,t2);
    strcpy(t2,temp);
}

void shaker_croiss (t_tab_chaine t, long *comparaison, long *permutation) {
    int i = 0; // indice du nombre d"éléments déjà trié
    int trie = 0; // Dit si le trie est fini
    while (trie == 0) {
        trie = 1;
        for (int a = i+1; a < TABLE_MAX-i; a++) { // On fait monter le plus grands nombre du tableau
           *comparaison = *comparaison + 1; // Ajout d'une comparaison
           if (strcmp(t[a],t[a-1]) < 0) {
                //printf("PERMUTE %d et %d\n", a, a-1);
                trie = 0; // Dit que le trie n'est pas terminé si il y a du changement
                permute(t[a],t[a-1]);
                *permutation = *permutation + 1; // Ajout d'une permutation 
            }
        }
        if (trie == 0) {
            for (int b = TABLE_MAX-i-2; b >= i; b--) { // On fait descendre le plus petit nombre du tableau
                *comparaison = *comparaison + 1; // Ajout d'une comparaison
                if (strcmp(t[b],t[b+1]) > 0) {
                    //printf("PERMUTE %d et %d\n", b, b+1);
                    trie = 0; // Dit que le trie n'est pas terminé si il y b du changement
                    permute(t[b],t[b+1]);
                    *permutation = *permutation + 1; // Ajout d'une permutation 
                }
            }
        }
        i=i+1;
    }
}

/***************************************************************************************
 *                                                                                     *
 *                                   TRI FUSION                                        *
 *                                                                                     *
 * ************************************************************************************/
void fusion(t_tab_chaine tableau, int debutDeuxiemeMoitier, int finPremiereMoitier, int finDuTableau, long *comparaison, long *permutation) {
    t_tab_chaine table1;
    int debutPremiereMoitier = finPremiereMoitier+1;
    int compt1 = debutDeuxiemeMoitier;
    int compt2 = debutPremiereMoitier;
    int i;
    bool pasTrie = true;
    for(i = debutDeuxiemeMoitier; i <= finPremiereMoitier; i++){
        strcpy(table1[i - debutDeuxiemeMoitier], tableau[i]);
    }
    i = debutDeuxiemeMoitier;
    while ((i <= finDuTableau) && pasTrie){
        *comparaison = *comparaison + 1; // Ajout d'une comparaison
        if (compt1 == debutPremiereMoitier) { // met que le tableau est trie 
            pasTrie = false;
        } else if (compt2 == (finDuTableau+1)) {
            strcpy(tableau[i], table1[compt1 - debutDeuxiemeMoitier]); // Si le compteur2 est arrivé a la fin du tableau trié 2 on met compteur1 valeur du tableau 1 a la suite du tableau final
            compt1++;
            *permutation = *permutation + 1; // Ajout d'une permutation 
        }else if (strcmp(table1[compt1 - debutDeuxiemeMoitier],tableau[compt2]) < 0 ){
            strcpy(tableau[i], table1[compt1 - debutDeuxiemeMoitier]);// Si la premiere valeur du tableau trie 1 et plus petite que la première valeur du tableau trie 2 alors on la met a l'indice i du tableau final
            compt1++;
            *permutation = *permutation + 1; // Ajout d'une permutation 
        } else { // Si aucune des autre condition a marche c'est que la premiere valeur du tableau trie 2 et plus petite que la première valeur du tableau trie 1 donc on la met a l'indice i du tableau final
            strcpy(tableau[i], tableau[compt2]);
            compt2++;
        }
        i++;
    }
}

void fusion_croiss_recur(t_tab_chaine tableau, int debutTableau, int finTableau, long *comparaison, long *permutation){
    int milieu;
    if (debutTableau < finTableau){
        milieu = (finTableau + debutTableau) / 2;
        fusion_croiss_recur(tableau, debutTableau, milieu, &*comparaison, &*permutation);
        fusion_croiss_recur(tableau, milieu + 1, finTableau, &*comparaison, &*permutation);
        fusion(tableau, debutTableau, milieu, finTableau, &*comparaison, &*permutation);
        //affiche(tableau); // Pour comprendre les étapes
    }
}

void fusion_croiss(t_tab_chaine tableau, long *comparaison, long *permutation){
    if (TABLE_MAX > 0){
        fusion_croiss_recur(tableau, 0, TABLE_MAX - 1, &*comparaison, &*permutation);
    }
}

int main() {
    t_tab_chaine tabOrigin, tabTri;
    //printf("Remplissage du Tableau en cours");
    remplirTable(tabOrigin);
    //printf("Copie du Tableau en cours");
    copier(tabTri, tabOrigin);
    //afficher(tabOrigin);
    clock_t t1;
    long nbComp, nbPerm;

    t1 = 0;
    debutMesuresPerf(&t1, &nbComp, &nbPerm);
    bulle_croiss(tabTri, &nbComp, &nbPerm);
    finMesuresPerf(t1, nbComp, nbPerm, "BULLES");

    copier(tabTri, tabOrigin);
    debutMesuresPerf(&t1, &nbComp, &nbPerm);
    shaker_croiss(tabTri, &nbComp, &nbPerm);
    finMesuresPerf(t1, nbComp, nbPerm, "SHAKER");

    copier(tabTri, tabOrigin);
    debutMesuresPerf(&t1, &nbComp, &nbPerm);
    fusion_croiss(tabTri, &nbComp, &nbPerm);
    finMesuresPerf(t1, nbComp, nbPerm, "FUSION");
    //afficher(tabTri);
    return EXIT_SUCCESS;
}
