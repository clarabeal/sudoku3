#ifndef _GRILLE_H
#define _GRILLE_H

#include "Ligne.h"
#include "Colonne.h"
#include "Carre.h"

class Grille {

    public :

    /**
	@brief La grille est un tableau 2D de cases stocké sur le tas
    */
    TabCases2DTas grille;

    /**
	@brief Indique la taille de la grille
    */
    unsigned char dim;

    /**
	@brief Tableau des lignes de la grille
    @details Modelise par un pointeur sur une Ligne
    */
    Ligne* lignes;

    /**
	@brief Tableau des colonnes de la grille
    @details Modelise par un pointeur sur une Colonne
    */
    Colonne* colonnes;

    /**
	@brief Tableau des Carre de la grille
    @details Modelise par un pointeur sur un Carre
    */
    Carre* carres;

    /**
	@brief Constructeur a parametres
    @param [in] d dimension de la grille a creer
    @details Initialise la donnee dim avec d, cree un tableau 2D de cases de taille dim, remplit les lignes, colonnes, carres de la grille
    */
    Grille(unsigned char d);

    /**
	@brief Destructeur
    @details Supprime les tableaux lignes, colonnes, carres qui etaient stockes sur le tas
    */
    ~Grille();

    /**
	@brief Procedure de modification d'une case de la grille
    @param [in] l indice de la ligne a modifier
    @param [in] c indice de la colonne a modifier
    @param [in] nb nouvellle valeur de la case
    @details Affecte la valeur nb a la case d'indice [l][c] de la grille
    */
    void setCase (unsigned char l, unsigned char c, unsigned char nb);

};


#endif