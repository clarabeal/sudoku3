# LIFAP4 - SUDOKU3

## Etudiants du groupe :
- Hervé Eruam p1909323
- Clara Beal p1907112
- Samuel Frew p1914522

## Présentation
Ce projet propose plusieurs variantes du jeu du Sudoku. Cette archive propose une version texte (sur terminal), et une version graphique (avec la librairie sdl2). Trois modes de jeu sont proposés sur ces deux versions :

- Classique : reprend le fonctionnement classique du sudoku. Le joueur choisit la taille de la grille avec laquelle il souhaite jouer (4x4, 9x9, 16x16), puis celle-ci est genérée par le programme.  Un chronomètre se lance et c'est au joueur de remplir la grille correctement et sans aide. A la fin de la partie, le nombres d'erreurs ainsi que la grille solution sont affichées.

- Pas à pas : ce mode offre plusieurs aides au joueur afin de l'aider à remplir sa grille de jeu. Il propose notamment d'afficher les coordonnées d'une case simple à remplir, de remplir une des cases.

- 1vs1 : ce mode permet à deux joueurs de s'affronter sur une même grille de sudoku. Le premier joueur remplit entièrement la grille puis le deuxième joueur remplit la même grille. Une fois la partie terminée, la grille de chacun des joueurs est affichée ainsi que la grille solution. 

De plus, un gestionnaire de sauvegarde accessible depuis le menu est proposé dans chaque mode de jeu. Un chronomètre est également affiché lors de chaque partie.

## Compilation
Le projet ce compile grâce à un fichier makefile. Pour compiler le projet, il faut taper la commande `make` dans un terminal. Pour compiler seulement la version texte, il faut taper la commande `make sudoku_txt` dans un terminal. Pour compiler la version graphique, il faut taper la commande `make sudoku_sdl`. Il est possible de compiler le programme sous les Os suivants : Windows, MacOs et Linux. La bibliothèque externe SDL2 doit être présente sur la machine pour permettre la compilation. Cette dernière est incluse dans le dossier extern.

## Executables du projet
- `sudoku_txt` : version console
- `sudoku_sdl` : version fenêtre graphique

## Organisation de l'archive
- `bin/` : contient les executables (`sudoku_txt` et `sudoku_sdl`)
- `obj/` : contient les fichiers .o intermédiaires
- `dep/` : 
- `data/` :
- `extern` : 
- `dep` : 
- `src/` : contient les fichiers codant le jeu.
- `Readme.md` : ce readme.
- `makefile` : permet de compiler les deux programmes

## Comment jouer?

### Sur la version texte

Il faut utiliser les touches numériques du clavier afin de saisir les valeurs, les coodonnées de la case ainsi que les différentes fonctionnalités du menu. Toutes les options du menus sont de la forme : Touche : Option.

### Sur la version graphique

Au cours du jeu, les touches du clavier offrent les options suivantes : 
- n : permet de générer une nouvelle grille de jeu
- p : permet de mettre le chronomètre en pause
- s : permet de relancer le chronomètre