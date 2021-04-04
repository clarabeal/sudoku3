#ifndef _TXT_CLASSIQUE_H
#define _TXT_CLASSIQUE_H

#include "Jeu.h"

class TXT_Classique
{
public:
	TXT_Classique(unsigned char d);
	TXT_Classique(unsigned char d, int id, Grille& g_sol, Grille& g_orig, Grille& g_jeu);

	~TXT_Classique();
	
	/**
	\brief Boucle du jeu
	*/
	void boucle();

	unsigned char menu() const;

private:
	Jeu jeu;
	void termClear() const;
};


#endif