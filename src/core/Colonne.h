#ifndef _COLONNE_H
#define _COLONNE_H

#include "TabCases2DTas.h"


class Colonne
{
public:

	bool valide;

	/**
	@brief Indique la taille de la grille
    */
	unsigned char tailleGrille;

	/**
	@brief Colonne
	@details Tableau de pointeurs de pointeurs de cases
    */
	Case **tabcl;
	
	/**
    @brief Constructeur par defaut d'une colonne vide
	@details Initialise la donnee membre valide a vrai
    */
	Colonne();

	/**
	@brief Constructeur a parametres
	@details Remplit la colonne avec la colonne numeroColonne de la grille passee en parametre
    */
	Colonne(unsigned char numeroColonne, TabCases2DTas& grille);

	/**
	@brief Destructeur
	@details Supprime les elements contenus dans tabc du tas
    */
	~Colonne();
	
	/**
	@brief Procedure de remplissage d'une colonne
	@details Remplit la colonne avec la colonne d'indice numeroColonne de la grille
	@param [IN] numeroColonne : numero de la colonne a recopier
	@param [IN] grille : reference sur un TabCases2DTas
    */
	void remplir(unsigned char numeroColonne, TabCases2DTas& grille);
	
	/**
	@brief Procedure d'affichage de la ligne sur la sortie standard
    */
	void print() const;
	
	/**
	@brief Fonction qui indique si la valeur passee en parametre est dans la colonne
	@param [IN] val
 	@details Retourne 1 si la colonne contient cette valeur et 0 sinon
    */
	bool isIn(unsigned char val);
};



#endif
