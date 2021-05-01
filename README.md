# LIFAP4 - SUDOKU3

## Etudiants du groupe :
- Hervé Eruam p1909323
- Clara Beal p1907112
- Samuel Frew p1914522

## Informations du projet sur la Forge LYON 1 :
- Nom : Sudoku3 LIFAP4
- Identifiant du projet : 18408
- Créateur : Hervé Eruam

## Présentation
Ce projet propose plusieurs variantes du jeu du Sudoku. C'est un jeu qui consiste à compléter une grille de chiffres partiellement remplie avec les chiffres manquants. Les chiffres placés doivent respecter un certain nombre de contraintes : chaque chiffre n'est répeté qu'une seule fois par ligne, par colonne, et par bloc carré. Cette archive propose une version texte (sur terminal), et une version graphique (avec la librairie sdl2). Trois modes de jeu sont proposés sur ces deux versions :

- Classique : reprend le fonctionnement traditionnel du sudoku. Le joueur choisit la taille de la grille avec laquelle il souhaite jouer (4x4, 9x9, 16x16), puis celle-ci est genérée par le programme.  Un chronomètre se lance et c'est au joueur de remplir la grille correctement et sans aide. A la fin de la partie (lorsque la grille est totalement remplie), le nombres d'erreurs ainsi que la grille solution sont affichées.

- Pas à pas : ce mode offre plusieurs aides au joueur afin de l'aider à remplir sa grille de jeu. Il propose notamment d'afficher les coordonnées d'une case simple à remplir, de remplir une des cases.

- 1vs1 : ce mode permet à deux joueurs de s'affronter avec des grilles de Sudoku identiques. Le premier joueur remplit entièrement sa grille de jeu puis, la grille est rénitilialisée et le deuxième joueur remplit la même grille. Une fois la partie terminée, la grille remplie par le premier joueur et la grille du deuxième joueur ainsi que la grille solution sont affichées. 

De plus, un gestionnaire de sauvegarde accessible depuis le menu est proposé dans chaque mode de jeu. Il permet de sauvgarder une partie non terminée puis de quitter le jeu afin de la recharger ultérieurement pour la terminer. Un chronomètre est également affiché à l'écran lors de chaque partie.

## Compilation
Le projet ce compile grâce à un fichier makefile. Pour compiler le projet, il faut taper la commande `make` dans un terminal à la racine du dossier. Cette commande permet de compiler à la fois la version texte et la version graphique. Pour compiler seulement la version texte, il faut taper la commande `make sudoku_txt` dans un terminal. Pour compiler la version graphique, il faut taper la commande `make sudoku_sdl`. Il est possible de compiler le programme sous les Os suivants : Windows, MacOs et Linux. La bibliothèque externe SDL2 doit être présente sur la machine pour permettre la compilation. Cette dernière est incluse dans le dossier extern de notre archive.

## Executables du projet
- `sudoku_txt` : version console de l'application
- `sudoku_sdl` : version fenêtre graphique de l'application

## Lancement des éxecutables
Il faut ouvrir un terminal à la racine du dossier et taper la commande suivante :
- `./bin/sudoku_txt`pour lancer le programme en mode console
- `./bin/sudoku_sdl`pour lancer le programme en mode graphique

## Organisation de l'archive

- `bin/` : contient les executables (`sudoku_txt` et `sudoku_sdl`)

- `data/` : contient tous les fichiers utiles à SDL pour réaliser l'affichage graphique (images des grilles, des chiffres, des menus etc)

- `dep/` : contient les fichiers listant les dépendances utilisées par le makefile

- `doc`: contient la documentation du code créée par Doxygen dans le fichier (html/index.html) et les fichiers Doxygen associés. Contient également le digrammme des classes UML final de notre application ainsi que le diagramme de Gantt et les tâches réalisées par chaque membre du groupe. Le fichier PDF de la présentation orale se trouve également dans ce dossier.

- `obj/` : contient les fichiers objets (*.o) intermédiaires

- `extern` : contient les fichiers exernes nécessaires au bon fonctionnement du jeu : la librairie graphique SDL2

- `src/` : contient les fichiers sources (*.h et *.cpp) qui codent notre application 

- `Readme.md` : ce fichier readme

- `makefile` : permet de compiler les deux programmes (création des fichiers objets et l'édition des liens) 

## Comment jouer au Sudoku3?

### Sur la version texte

Il faut utiliser les touches numériques du clavier afin de saisir les valeurs à placer, les coodonnées de la case où l'on souhaite placer le nombre ainsi que les différentes fonctionnalités du menu. Toutes les options du menus sont de la forme : "Touche : Option".

### Sur la version graphique

Au cours du jeu, les touches du clavier offrent les options suivantes : 
- n : permet de générer une nouvelle grille de jeu
- p : permet de mettre le chronomètre en pause
- s : permet de relancer le chronomètre

Pour jouer, il suffit de cliquer à l'aide de la souris sur la case que l'on souhaite remplir, puis d'utiliser le sélecteur à l'écran en cliquant sur le chiffre choisi afin de placer la valeur dans la grille. Pour quitter le jeu, il faut fermer la fenêtre à l'aide de la croix en haut.