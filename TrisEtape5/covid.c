#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX 17776

typedef struct{
    int dep;
    char date[10];
    int pos;
    int classe;
    int pop;
}donnees_covid;

typedef donnees_covid t_covid[MAX];


void permute(donnees_covid t1, donnees_covid t2, long *permutation) {
    *permutation = *permutation +1;
    donnees_covid temp;
    strcpy(temp.date, t1.date);
    temp.classe = t1.classe;
    temp.dep = t1.dep;
    temp.pop = t1.pop;
    temp.pos = t1.pos;
    strcpy(t1.date,t2.date);
    t1.classe = t2.classe;
    t1.dep = t2.dep;
    t1.pop = t2.pop;
    t1.pos = t2.pos;
    strcpy(t2.date,temp.date);
    t2.classe = temp.classe;
    t2.dep = temp.dep;
    t2.pop = temp.pop;
    t2.pos = temp.pos;
}

void shaker_croiss (t_covid t,long *permutation, long *comparaison) {
    int i = 0; // indice du nombre d"éléments déjà trié
    int trie = 0; // Dit si le trie est fini
    while (trie == 0) {
        trie = 1;
        for (int a = i+1; a < MAX-i; a++) { // On fait monter le plus grands nombre du tableau
            *comparaison = *comparaison+1;
            if (t[a].pop < t[a-1].pop) {
                //printf("PERMUTE %d et %d\n", a, a-1);
                trie = 0; // Dit que le trie n'est pas terminé si il y a du changement
                permute(t[a],t[a-1],&*permutation);
            }
        }
        if (trie == 0) {
            for (int b = MAX-i-2; b >= i; b--) { // On fait descendre le plus petit nombre du tableau
                *comparaison = *comparaison +1;
                if (t[b].pop > t[b-1].pop) {
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




void LireFichier(t_covid t)
{
    FILE* f;
    f = fopen("DonneesCovid.data.data","rb");
    donnees_covid donnees;
    fread(&donnees, sizeof(donnees_covid),1,f);
    int i = 0;
    while (!feof(f))
    {
        t[i] = donnees;
        fread(&donnees, sizeof(donnees_covid),1,f);
        i = i + 1;
    }
    fclose(f);
}

void triDepartement(t_covid t)
{
    long comp;
    long perm;
    shaker_croiss(t,&comp,&perm);
}


void afficher(t_covid t)
{
    for(int i=0; i<MAX; i++)
    {
        printf("Departement : %3d | Date : %s | Positif : %3d | Classe : %3d | Population : %8d\n",t[i].dep, t[i].date, t[i].pos, t[i].classe, t[i].pop);
    }
}

int main()
{
    t_covid tab;
    LireFichier(tab);
    triDepartement(tab);
    afficher(tab);
    return EXIT_SUCCESS;
}