#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

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
    if (TAB_MAX > 0){
        fusion_croiss_recur(tableau, 0, TAB_MAX - 1);
    }
}


void afficher(t_tab_chaine tab) {
    for (long i = 0; i < TAB_MAX; i++) {
        printf("%s\n",tab[i]);
    }
}

int main() {
    t_tab_chaine tab;
    srand( time( NULL ));
    remplir_tab(tab);
    fusion_croiss(tab);
    afficher(tab);
    printf("%d\n", TAB_MAX);
    return EXIT_SUCCESS;
}