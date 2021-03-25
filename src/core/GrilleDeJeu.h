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
    @brief Constructeur a parametres
    @details Cree une grilleJeu et une grilleSolution ttes les 2 de taille dim
    */
    GrilleDeJeu(unsigned char d);

    /**
    @brief Destructeur
    */
    ~GrilleDeJeu();

    /**
    @brief Genere une grille pleine, qui respecte les contraintes d'une grille de sudoku
    */
    bool genererGrillePleine ();

    /**
    @brief Remplit un tableau avec entiers aleatoires compris entre 1 et max
    @param [je sais pas] tab : le tableau a remplir
    @param [in] max la valeur maximale que doivent prendre les nombres geres aleatoirement
    */
    void remplirTblAlea(unsigned char* tab, unsigned char max);

    /**
    @brief Genere la grille de jeu a partir de la grille de solution
    */
    void genererGrilleMinimale ();

    /**
    @brief Verifie qu'une grille de jeu a qu'une unique solution
    */
    unsigned char nombreDeSolutions () const;

private:

    /**
    @brief Determine dans quel carre de la grille se trouve la case [l][c]
    @details Retourne l'indice du carre dans lequel se trouve la case
    */
    unsigned char trouverNumeroCarre(unsigned char l, unsigned char c) const;

    /**
    @brief Verifie si la grille est pleine ou non
    @details Retourne 1 si pleine 0 sinon
    */
    bool verifGrillePleine() const;

};

#endif