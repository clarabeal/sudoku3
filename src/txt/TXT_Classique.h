#ifndef _TXT_CLASSIQUE_H
#define _TXT_CLASSIQUE_H

#include "../core/Sauvegarde.h"

class TXT_Classique
{
public:
	TXT_Classique(const unsigned char& d);
	TXT_Classique(const unsigned char& d, const int& id, const unsigned long int& time, const Grille& g_sol, const Grille& g_orig, const Grille& g_jeu);

	~TXT_Classique();
	
	/**
	\brief Boucle du jeu
	*/
	void boucle();

	unsigned char menu();

private:
	Jeu jeu;
	void termClear() const;
};


#endif