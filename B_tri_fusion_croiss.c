#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#define TABLE_MAX 200000 // pour 500000 on ne peut pas trier les 3 tableau dans le même programme donc on a fait avec 500000 en alléatoire puis 200000 en croissant et décroissant


typedef long int table[TABLE_MAX];

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

void fusion_croiss(table tableau,int n){
    if (n > 0){
        fusion_croiss_recur(tableau, 0, n - 1);
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
    fusion_croiss(Aleatoire,TABLE_MAX);
    fusion_croiss(Ascendant,TABLE_MAX);
    fusion_croiss(Descendant,TABLE_MAX);
    // affichage :
    afficheTab(Aleatoire, Ascendant, Descendant);
    
    
    return EXIT_SUCCESS;
}