#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define int MAX 17776

typedef struct{
    int dep;
    char date[10];
    int pos;
    int classe;
    int pop;
}donnees_covid;

typedef donnees_covid t_covid[MAX];


void fusion_c(t_covid tableau, int debutDeuxiemeMoitier, int finPremiereMoitier, int finDuTableau, long *comparaison, long *permutation) {
    t_covid table1[finPremiereMoitier - debutDeuxiemeMoitier+1];
    int debutPremiereMoitier = finPremiereMoitier+1;
    int compt1 = debutDeuxiemeMoitier;
    int compt2 = debutPremiereMoitier;
    int i;
    bool pasTrie = true;
    for(i = debutDeuxiemeMoitier; i <= finPremiereMoitier; i++){
        table1[i - debutDeuxiemeMoitier] = tableau[i].dep;
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
        }else if (table1[compt1 - debutDeuxiemeMoitier].dep < tableau[compt2].dep){// Si la premiere valeur du tableau trie 1 et plus petite que la première valeur du tableau trie 2 alors on la met a l'indice i du tableau final
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

void fusion_croiss_recur(t_covid tableau, int debutTableau, int finTableau, long *comparaison, long *permutation){
    int milieu;
    if (debutTableau < finTableau){
        milieu = (finTableau + debutTableau) / 2;
        fusion_croiss_recur(tableau, debutTableau, milieu, &*comparaison, &*permutation);
        fusion_croiss_recur(tableau, milieu + 1, finTableau, &*comparaison, &*permutation);
        fusion_c(tableau, debutTableau, milieu, finTableau, &*comparaison, &*permutation);
        //affiche(tableau); // Pour comprendre les étapes
    }
}


void fusion_croiss(t_covid tableau, long *comparaison, long *permutation){
    if (MAX > 0){
        fusion_croiss_recur(tableau, 0, MAX - 1, &*comparaison, &*permutation);
    }
}



void LireFichier(t_covid t)
{
    FILE* f;
    f = fopen("DonneesCovid.data.data","r");
    donnees_covid donnees;
    fread(&donnees, sizeof(donnees_covid),1,f);
    int i = 0;
    while (!feof(f))
    {
        t[i] = donnes;
        fread(&donnees, sizeof(donnees_covid),1,f);
        i = i + 1;
    }
    fclose(f);
}

void triDepartement(t_covid t)
{
    long comp;
    long perm;
    fusion_croiss(t,&comp,&perm);
}


void afficher(t_covid t)
{
    for(int i=0; i<MAX; i++)
    {
        printf("%d %s %d %d %d");
    }
}

int main()
{
    t_covid tab;
    LireFichier(t);
    triDepartement(t);
    afficher(t);
    return EXIT_SUCCESS;
}
