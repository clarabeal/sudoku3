#ifndef _CARRE_H
#define _CARRE_H

#include "TabCases2DTas.h"

#include <iostream>
#include <cassert>
#include <math.h>

/**\brief Reresente un carre dans une grille
\details La classe Carre a pour but de faciliter les differents actions a effectuer sur la grille (au meme titre que les classes Ligne et Colonne)
La donne membre principale de la class est un tableau de pointeur sur case. Dans l'exemple d'une grille de 9*9 case (voir ci dessous), il s'agit d'un tableau de 3*3 (en realite modelise sous la forme d'un tableau de 9 cases sur une dimension).
Lors de la construcion (ou juste apres l'execution de remplir) chaque pointeur du tableau pointe vers la valeur associee dans la grille. 

\image html numeroCaseLigneCol.png
\see Ligne Colonne*/
class Carre
{
public:
	/**\brief Constructeur par defaut
	\details Ne fait rien et n'a pas vocation a etre utilise seul
	\warning La fonction remplir doit etre appelee avant toute autre manipulation */
	Carre();

	/**\brief Constructeur
	\details Constructeur qui appel directement remplir
	\see remplir(unsigned char numeroCarre, TabCases2DTas& grille) */
	Carre(const unsigned char& numeroCarre, const TabCases2DTas& grille);

	~Carre();

	/**
	\brief Remplit le carre en fonction de sa position dans la grille 
	\details Prends en parametre une reference sur grille et le numero du carre(qui definit sa postion dans la grille voir l'image de la description de la classe)
	Copie l'adresse des cases correspondantes de la grille passee en parametre dans le tableau local a la fonction et initialise la variable tailleGrille
	*/
	void remplir(const unsigned char& numeroCarre, const TabCases2DTas& grille);

	/**\brief Indique si l'element passe en parametre est deja dans le carre (0 si non 1 si oui)*/
	bool isIn(const unsigned char& val) const;

	/**\brief Affiche a l'ecran toutes les informations utiles sur la fonction, utile pour le debugage */
	void print() const;

	/**\brief Tableau de pointeur sur les cases du carre
	\details Il s'agit d'un double pointeur car la taille d'un carre etant definie lors de l'instanciation du carre celui-ci doit etre sur le tas */
	Case **tabc;
	

private:
	/**\brief Contient la taille de la grille ou se trouve le carre(en nombre de case)*/
	unsigned char tailleGrille;

	/**\brief Contient la taille d'un carre de la grille ou se trouve le carre(en nombre de case). Ex: Grille de 9*9 -> carre 3*3*/
	unsigned char tailleCarre;
};



#endif
