#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#define TABLE_MAX 200000 
typedef long int table[TABLE_MAX];

void debutMesuresPerf(clock_t t1, long *comparaison, long *permutation) {
    t1 = clock(); // Enregistre le premier temps
    *comparaison = 0; // initialise les comparaisons à 0
    *permutation = 0; // initialise les permutations à 0
}

void finMesuresPerf(clock_t t1, long comparaison, long permutation, char tri[]) {
    clock_t t2; // Crée la variable temps 2
    float temps; // Variable temps
    t2 = clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("        TRI %s CROISSANT        \n\n",tri);
    printf("Temps CPU du tri : %3fs\n\n", temps);
    printf("Nombre de comparaisons : %ld\n\n", comparaison);
    printf("Nombre de Permutation : %ld\n\n", permutation);
}



void bulle_croiss (table t, long *comparaison, long *permutation) {
    int i = 0; // indice du nombre d"éléments déjà trié
    int trie = 0; // Dit si le trie est fini
    int temp; // variable temporaire pour l'echange de place
    while (trie == 0) {
        trie = 1;
        for (int a = 1; a < TABLE_MAX-i; a++) {
            *comparaison = *comparaison + 1; // Ajout d'une comparaison
            if (t[a] < t[a-1]) {
                *permutation = *permutation + 1; // Ajot d'une permutation
                trie = 0;
                temp = t[a];
                t[a] = t[a-1];
                t[a-1] = temp;
            }
        }
        i = i+1;
    }
}



void shaker_croiss (table t, long *comparaison, long *permutation) {
    int i = 0; // indice du nombre d"elements deja trie
    long int trie = 0; // Dit si le trie est fini
    long int temp; // variable temporaire pour l'echange de place
    while (trie == 0) {
        trie = 1;
        for (int a = i+1; a < TABLE_MAX-i; a++) { // On fait monter le plus grands nombre du tableau
            *comparaison = *comparaison + 1; // Ajout d'une comparaison
            if (t[a] < t[a-1]) {
                *permutation = *permutation + 1; // Ajout d'une permutation
                trie = 0;
                temp = t[a];
                t[a] = t[a-1];
                t[a-1] = temp;
            }
        }
        if (trie == 0) {
            for (int b = TABLE_MAX-i-2; b >= i; b--) { // On fait descendre le plus petit nombre du tableau
                *comparaison = *comparaison + 1; // Ajout d'une comparaison
                if (t[b] > t[b+1]) {
                    *permutation = *permutation + 1; // Ajout d'une permutation 
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



void fusion_c(table tableau, int debutDeuxiemeMoitier, int finPremiereMoitier, int finDuTableau, long *comparaison, long *permutation) {
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
            *permutation = *permutation + 1; // Ajout d'une permutation 
        }else if (table1[compt1 - debutDeuxiemeMoitier] < tableau[compt2]){// Si la premiere valeur du tableau trie 1 et plus petite que la première valeur du tableau trie 2 alors on la met a l'indice i du tableau final
            tableau[i] = table1[compt1 - debutDeuxiemeMoitier];
            compt1++;
            *permutation = *permutation + 1; // Ajout d'une permutation 
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
        fusion_c(tableau, debutTableau, milieu, finTableau, &*comparaison, &*permutation);
        //affiche(tableau); // Pour comprendre les étapes
    }
}

void fusion_croiss(table tableau, long *comparaison, long *permutation){
    if (TABLE_MAX > 0){
        fusion_croiss_recur(tableau, 0, TABLE_MAX - 1, &*comparaison, &*permutation);
    }
}


void fusion_d(table tableau, int debutDeuxiemeMoitier, int finPremiereMoitier, int finDuTableau, long *comparaison, long *permutation) {
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
        }else if (table1[compt1 - debutDeuxiemeMoitier] > tableau[compt2]){// Si la premiere valeur du tableau trie 1 et plus petite que la première valeur du tableau trie 2 alors on la met a l'indice i du tableau final
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

void fusion_decroiss_recur(table tableau, int debutTableau, int finTableau, long *comparaison, long *permutation){
    int milieu;
    if (debutTableau < finTableau){
        milieu = (finTableau + debutTableau) / 2;
        fusion_decroiss_recur(tableau, debutTableau, milieu, &*comparaison, &*permutation);
        fusion_decroiss_recur(tableau, milieu + 1, finTableau, &*comparaison, &*permutation);
        fusion_d(tableau, debutTableau, milieu, finTableau, &*comparaison, &*permutation);
        //affiche(tableau); // Pour comprendre les étapes
    }
}

void fusion_decroiss(table tableau, long *comparaison, long *permutation){
    if (TABLE_MAX > 0){
        fusion_decroiss_recur(tableau, 0, TABLE_MAX - 1, &*comparaison, &*permutation);
    }
}


void afficheTab(table tabAlea) {
    for (long i = 0; i < TABLE_MAX; i++) {
        printf("%ld\n", tabAlea[i]);
    }
}

void remplirTable(table t)
{
    for (long i = 0; i < TABLE_MAX; i++) {
        t[i] = rand() % RAND_MAX;
    }
}

void favorable(table t, long *cp, long *pm)
{
    fusion_croiss(t,&*cp,&*pm);
}

void defavorable(table t, long *cp, long *pm)
{
    fusion_decroiss(t,&*cp,&*pm);
}


void copier (table dest,table source)
{
    for (int i = 0; i < TABLE_MAX; i++)
    {
        dest[i] = source[i];
    }
}

int main() {
    srand(time(NULL));
    table tab_base;
    table tab_tri;
    clock_t t1;
    t1 = 0;
    long nbComp, nbPerm;
    remplirTable(tab_base);

    /*********************************
     * aleatoire
     * ********************************/

    printf("\n----------------------------------------\naleatoire\n----------------------------------------\n ");
    // tri 1 :
    copier(tab_tri,tab_base);
    debutMesuresPerf(t1, &nbComp, &nbPerm);
    fusion_croiss(tab_tri, &nbComp, &nbPerm);
    finMesuresPerf(t1, nbComp, nbPerm,"FUSION"); 
    printf("\n");   


    // tri 2 :
    copier(tab_tri,tab_base);
    debutMesuresPerf(t1, &nbComp, &nbPerm);
    shaker_croiss(tab_tri, &nbComp, &nbPerm);
    finMesuresPerf(t1, nbComp, nbPerm,"SHAKER");    
    printf("\n");   


    // tri 3 :
    copier(tab_tri,tab_base);
    debutMesuresPerf(t1, &nbComp, &nbPerm);
    bulle_croiss(tab_tri, &nbComp, &nbPerm);
    finMesuresPerf(t1, nbComp, nbPerm,"BULLES");
    printf("\n");   


    /***********************************
     * favorable
     * ********************************/ 


    printf("\n----------------------------------------\nfavorable\n----------------------------------------\n ");
    favorable(tab_base,&nbComp, &nbPerm);
    // tri 1 :
    copier(tab_tri,tab_base);
    debutMesuresPerf(t1, &nbComp, &nbPerm);
    fusion_croiss(tab_tri, &nbComp, &nbPerm);
    finMesuresPerf(t1, nbComp, nbPerm,"FUSION");  
    printf("\n");   


    // tri 2 :
    copier(tab_tri,tab_base);
    debutMesuresPerf(t1, &nbComp, &nbPerm);
    shaker_croiss(tab_tri, &nbComp, &nbPerm);
    finMesuresPerf(t1, nbComp, nbPerm,"SHAKER"); 
    printf("\n");   


    // tri 3 :
    copier(tab_tri,tab_base);
    debutMesuresPerf(t1, &nbComp, &nbPerm);
    bulle_croiss(tab_tri, &nbComp, &nbPerm);
    finMesuresPerf(t1, nbComp, nbPerm,"BULLES");
    printf("\n");   


    /**************************************
     * defavorable
     * ************************************/  

    printf("\n----------------------------------------\ndefavorable\n----------------------------------------\n ");
    defavorable(tab_base,&nbComp, &nbPerm);
    // tri 1 :
    copier(tab_tri,tab_base);
    debutMesuresPerf(t1, &nbComp, &nbPerm);
    fusion_croiss(tab_tri, &nbComp, &nbPerm);
    finMesuresPerf(t1, nbComp, nbPerm,"FUSION"); 
    printf("\n");   

    // tri 2 :
    copier(tab_tri,tab_base);
    debutMesuresPerf(t1, &nbComp, &nbPerm);
    shaker_croiss(tab_tri, &nbComp, &nbPerm);
    finMesuresPerf(t1, nbComp, nbPerm,"SHAKER");  
    printf("\n");   


    // tri 3 :
    copier(tab_tri,tab_base);
    debutMesuresPerf(t1, &nbComp, &nbPerm);
    bulle_croiss(tab_tri, &nbComp, &nbPerm);
    finMesuresPerf(t1, nbComp, nbPerm,"BULLES");
    printf("\n");   

    return EXIT_SUCCESS;
}