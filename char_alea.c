#include<stdlib.h>
#include<stdio.h>
#include <time.h>
#include<string.h>

#define TAB_MAX 150000
#define TAILLE_CHAINE 11

typedef char t_tab_chaine[TAB_MAX][TAILLE_CHAINE];

char char_alea()
{
    return (rand() % 25)+97;
}

int nb_alea()
{
    return (rand() % (TAILLE_CHAINE-5))+5;
}

/*
void gen_chaine(char chaine[], int taille)
{
    for (int i = 0; i < taille; i++)
    {
        chaine[i] = char_alea();
    }
}
*/

void remplir_tab(t_tab_chaine tab)
{
    for (int i = 0; i < TAB_MAX; i++)
    {
        for (int j = 0; j < nb_alea(); j++)
        {
            tab[i][j] = char_alea();
        }
    }
}


void afficher(t_tab_chaine tab)
{
    for (int i = 0; i < TAB_MAX; i++)
    {
        printf("%s\n",tab[i]);
    }
    
}

int main()
{
    t_tab_chaine t;
    remplir_tab(t);
    afficher(t);
    return EXIT_SUCCESS;
}


