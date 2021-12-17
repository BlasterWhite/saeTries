#include<stdlib.h>
#include<stdio.h>
#include <time.h>
#include<string.h>

#define TAB_MAX 150000
#define TAILLE_CHAINE 11

typedef char t_chaine[TAILLE_CHAINE];
typedef t_chaine t_tab_chaine[TAB_MAX];

char char_alea()
{
    return (rand() % 25)+97;
}


int nb_alea()
{
    return (rand() % (TAILLE_CHAINE-5))+5;
}


void remplir_tab(t_tab_chaine tab)
{
    for (int i = 0; i < TAB_MAX; i++)
    {
        int alea = nb_alea();
        for (int j = 0; j < alea; j++)
        {
            tab[i][j] = char_alea();
            if (j == alea-1)
            {
                tab[i][j+1] = '\0';
            }
            
        }
    }
}

void bulle_croiss (t_tab_chaine t) {
    int i = 0; // indice du nombre d"éléments déjà trié
    int trie = 0; // Dit si le trie est fini
    t_chaine temp; // variable temporaire pour l'echange de place
    while (trie == 0) {
        trie = 1;
        for (int a = 1; a < TAB_MAX-i; a++) {
            if (strcmp(t[a],t[a-1]) < 0) {
                printf("%d",a);
                trie = 0;
                strcpy(temp,t[a]);
                strcpy(t[a],t[a-1]);
                strcpy(t[a-1],temp);
            }
        }
        i = i+1;
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
    bulle_croiss(t);
    afficher(t);
    return EXIT_SUCCESS;
}