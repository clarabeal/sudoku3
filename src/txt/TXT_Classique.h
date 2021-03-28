#ifndef _TXT_CLASSIQUE_H
#define _TXT_CLASSIQUE_H

#include "../core/GrilleDeJeu.h"

class TXT_Classique
{
public:
	TXT_Classique(unsigned char d);

	~TXT_Classique();
	
	/**
	\brief Boucle du jeu
	*/
	void boucle();

	/**
	\brief Affiche la grille de jeu sur le terminal
	*/
	void afficherGrille();

private:
	Jeu jeu;
    
};


#endif