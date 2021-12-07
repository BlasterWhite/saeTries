#include <stdlib.h>
#include <stdio.h>

#define TAILLE_TAB 10
typedef int table[TAILLE_TAB];



void fusion(int t1[], int t2[])
{

}



void tri_fusion(table t)
{
    int milieu = TAILLE_TAB/2;
    if (TAILLE_TAB!=1 || TAILLE_TAB!=0)
    {
        int t1[milieu];
        int t2[milieu];
        for (int i = 0; i < milieu; i++)
        {
            t1[i] = t[i];
        }
        for (int i = TAILLE_TAB-1; i >= milieu; i--)
        {
            t2[i] = t[i];
        }
        fusion(t)

        
    }
}



void affiche(table t)
{
    for (int i = 0; i < TAILLE_TAB; i++)
    {
        printf("%d ",t[i]);
    }
    printf("\n");
}

int main()
{
    table tab = {10,6,78,40,45,64,12,1,0,40};
    table tab_croiss = {0,2,4,8,14,15,81,86,90,99};
    table tab_decroiss = {90,80,74,50,26,24,13,12,10,1};
    shaker_croiss(tab);
    shaker_croiss(tab_croiss);
    shaker_croiss(tab_decroiss);
    affiche(tab);
    affiche(tab_croiss);
    affiche(tab_decroiss);
    return EXIT_SUCCESS;
    
}