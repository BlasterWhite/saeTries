#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#define TABLE_MAX 500000 // pour 500000 on ne peut pas trier les 3 tableau dans le même programme donc on a fait avec 500000 en alléatoire puis 200000 en croissant et décroissant
typedef long int table[TABLE_MAX];

void debutMesuresPerf(clock_t t1, long *comparaison, long *permutation) {
    t1 = clock(); // Enregistre le premier temps
    *comparaison = 0; // initialise les comparaisons à 0
    *permutation = 0; // initialise les permutations à 0
}

void finMesuresPerf(clock_t t1, long comparaison, long permutation) {
    clock_t t2; // Crée la variable temps 2
    float temps; // Variable temps
    t2 = clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("        TRI PAR SHAKER        \n\n");
    printf("Temps CPU du tri : %3fs\n\n", temps);
    printf("Nombre de comparaisons : %ld\n\n", comparaison);
    printf("Nombre de Permutation : %ld\n\n", permutation);
}

void fusion(table tableau, int debutDeuxiemeMoitier, int finPremiereMoitier, int finDuTableau, long *comparaison, long *permutation) {
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
        *comparaison = *comparaison + 1; // Ajout d'une comparaison
        if (compt1 == debutPremiereMoitier) { // met que le tableau est trie 
            pasTrie = false;
        } else if (compt2 == (finDuTableau+1)) {
            tableau[i] = table1[compt1 - debutDeuxiemeMoitier]; // Si le compteur2 est arrivé a la fin du tableau trié 2 on met compteur1 valeur du tableau 1 a la suite du tableau final
            compt1++;
            *permutation = *permutation + 1; // Ajot d'une permutation 
        }else if (table1[compt1 - debutDeuxiemeMoitier] < tableau[compt2]){// Si la premiere valeur du tableau trie 1 et plus petite que la première valeur du tableau trie 2 alors on la met a l'indice i du tableau final
            tableau[i] = table1[compt1 - debutDeuxiemeMoitier];
            compt1++;
            *permutation = *permutation + 1; // Ajot d'une permutation 
        } else { // Si aucune des autre condition a marche c'est que la premiere valeur du tableau trie 2 et plus petite que la première valeur du tableau trie 1 donc on la met a l'indice i du tableau final
            tableau[i] = tableau[compt2];
            compt2++;
        }
        i++;
    }
}

void fusion_croiss_recur(table tableau, int debutTableau, int finTableau, long *comparaison, long *permutation){
    int milieu;
    if (debutTableau < finTableau){
        milieu = (finTableau + debutTableau) / 2;
        fusion_croiss_recur(tableau, debutTableau, milieu, &*comparaison, &*permutation);
        fusion_croiss_recur(tableau, milieu + 1, finTableau, &*comparaison, &*permutation);
        fusion(tableau, debutTableau, milieu, finTableau, &*comparaison, &*permutation);
        //affiche(tableau); // Pour comprendre les étapes
    }
}

void fusion_croiss(table tableau, long *comparaison, long *permutation){
    if (TABLE_MAX > 0){
        fusion_croiss_recur(tableau, 0, TABLE_MAX - 1, &*comparaison, &*permutation);
    }
}

void afficheTab(table tabAlea) {
    for (long i = 0; i < TABLE_MAX; i++) {
        printf("%ld\n", tabAlea[i]);
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
    table monTab;
    genere_Aleatoire(monTab);
    // tri :
    clock_t t1;
    t1 = 0;
    long nbComp, nbPerm;
    debutMesuresPerf(t1, &nbComp, &nbPerm);
    fusion_croiss(monTab, &nbComp, &nbPerm);
    finMesuresPerf(t1, nbComp, nbPerm);    
    // affichage :
    //afficheTab(monTab);
    return EXIT_SUCCESS;
}