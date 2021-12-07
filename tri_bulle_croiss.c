#include <stdlib.h>
#include <stdio.h>

#define N 10
typedef int table[N];


void bulle_croiss (table t)
{
    int i = 0;
    int trie = 0;
    int temp;
    while (trie == 0)
    {
        trie = 1;
        for (int a = 1; a < N-i; a++)
        {
            if (t[a] < t[a-1])
            {
                trie = 0;
                temp = t[a];
                t[a] = t[a-1];
                t[a-1] = temp;
            }
        }
        i = i+1;
    }
}

void affiche(table t)
{
    for (int i = 0; i < N; i++)
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
    affiche(tab);
    affiche(tab_croiss);
    affiche(tab_decroiss);
    printf("------------------------- triées ----------------------------------\n");
    bulle_croiss(tab);
    bulle_croiss(tab_croiss);
    bulle_croiss(tab_decroiss);
    affiche(tab);
    affiche(tab_croiss);
    affiche(tab_decroiss);
    return EXIT_SUCCESS;
    
}