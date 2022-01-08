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
    for (int i = 0; i < TABLE_MAX; i++) {
        scanf("%s", t[i]);
    }
}

void copieTab(t_tab_chaine taborigin, t_tab_chaine tabdest) {
    for (long i = 0; i < TABLE_MAX; i++) {
        strcpy(taborigin[i], tabdest[i]);
    }    
}

void afficher(t_tab_chaine tab) {
    for (long i = 0; i < TABLE_MAX; i++) {
        printf("%s\n",tab[i]);
    }
}

/***************************************************************************************
 *                                                                                     *
 *                                   TRI BULLES                                        *
 *                                                                                     *
 * ************************************************************************************/
void bulle_croiss (t_tab_chaine t) {
     int i = 0; // indice du nombre d"éléments déjà trié
     int trie = 0; // Dit si le trie est fini
     t_chaine temp; // variable temporaire pour l'echange de place
     while (trie == 0) {
         trie = 1;
         for (int a = 1; a < TABLE_MAX-i; a++) {
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

/***************************************************************************************
 *                                                                                     *
 *                                   TRI SHAKER                                        *
 *                                                                                     *
 * ************************************************************************************/
void shaker_croiss (t_tab_chaine t) {
    int i = 0; // indice du nombre d"éléments déjà trié
    int trie = 0; // Dit si le trie est fini
    while (trie == 0) {
        trie = 1;
        for (int a = i+1; a < TABLE_MAX-i; a++) { // On fait monter le plus grands nombre du tableau
           if (strcmp(t[a],t[a-1]) < 0) {
                //printf("PERMUTE %d et %d\n", a, a-1);
                trie = 0; // Dit que le trie n'est pas terminé si il y a du changement
                permute(t[a],t[a-1]);
            }
        }
        if (trie == 0) {
            for (int b = TABLE_MAX-i-2; b >= i; b--) { // On fait descendre le plus petit nombre du tableau
                if (strcmp(t[b],t[b+1]) > 0) {
                    //printf("PERMUTE %d et %d\n", b, b+1);
                    trie = 0; // Dit que le trie n'est pas terminé si il y b du changement
                    permute(t[b],t[b+1]);
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
void fusion(t_tab_chaine tableau, int debutDeuxiemeMoitier, int finPremiereMoitier, int finDuTableau) {
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
        if (compt1 == debutPremiereMoitier) { // met que le tableau est trie 
            pasTrie = false;
        } else if (compt2 == (finDuTableau+1)) {
            strcpy(tableau[i], table1[compt1 - debutDeuxiemeMoitier]); // Si le compteur2 est arrivé a la fin du tableau trié 2 on met compteur1 valeur du tableau 1 a la suite du tableau final
            compt1++;
        }else if (strcmp(table1[compt1 - debutDeuxiemeMoitier],tableau[compt2]) < 0 ){
            strcpy(tableau[i], table1[compt1 - debutDeuxiemeMoitier]);// Si la premiere valeur du tableau trie 1 et plus petite que la première valeur du tableau trie 2 alors on la met a l'indice i du tableau final
            compt1++;
        } else { // Si aucune des autre condition a marche c'est que la premiere valeur du tableau trie 2 et plus petite que la première valeur du tableau trie 1 donc on la met a l'indice i du tableau final
            strcpy(tableau[i], tableau[compt2]);
            compt2++;
        }
        i++;
    }
}

void fusion_croiss_recur(t_tab_chaine tableau, int debutTableau, int finTableau){
    int milieu;
    if (debutTableau < finTableau){
        milieu = (finTableau + debutTableau) / 2;
        fusion_croiss_recur(tableau, debutTableau, milieu);
        fusion_croiss_recur(tableau, milieu + 1, finTableau);
        fusion(tableau, debutTableau, milieu, finTableau);
        //affiche(tableau); // Pour comprendre les étapes
    }
}

void fusion_croiss(t_tab_chaine tableau){
    if (TABLE_MAX > 0){
        fusion_croiss_recur(tableau, 0, TABLE_MAX - 1);
    }
}

int main() {
    t_tab_chaine tabOrigin, tabTri;
    remplirTable(tabOrigin);
    copieTab(tabOrigin, tabTri);

    return EXIT_SUCCESS;
}