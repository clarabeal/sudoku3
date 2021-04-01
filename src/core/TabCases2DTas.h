#ifndef _TabCases2DTas_H
#define _TabCases2DTas_H

#include "Case.h"

class TabCases2DTas
{
public:

	/**
	@brief Constructeur
	@details Cree un tableau de taille dimLignes*dimColonnes sur le tas, initialise les donnes dimLigne et dimColonne avec les param fournis
    */
	TabCases2DTas(unsigned char dimLignes, unsigned char dimColonnes);

	/**
	@brief Destructeur
	@details Supprime le tableau de cases du tas
    */
	~TabCases2DTas();
	
	/**
	@brief Accesseur : retourne dimLignes
    */
	unsigned char getDimLignes() const;

	/**
	@brief Accesseur : retourne dimColonnes
    */
	unsigned char getDimCol() const;

	/**
	@brief Accesseur : retourne une reference sur la case [ligne][colonne] (entre 0 et dimGrille)
	@param [in] ligne
	@param [in] colonne
    */
	Case& getCase(unsigned char ligne, unsigned char col) const;

	/**
	@brief Accesseur : retourne un pointeur sur la case [ligne][colonne]
	@param [in] ligne
	@param [in] colonne
    */
	Case *getPtr(unsigned char ligne, unsigned char col) const;

	/**
	@brief Procedure d'affichage du tableau 2D sur la sortie standard
    */
	void print() const;

	/**
	@brief Set toutes les cases du tableau a 0 et les rends non modifiable
	*/
	void vider();

	void operator = (TabCases2DTas &tab);
private:

	/**
	@brief Nombre de lignes du tableau 2D
    */
	unsigned char dimLignes;

	/**
	@brief Nombre de colonnes du tableau 2D
    */
	unsigned char dimColonnes;

	/**
	@brief Tableau de cases (pointeur sur une case)
    */
	Case *tab;
};


#endif
