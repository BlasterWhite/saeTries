#include <stdlib.h>
#include <stdio.h>

#define MAX 10

typedef int table[MAX];

void bulle_croiss (table t) {
    int i = 0;
    int trie = 0;
    int temp;
    while (trie == 0)
    {
        trie = 1;
        for (int a = 1; a < MAX-i; a++)
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
    for (int i = 0; i < MAX; i++)
    {
        printf("%d ",t[i]);
    }
    printf("\n");
}

int main()
{

    table tabloAleatoire = {55, 97, 45, 12, 3, 77, 29, 31, 82, 48};
    table tabloCroissant = {3, 12, 29, 31, 45, 48, 55, 77, 82, 97};
    table tabloDecroissant = {97, 82, 77, 55, 48, 45, 31, 29, 12, 3};
    printf("          TRI BULLES          \n\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("tableau avant tri : \n");
    affiche(tabloAleatoire);
    bulle_croiss(tabloAleatoire);
    printf("tableau après tri : \n");
    affiche(tabloAleatoire);
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("tableau avant tri : \n");
    affiche(tabloCroissant);
    bulle_croiss(tabloCroissant);
    printf("tableau après tri : \n");
    affiche(tabloCroissant);
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("tableau avant tri : \n");
    affiche(tabloDecroissant);
    bulle_croiss(tabloDecroissant);
    printf("tableau après tri : \n");
    affiche(tabloDecroissant);
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    return EXIT_SUCCESS;
    
}