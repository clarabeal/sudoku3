#ifndef _LIGNE_H
#define _LIGNE_H

#include "TabCases2DTas.h"


/**\class Ligne
\details La classe ligne a pour but de faciliter les differents actions a effectuer sur la grille (au meme titre que les classes Carre et Colonne)
La donne membre principale de la class est un tableau de pointeur sur case. Dans l'exemple d'une grille de 9*9 case (voir ci dessous), il s'agit d'un tableau de 9 case.
Lors de la construcion (ou juste apres l'execution de remplir) chaque pointeur du tableau pointe vers la valeur associee dans la grille.

\image html numeroCaseLigneCol.png
\see Carre Colonne*/class Ligne
{
	public:

	/**
    @brief Constructeur par defaut d'une ligne vide
	@details Initialise la donnee membre valide a vrai
    */
	Ligne();

	/**
	@brief Constructeur a parametres
	@details Remplit la ligne avec la ligne numeroLigne de la grille passee en parametre
    */
	Ligne(const unsigned char& numeroLigne, const TabCases2DTas& grille);

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
	void remplir(const unsigned char& numeroLigne, const TabCases2DTas& grille);

	/**
	@brief Procedure d'affichage de la ligne sur la sortie standard
	*/
	void print() const;

	/**
	@brief Fonction qui indique si la valeur passee en parametre est dans la ligne
	@param [IN] val
	@details Retourne 1 si la ligne contient cette valeur et 0 sinon
	*/
	bool isIn(const unsigned char& val);



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
	@details Pointeur sur tableau de pointeurs de cases
    */
	Case **tabl;

	


};


#endif
