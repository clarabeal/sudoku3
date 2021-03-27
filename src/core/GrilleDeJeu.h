#ifndef _GRILLE_DE_JEU_H
#define _GRILLE_DE_JEU_H

#include "Grille.h"

class Jeu {

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
    Jeu(unsigned char d);

    /**
    @brief Destructeur
    */
    ~Jeu();

    /**
    @brief Genere une grille pleine, qui respecte les contraintes d'une grille de sudoku
    */
    bool genererGrillePleine (int etape = 0);

    /**
    @brief Remplit un tableau avec entiers aleatoires compris entre 1 et max
    @param [je sais pas] tab : le tableau a remplir
    @param [in] max la valeur maximale que doivent prendre les nombres geres aleatoirement
    */
    void remplirTblAlea(unsigned char* tab, unsigned char max);


    /**
    @brief Renvoie le nombre de solution possible pour une grille
    */
    unsigned char nombreDeSolutions (Grille &grille, unsigned char nbSolution = 0) const;

    /**
    @brief Genere la grille de jeu a partir de la grille de solution
    */
    void genererGrilleMinimale ();

    /**
  @brief Verifie si la grille est pleine ou non
  @details Retourne 1 si pleine 0 sinon
  */
    bool verifGrillePleine(Grille& grille) const;
private:

    /**
    @brief Determine dans quel carre de la grille se trouve la case [l][c]
    @details Retourne l'indice du carre dans lequel se trouve la case
    */
    unsigned char trouverNumeroCarre(unsigned char l, unsigned char c) const;

  

};

#endif