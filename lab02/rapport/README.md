# Rapport

## Introduction

Le laboratoire numéro 2 se consacre à la récursivité. 
En informatique, un algorithme récursif est un algorithme qui inclut au moins un appel à lui-même. Selon _Le Petit
Larousse Illustré 2013_, l'adjectif récursif "se dit d'un programme informatique organisé de manière telle qu'il puisse 
se rappeler lui-même, c'est-à-dire demander sa propre exécution au cours de son déroulement". 
Certaines structures, comme les arbres, sont parfois récursives par nature. Leur traitement est très souvent simplifié 
par l’utilisation d’algorithmes récursifs pour mettre en œuvre leurs opérations

Dans ce laboratoire, nous allons utiliser le concept de récursivité à travers la résolution d'un puzzle impossible, en 
essayant de construire les solutions pas à pas, en partant de la pose de la première pièce jusqu'à la dernière. Nous 
allons créer les solutions en descendant petit à petit dans notre arbre d'appels de notre fonction récursive et 
définir des conditions pour éviter de continuer de parcourir trop longtemps des branches qui ne mènent pas à une 
solution.

## Objectifs

L'objectif principal de ce laboratoire est d'écrire un programme capable de
générer toutes les solutions du puzzle impossible au format permettant de tester
leur validité sur le site https://asd1-heigvd.github.io/ASD1-Labs/puzzle/.

Lorsque le programme est effectif, l'objectif sera de considérer de manière
critique le slogan "des millions de possibilités, une seule solution" en se
basant sur les quatre grandeurs suivantes, que nous devrons donc réussir à mesurer/calculer :

- Nombre total de possibilités de remplir la grille du puzzle
- Nombre total de solutions du puzzle
- Nombre d'appels à la fonction récursive (en ne parcourant pas les branches
  inutiles de l'appel de l'arbre)

## Résultats

### Nombre total de possibilités

Pour calculer le nombre total de possibilités, nous allons utiliser la combinatoire.
Nous allons poser une pièce après l'autre pour remplir notre puzzle de 3x3 cases et calculer combien 
de possibilités de placements existent à chaque nouveau cran.
On peut voir que pour mettre la première pièce, on a 9 cartes différentes
parmi lesquelles choisir avec pour chacune 4 orientations possibles. Cela nous donne donc 36
possibilités. Pour la deuxième pièce, on a 8 cartes parmi lesquelles choisir avec chacune 4 orientations possibles et
donc on multiplie par 32 pour avoir le nombre de possibilités totales pour les deux premières cartes, puis 28, 24....4.
On a donc, pour les 9 cartes 36*32*28*...*8*4 possibilités de remplissage du puzzle.
De cela, on peut déduire la formule mathématique en fonction de n (le nombre de
cartes) suivante: $4^n * n!$, $n$ >= 0. 

Pour $n$ = 9, on trouve ainsi 95'126'814'720 possibilités.

Néanmoins, comme on le verra aussi plus tard, ce résultat nous donnera toutes les
possibilités en comptant les rotations entières du puzzle comme distinctes, ce
que l'on ne veut pas nécessairement. On divisera donc ce résultat par 4 pour
obtenir la formule : $4^{n-1}*n!$, $n$ >= 0.

Pour $n$ = 9, on a donc $4^8 * 9!$ = 23'781'703'680 possibilités uniques.

### Nombre de solutions trouvées

Notre programme nous génère 8 solutions qui sont les suivantes :

- 1b 5d 4a 7a 6a 2a 8a 3a 9d
- 1c 9a 6b 2a 4b 8b 7a 3a 5a
- 4b 2b 9a 5a 6b 3b 1c 7b 8b
- 5c 3c 7c 8d 4d 2c 6d 9c 1a
- 6c 8c 5b 9b 4c 3b 1d 2b 7b
- 7d 2d 1b 3d 4a 9d 5d 8a 6a
- 8d 7d 1a 3d 6d 5c 9c 2d 4d
- 9b 3c 8c 2c 6c 7c 4c 5b 1d

En vérifiant les solutions sur l'outil en
ligne https://asd1-heigvd.github.io/ASD1-Labs/puzzle/,
on constate que toutes les solutions sont correctes.

Il est toutefois nécessaire de noter qu'il n'y a que 2 solutions uniques. En effet, les 8
solutions trouvées sont des rotations de 2 solutions différentes. On peut les
différencier en regardant le numéro de la pièce du milieu (la même entre deux
solutions qui sont des rotations l'une de l'autre).

Finalement, on a comme rotations de la solution 1 :

- 1c 9a 6b 2a 4b 8b 7a 3a 5a
- 5c 3c 7c 8d 4d 2c 6d 9c 1a
- 6c 8c 5b 9b 4c 3b 1d 2b 7b
- 7d 2d 1b 3d 4a 9d 5d 8a 6a

On peut constater dans le tableau ci-dessous qu'il y a une simple rotation de 90°
vers la droite du puzzle entier d'une solution à l'autre. Cela ne représente donc
qu'une seule "vraie solution".

| solution | puzzle résolu associé                               |
|----------|-----------------------------------------------------|
|1c 9a 6b 2a 4b 8b 7a 3a 5a| <img src= images_rapport/puzzle_sol1.png width=250> |
|7d 2d 1b 3d 4a 9d 5d 8a 6a| <img src= images_rapport/puzzle_sol4.png width=250> |
|5c 3c 7c 8d 4d 2c 6d 9c 1a| <img src= images_rapport/puzzle_sol2.png width=250> |
|6c 8c 5b 9b 4c 3b 1d 2b 7b| <img src= images_rapport/puzzle_sol3.png width=250> |

Et comme rotations de la solution 2 :

- 1b 5d 4a 7a 6a 2a 8a 3a 9d
- 4b 2b 9a 5a 6b 3b 1c 7b 8b
- 8d 7d 1a 3d 6d 5c 9c 2d 4d
- 9b 3c 8c 2c 6c 7c 4c 5b 1d

### Nombre d'appels à notre fonction récursive

Le nombre d'appels à notre fonction est de 3'343 (valeur mesurée par notre programme). 

Nous pouvons constater que ce
nombre est bien plus petit que les 95'126'814'720 possibilités (en comptant les rotations) théoriques calculées 
précédemment. Cela est dû au fait que nous ne demandons pas à la fonction récursive de créer toutes les possibilités 
mais uniquement les solutions et que nous réduisons le nombre d'appels de cette fonction en imposant des restrictions 
bien choisies.

En effet, nous ne parcourons pas les branches qui remplissent une des conditions suivantes :

- Aucune carte parmi celles restantes n'est compatible
- Un arrosoir inversé est placé à un endroit devant être comparé avec une autre carte par la suite
- Deux attributs NONE sont comparés

Ces conditions permettent de grandement réduire le nombre d'appels de notre fonction récursive.

## Discussion

Penchons-nous maintenant sur le texte de Djeco : "des millions de possibilités et
une seule solution".

Tout d'abord, nous avons pu constater au point précédent qu'il y a 23'781'703'680
différentes possibilités uniques pour remplir la grille de 3x3 cases. Nous sommes plutôt
dans l'ordre du milliard de possibilités que du million, bien que cela semble déjà
être un très grand nombre.

Ensuite, nous avons pu constater qu'il y a 2 solutions uniques différentes au puzzle
impossible de taille 3x3, ce qui est proche du nombre de 1 cité dans la phrase de
Djeco.

Finalement, nous pouvons dire que la citation "des millions de possibilités et
une seule solution", qui semble déjà démontrer une grande difficulté de la
résolution du puzzle, est en réalité sous-évaluée. On devrait plutôt dire "des
milliards de possibilités, une seule solution" (si on choisit de garder le terme
"une solution" pour un impact marketing).

Cependant, il est évident de noter qu'aucun être humain essayant de résoudre le puzzle ne va continuer à poser des
pièces dans son puzzle lorsqu'il se rend compte qu'il contient une erreur, ni poser une pièce au hasard. En ce sens, en 
tant qu'humains, notre manière de réfléchir est plus proche de l'approche récursive et nous n'allons donc jamais tester 
des milliards de possibilités avant de trouver une solution. 

## Conclusion

Au travers de ce projet, nous avons pu découvrir et prendre en main les différents concepts de
récursivité, que ce soit le cas trivial à gérer ou la généralisation de ce dernier pour pouvoir trouver des solutions 
au puzzle pour tout ensemble de $n$ pièces. Nous avons réussi à implémenter un programme qui, en utilisant une fonction 
récursive, trouve toutes les solutions du puzzle impossible. Cela nous a permis de constater que, dans ce cas où la 
récursivité se fait assez naturellement, procéder à la recherche de solutions par récursion en imposant les bonnes 
conditions est rapide et efficace, bien plus qu'en créant toutes les possibilités de remplissage du puzzle puis en 
recherchant les solutions parmi ces dernières.

Nous avons trouvé un total de 23'781'703'680 possibilités uniques de remplir la grille, 2 solutions uniques au puzzle
et un nombre d'appels de notre fonction de 3343. En considérant ces mesures et calculs, nous avons pu discuter la 
citation "des millions de possibilités et une seule solution". Nous avons conclu qu'en nous basant sur les nombres de 
possibilités et de solutions uniques, cette phrase était sous-évaluée et pourrait être changée en "des milliards de 
possibilités, une seule solution". Néanmoins, malgré ces faits numériques, un humain ne procéderait jamais à une 
résolution du puzzle en testant toutes les possibilités une à une en attendant de tomber sur la bonne. Il s'arrêterait 
plutôt à la moindre erreur et essaierait de la corriger ou de modifier le début de son puzzle. Cette 
approche ressemble beaucoup à la méthode récursive implémentée dans ce laboratoire. Donc, pas de panique, il ne vous
faudra pas un millard d'essais pour résoudre ce puzzle, mais tout au plus quelques centaines !