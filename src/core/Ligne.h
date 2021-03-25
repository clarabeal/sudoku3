#ifndef _LIGNE_H
#define _LIGNE_H

#include "TabCases2DTas.h"

class Ligne
{
	public:

	bool valide;

	/**
	@brief Indique la taille de la grille
    */
	unsigned char tailleGrille;

	/**
	@brief Indique la taille de la ligne
    */
	unsigned char tailleLigne;

	/**
	@brief Ligne
	@details Tableau de pointeurs de pointeurs de cases
    */
	Case **tabl;

	/**
    @brief Constructeur par defaut d'une ligne vide
	@details Initialise la donnee membre valide a vrai
    */
	Ligne();

	/**
	@brief Constructeur a parametres
	@details Remplit la ligne avec la ligne numeroLigne de la grille passee en param
    */
	Ligne(unsigned char numeroLigne, TabCases2DTas& grille);

	/**
	@brief Destructeur
	@details Supprime les elements contenus dans tabl du tas
    */
	~Ligne();

	/**
	@brief Procedure de remplissage d'une ligne
	@details Remplit la ligne avec la ligne d'indice numeroLigne de la grille
	@param [IN] numeroLigne : numero de la ligne a recopier
	@param [IN] grille : reference sur un TabCases2DTas
    */
	void remplir(unsigned char numeroLigne, TabCases2DTas& grille);
	
	/**
	@brief Procedure d'affichage de la ligne sur la sortie standard
    */
	void print() const;

	/**
	@brief Fonction qui indique si la valeur passee en parametre est dans la ligne
	@param [IN] val
 	@details Retourne 1 si la ligne contient cette valeur et 0 sinon
    */
	bool isIn(unsigned char val);

};


#endif
