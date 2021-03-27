#ifndef _TXT_IHM
#define _TXT_IHM

#include "../core/GrilleDeJeu.h"

class TXT_IHM
{
public:
	TXT_IHM();

	~TXT_IHM();
	
	/**
	\brief Boucle du jeu
	*/
	void boucle();

	/**
	\brief Affiche la grille sur le terminal
	*/
	void afficherGrille();

private:
	GrilleDeJeu jeu;
    
};


#endif