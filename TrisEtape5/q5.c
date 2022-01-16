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


void permute(donnees_covid *t1, donnees_covid *t2) {
    donnees_covid temp;
    temp = *t1;
    *t1 = *t2;
    *t2 = temp;
}

void triDepartement (t_covid t) {
    int i = 0; // indice du nombre d"éléments déjà trié
    int trie = 0; // Dit si le trie est fini
    while (trie == 0) {
        trie = 1;
        for (int a = i+1; a < MAX-i; a++) { // On fait monter le plus grands nombre du tableau
            if (t[a].dep < t[a-1].dep) {
                trie = 0;
                permute(&t[a],&t[a-1]);
            }
        }
        if (trie == 0) {
            for (int b = MAX-i-2; b >= i; b--) { // On fait descendre le plus petit nombre du tableau
                if (t[b].dep > t[b+1].dep) { 
                    trie = 0;
                    permute(&t[b],&t[b+1]);
                }
            }
        }
        i=i+1;
    }
}


void triDate(t_covid t)
{
    int i = 0; // indice du nombre d"éléments déjà trié
    int trie = 0; // Dit si le trie est fini
    while (trie == 0) {
        trie = 1;
        for (int a = i+1; a < MAX-i; a++) { // On fait monter le plus grands nombre du tableau
           if (strcmp(t[a].date,t[a-1].date) < 0) {
                trie = 0; // Dit que le trie n'est pas terminé si il y a du changement
                permute(&t[a],&t[a-1]);
            }
        }
        if (trie == 0) {
            for (int b = MAX-i-2; b >= i; b--) { // On fait descendre le plus petit nombre du tableau
                if (strcmp(t[b].date,t[b+1].date) > 0) {
                    trie = 0; // Dit que le trie n'est pas terminé si il y b du changement
                    permute(&t[b],&t[b+1]);
                }
            }
        }
        i=i+1;
    }
}

void debutMesuresPerf(clock_t *t1) {
    *t1 = clock();
}

void finMesuresPerf(clock_t t1) {
    clock_t t2;
    float temps;

    t2 = clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("Temps CPU d'execution : %3fs\n\n", temps);

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


int population22(t_covid t)
{
    int somme =0;
    for (int i = 0; i < MAX; i++)
    {
        if (t[i].dep == 22)
        {
            somme = somme +1;
        }
    }
    return somme;
}



void DebutAnnee35(t_covid t)
{
    int res[10] = {0,0,0,0,0,0,0,0,0,0};
    int somme = 0;

    for (int i = 0; i < MAX; i++)
    {
        if (strcmp("2021-01-01",t[i].date) == 0 && t[i].dep == 35)
        {
            res[t[i].classe/10] = res[t[i].classe/10] + t[i].pos ;
            somme = somme + t[i].pos ;
        }
    }
    printf("Nombre de cas en Ille-et-Vilaine par classe d'age, le 1er janvier 2021\n\n");
    for (int j = 0; j < 10; j++)
    {
        printf("[%d0-%d9] : %d\n",j,j,res[j]);
    }
    printf("\nTOTAL : %d",somme);
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
    clock_t duree;
    t_covid tab;
    LireFichier(tab);
    duree = 0;
    triDepartement(tab);
    debutMesuresPerf(&duree);
    DebutAnnee35(tab);
    finMesuresPerf(duree);
    return EXIT_SUCCESS;
}