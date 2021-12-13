# Saé Tries S1.02
---
Les tries choisis :
- Tri Bulles
- Tri Shaker
- Tri Fusion
---
Chacun de ces 3 tris ont une version de tri croissant et décroissant
---
Liste testé sur le programme:
```c
#define MAX 10

int tabloAleatoire[MAX] = {55, 97, 45, 12, 3, 77, 29, 31, 82, 48};
int tabloAleatoire[MAX] = {3, 12, 29, 31, 45, 48, 55, 77, 82, 97};
int tabloAleatoire[MAX] = {97, 82, 77, 55, 48, 45, 31, 29, 12, 3};
```
---
## Etape 1 :
### Consignes :
- Pour chaque algorithme de tri qui vous sont attribués, écrivez le programme
correspondant en C. Votre programme doit être capable de trier un tableau
d’entiers par ordre croissant des valeurs.
- Écrivez une version "décroissante" de chacun de vos programmes qui trie le
tableau par ordre décroissant.
- Testez vos programmes sur un nombre restreint de valeurs (tableau constant de
10 entiers). 
Ne vous contentez pas d’un seul test d’exécution ! Vous devrez tester vos
programmes de tri par ordre croissant dans le  cas  moyen  (cas  général) mais
aussi dans le  cas favorable  (quand le tableau est déjà trié) et dans le  cas
défavorable (quand le tableau est trié par ordre décroissant.)

## Etape 2 :
### Consignes : 
- Écrivez de nouvelles versions de vos programmes : ils doivent désormais être capables
de trier un tableau de 500 000 entiers. Pour cela vous écrirez une procédure qui remplit
le tableau d’entiers avec des valeurs aléatoires comprises entre 1 et 10*RAND_MAX.
Refaites les mêmes tests que dans la partie 1 (cas moyen, favorable et défavorable).

## Etape 3 :
### Consignes : 
- Écrivez une troisième version de vos programmes pour qu’ils soient capables de trier un
tableaux de 150 000 chaînes de caractères.
- Vous écrirez une procédure qui remplit le tableau avec des chaînes construites de
manière aléatoire et dont la longueur sera comprise aléatoirement entre 5 et 10
caractères. Vos chaînes ne seront composées que de lettres minuscules, donc comprises
entre le caractère ‘a’ (de code 97) et le caractère ‘z’ (de code 122).
Refaites les mêmes tests que dans la partie 1 (cas moyen, favorable et défavorable).