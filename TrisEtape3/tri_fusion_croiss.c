#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX 10

typedef int table[MAX];

void affiche(table tableau);

void fusion(table tableau, int debutDeuxiemeMoitier, int finPremiereMoitier, int finDuTableau) {
    int table1[finPremiereMoitier - debutDeuxiemeMoitier+1];
    int debutPremiereMoitier = finPremiereMoitier+1;
    int compt1 = debutDeuxiemeMoitier;
    int compt2 = debutPremiereMoitier;
    int i;
    bool pasTrie = true;
    for(i = debutDeuxiemeMoitier; i <= finPremiereMoitier; i++){
        table1[i - debutDeuxiemeMoitier] = tableau[i];
    }
    i = debutDeuxiemeMoitier;
    while ((i <= finDuTableau) && pasTrie){
        if (compt1 == debutPremiereMoitier) { // met que le tableau est trie 
            pasTrie = false;
        } else if (compt2 == (finDuTableau+1)) {
            tableau[i] = table1[compt1 - debutDeuxiemeMoitier]; // Si le compteur2 est arrivé a la fin du tableau trié 2 on met compteur1 valeur du tableau 1 a la suite du tableau final
            compt1++;
        }else if (table1[compt1 - debutDeuxiemeMoitier] < tableau[compt2]){// Si la premiere valeur du tableau trie 1 et plus petite que la première valeur du tableau trie 2 alors on la met a l'indice i du tableau final
            tableau[i] = table1[compt1 - debutDeuxiemeMoitier];
            compt1++;
        } else { // Si aucune des autre condition a marche c'est que la premiere valeur du tableau trie 2 et plus petite que la première valeur du tableau trie 1 donc on la met a l'indice i du tableau final
            tableau[i] = tableau[compt2];
            compt2++;
        }
        i++;
    }
}

void fusion_croiss_recur(table tableau, int debutTableau, int finTableau){
    int milieu;
    if (debutTableau < finTableau){
        milieu = (finTableau + debutTableau) / 2;
        fusion_croiss_recur(tableau, debutTableau, milieu);
        fusion_croiss_recur(tableau, milieu + 1, finTableau);
        fusion(tableau, debutTableau, milieu, finTableau);
        //affiche(tableau); // Pour comprendre les étapes
    }
}

void fusion_croiss(table tableau){
    if (MAX > 0){
        fusion_croiss_recur(tableau, 0, MAX - 1);
    }
}


void affiche(table tableau) {
    for (int i = 0; i < MAX; i++) {
        printf("%d ",tableau[i]);
    }
    printf("\n");
}

int main() {
    table tabloAleatoire = {55, 97, 45, 12, 3, 77, 29, 31, 82, 48}; // Liste de nombre aléatoire
    table tabloCroissant = {3, 12, 29, 31, 45, 48, 55, 77, 82, 97}; // Liste de nombre classé en ordre croissant
    table tabloDecroissant = {97, 82, 77, 55, 48, 45, 31, 29, 12, 3};// Liste de nombre classé en ordre decroissant
    printf("          TRI FUSION          \n\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("tableau avant tri : \n");
    affiche(tabloAleatoire);
    fusion_croiss(tabloAleatoire);
    printf("tableau après tri : \n");
    affiche(tabloAleatoire);
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("tableau avant tri : \n");
    affiche(tabloCroissant);
    fusion_croiss(tabloCroissant);
    printf("tableau après tri : \n");
    affiche(tabloCroissant);
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("tableau avant tri : \n");
    affiche(tabloDecroissant);
    fusion_croiss(tabloDecroissant);
    printf("tableau après tri : \n");
    affiche(tabloDecroissant);
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    return EXIT_SUCCESS;
}