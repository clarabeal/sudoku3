#ifndef _GRILLE_DE_JEU_H
#define _GRILLE_DE_JEU_H

#include "Grille.h"

class GrilleDeJeu {

    public :

    /**
    @brief Grille pleine, contient la solution du sudoku
    */
    Grille grilleSolution;

    /**
    @brief Grille a remplir, celle avec lequel le joueur interagit
    */
    Grille grilleJeu;

    /**
    @brief Genere une grille pleine, qui respecte les contraintes d'une grille de sudoku
    */
    void genererGrillePleine ();

    /**
    @brief Genere la grille de jeu a partir de la grille de solution
    */
    void genererGrilleMinimale ();

    /**
    @brief Verifie qu'une grille de jeu a qu'une unique solution
    */
    unsigned char nombreDeSolutions () const;

};

#endif